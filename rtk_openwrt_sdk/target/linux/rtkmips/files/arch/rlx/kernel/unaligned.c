/*
 * Handle unaligned accesses by emulation.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1996, 1998, 1999, 2002 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 *
 * This file contains exception handler for address error exception with the
 * special capability to execute faulting instructions in software.  The
 * handler does not try to handle the case when the program counter points
 * to an address not aligned to a word boundary.
 *
 * Putting data to unaligned addresses is a bad practice even on Intel where
 * only the performance is affected.  Much worse is that such code is non-
 * portable.  Due to several programs that die on MIPS due to alignment
 * problems I decided to implement this handler anyway though I originally
 * didn't intend to do this at all for user code.
 *
 * For now I enable fixing of address errors by default to make life easier.
 * I however intend to disable this somewhen in the future when the alignment
 * problems with user programs have been fixed.	 For programmers this is the
 * right way to go.
 *
 * Fixing address errors is a per process option.  The option is inherited
 * across fork(2) and execve(2) calls.	If you really want to use the
 * option in your user programs - I discourage the use of the software
 * emulation strongly - use the following code in your userland stuff:
 *
 * #include <sys/sysmips.h>
 *
 * ...
 * sysmips(MIPS_FIXADE, x);
 * ...
 *
 * The argument x is 0 for disabling software emulation, enabled otherwise.
 *
 * Below a little program to play around with this feature.
 *
 * #include <stdio.h>
 * #include <sys/sysmips.h>
 *
 * struct foo {
 *	   unsigned char bar[8];
 * };
 *
 * main(int argc, char *argv[])
 * {
 *	   struct foo x = {0, 1, 2, 3, 4, 5, 6, 7};
 *	   unsigned int *p = (unsigned int *) (x.bar + 3);
 *	   int i;
 *
 *	   if (argc > 1)
 *		   sysmips(MIPS_FIXADE, atoi(argv[1]));
 *
 *	   printf("*p = %08lx\n", *p);
 *
 *	   *p = 0xdeadface;
 *
 *	   for(i = 0; i <= 7; i++)
 *	   printf("%02x ", x.bar[i]);
 *	   printf("\n");
 * }
 *
 * Coprocessor loads are not supported; I think this case is unimportant
 * in the practice.
 *
 * TODO: Handle ndc (attempted store to doubleword in uncached memory)
 *	 exception for the R6000.
 *	 A store crossing a page boundary might be executed only partially.
 *	 Undo the partial store in this case.
 */
#include <linux/context_tracking.h>
#include <linux/mm.h>
#include <linux/signal.h>
#include <linux/smp.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <linux/perf_event.h>

#include <asm/asm.h>
#include <asm/branch.h>
#include <asm/byteorder.h>
#include <asm/fpu.h>
#include <asm/fpu_emulator.h>
#include <asm/inst.h>
#include <asm/uaccess.h>

#define STR(x)	__STR(x)
#define __STR(x)  #x

enum {
	UNALIGNED_ACTION_QUIET,
	UNALIGNED_ACTION_SIGNAL,
	UNALIGNED_ACTION_SHOW,
};
#ifdef CONFIG_DEBUG_FS
static u32 unaligned_instructions;
static u32 unaligned_action;
#else
#define unaligned_action UNALIGNED_ACTION_QUIET
#endif
extern void show_registers(struct pt_regs *regs);

#ifdef __BIG_ENDIAN
#define     LoadHW(addr, value, res)  \
		__asm__ __volatile__ (".set\tnoat\n"        \
			"1:\tlb\t%0, 0(%2)\n"               \
			"2:\tlbu\t$1, 1(%2)\n\t"            \
			"sll\t%0, 0x8\n\t"                  \
			"or\t%0, $1\n\t"                    \
			"li\t%1, 0\n"                       \
			"3:\t.set\tat\n\t"                  \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#ifdef CONFIG_CPU_HAS_ULS
#define     LoadW(addr, value, res)   \
		__asm__ __volatile__ (                      \
			"1:\tlwl\t%0, (%2)\n"               \
			"2:\tlwr\t%0, 3(%2)\n\t"            \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));
#else
#define     LoadW(addr, value, res)   \
		__asm__ __volatile__ (                      \
			"1:\tlbu\t%0, 0(%2)\n\t"            \
			"lbu\t%1, 1(%2)\n\t"                \
			"sll\t%0, 8\n\t"                    \
			"or\t%0, %1\n\t"                    \
			"lbu\t%1, 2(%2)\n\t"                \
			"sll\t%0, 8\n\t"                    \
			"or\t%0, %1\n\t"                    \
			"lbu\t%1, 3(%2)\n\t"                \
			"sll\t%0, 8\n\t"                    \
			"or\t%0, %1\n\t"                    \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=&r" (res)        \
			: "r" (addr), "i" (-EFAULT));
#endif

#define     LoadHWU(addr, value, res) \
		__asm__ __volatile__ (                      \
			".set\tnoat\n"                      \
			"1:\tlbu\t%0, 0(%2)\n"              \
			"2:\tlbu\t$1, 1(%2)\n\t"            \
			"sll\t%0, 0x8\n\t"                  \
			"or\t%0, $1\n\t"                    \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".set\tat\n\t"                      \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#define     LoadWU(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tlwl\t%0, (%2)\n"               \
			"2:\tlwr\t%0, 3(%2)\n\t"            \
			"dsll\t%0, %0, 32\n\t"              \
			"dsrl\t%0, %0, 32\n\t"              \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			"\t.section\t.fixup,\"ax\"\n\t"     \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#define     LoadDW(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tldl\t%0, (%2)\n"               \
			"2:\tldr\t%0, 7(%2)\n\t"            \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			"\t.section\t.fixup,\"ax\"\n\t"     \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#define     StoreHW(addr, value, res) \
		__asm__ __volatile__ (                      \
			".set\tnoat\n"                      \
			"1:\tsb\t%1, 1(%2)\n\t"             \
			"srl\t$1, %1, 0x8\n"                \
			"2:\tsb\t$1, 0(%2)\n\t"             \
			".set\tat\n\t"                      \
			"li\t%0, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=r" (res)                        \
			: "r" (value), "r" (addr), "i" (-EFAULT));

#ifdef CONFIG_CPU_HAS_ULS
#define     StoreW(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tswl\t%1,(%2)\n"                \
			"2:\tswr\t%1, 3(%2)\n\t"            \
			"li\t%0, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
		: "=r" (res)                                \
		: "r" (value), "r" (addr), "i" (-EFAULT));
#else
#define     StoreW(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tor\t%0,%1,$0\n\t"              \
			"sb\t%0,3(%2)\n\t"                  \
			"srl\t%0,8\n\t"                     \
			"sb\t%0,2(%2)\n\t"                  \
			"srl\t%0,8\n\t"                     \
			"sb\t%0,1(%2)\n\t"                  \
			"srl\t%0,8\n\t"                     \
			"sb\t%0,0(%2)\n\t"                  \
			"li\t%0,0\n"                        \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			".previous"                         \
		: "=&r" (res)                               \
		: "r" (value), "r" (addr), "i" (-EFAULT));
#endif

#define     StoreDW(addr, value, res) \
		__asm__ __volatile__ (                      \
			"1:\tsdl\t%1,(%2)\n"                \
			"2:\tsdr\t%1, 7(%2)\n\t"            \
			"li\t%0, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
		: "=r" (res)                                \
		: "r" (value), "r" (addr), "i" (-EFAULT));
#endif

#ifdef __LITTLE_ENDIAN
#define     LoadHW(addr, value, res)  \
		__asm__ __volatile__ (".set\tnoat\n"        \
			"1:\tlb\t%0, 1(%2)\n"               \
			"2:\tlbu\t$1, 0(%2)\n\t"            \
			"sll\t%0, 0x8\n\t"                  \
			"or\t%0, $1\n\t"                    \
			"li\t%1, 0\n"                       \
			"3:\t.set\tat\n\t"                  \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#ifdef CONFIG_CPU_HAS_ULS
#define     LoadW(addr, value, res)   \
		__asm__ __volatile__ (                      \
			"1:\tlwl\t%0, 3(%2)\n"              \
			"2:\tlwr\t%0, (%2)\n\t"             \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));
#else
#define     LoadW(addr, value, res)   \
		__asm__ __volatile__ (                      \
			"1:\tlbu\t%0,3(%2)\n\t"             \
			"lbu\t%1,2(%2)\n\t"                 \
			"sll\t%0,8\n\t"                     \
			"or\t%0,%1\n\t"                     \
			"lbu\t%1,1(%2)\n\t"                 \
			"sll\t%0,8\n\t"                     \
			"or\t%0,%1\n\t"                     \
			"lbu\t%1,0(%2)\n\t"                 \
			"sll\t%0,8\n\t"                     \
			"or\t%0,%1\n\t"                     \
			"li\t%1,0\n"                        \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=&r" (res)        \
			: "r" (addr), "i" (-EFAULT));
#endif

#define     LoadHWU(addr, value, res) \
		__asm__ __volatile__ (                      \
			".set\tnoat\n"                      \
			"1:\tlbu\t%0, 1(%2)\n"              \
			"2:\tlbu\t$1, 0(%2)\n\t"            \
			"sll\t%0, 0x8\n\t"                  \
			"or\t%0, $1\n\t"                    \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".set\tat\n\t"                      \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#define     LoadWU(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tlwl\t%0, 3(%2)\n"              \
			"2:\tlwr\t%0, (%2)\n\t"             \
			"dsll\t%0, %0, 32\n\t"              \
			"dsrl\t%0, %0, 32\n\t"              \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			"\t.section\t.fixup,\"ax\"\n\t"     \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#define     LoadDW(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tldl\t%0, 7(%2)\n"              \
			"2:\tldr\t%0, (%2)\n\t"             \
			"li\t%1, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			"\t.section\t.fixup,\"ax\"\n\t"     \
			"4:\tli\t%1, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=&r" (value), "=r" (res)         \
			: "r" (addr), "i" (-EFAULT));

#define     StoreHW(addr, value, res) \
		__asm__ __volatile__ (                      \
			".set\tnoat\n"                      \
			"1:\tsb\t%1, 0(%2)\n\t"             \
			"srl\t$1,%1, 0x8\n"                 \
			"2:\tsb\t$1, 1(%2)\n\t"             \
			".set\tat\n\t"                      \
			"li\t%0, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
			: "=r" (res)                        \
			: "r" (value), "r" (addr), "i" (-EFAULT));

#ifdef CONFIG_CPU_HAS_ULS
#define     StoreW(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tswl\t%1, 3(%2)\n"              \
			"2:\tswr\t%1, (%2)\n\t"             \
			"li\t%0, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
		: "=r" (res)                                \
		: "r" (value), "r" (addr), "i" (-EFAULT));
#else
#define     StoreW(addr, value, res)  \
		__asm__ __volatile__ (                      \
			"1:\tor\t%0,%1,$0\n\t"              \
			"sb\t%0,0(%2)\n\t"                  \
			"srl\t%0,8\n\t"                     \
			"sb\t%0,1(%2)\n\t"                  \
			"srl\t%0,8\n\t"                     \
			"sb\t%0,2(%2)\n\t"                  \
			"srl\t%0,8\n\t"                     \
			"sb\t%0,3(%2)\n\t"                  \
			"li\t%0,0\n"                        \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			".previous"                         \
		: "=&r" (res)                               \
		: "r" (value), "r" (addr), "i" (-EFAULT));
#endif

#define     StoreDW(addr, value, res) \
		__asm__ __volatile__ (                      \
			"1:\tsdl\t%1, 7(%2)\n"              \
			"2:\tsdr\t%1, (%2)\n\t"             \
			"li\t%0, 0\n"                       \
			"3:\n\t"                            \
			".insn\n\t"                         \
			".section\t.fixup,\"ax\"\n\t"       \
			"4:\tli\t%0, %3\n\t"                \
			"j\t3b\n\t"                         \
			".previous\n\t"                     \
			".section\t__ex_table,\"a\"\n\t"    \
			STR(PTR)"\t1b, 4b\n\t"              \
			STR(PTR)"\t2b, 4b\n\t"              \
			".previous"                         \
		: "=r" (res)                                \
		: "r" (value), "r" (addr), "i" (-EFAULT));
#endif

static void emulate_load_store_insn(struct pt_regs *regs,
	void __user *addr, unsigned int __user *pc)
{
	union mips_instruction insn;
	unsigned long value;
	unsigned int res;
	unsigned long origpc;
	unsigned long orig31;
#ifdef CONFIG_CPU_HAS_FPU
	void __user *fault_addr = NULL;
#endif

	origpc = (unsigned long)pc;
	orig31 = regs->regs[31];

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

	/*
	 * This load never faults.
	 */
	__get_user(insn.word, pc);

	switch (insn.i_format.opcode) {
		/*
		 * These are instructions that a compiler doesn't generate.  We
		 * can assume therefore that the code is MIPS-aware and
		 * really buggy.  Emulating these instructions would break the
		 * semantics anyway.
		 */
	case ll_op:
	case lld_op:
	case sc_op:
	case scd_op:

		/*
		 * For these instructions the only way to create an address
		 * error is an attempted access to kernel/supervisor address
		 * space.
		 */
	case ldl_op:
	case ldr_op:
	case lwl_op:
	case lwr_op:
	case sdl_op:
	case sdr_op:
	case swl_op:
	case swr_op:
	case lb_op:
	case lbu_op:
	case sb_op:
		goto sigbus;

		/*
		 * The remaining opcodes are the ones that are really of
		 * interest.
		 */
	case lh_op:
		if (!access_ok(VERIFY_READ, addr, 2))
			goto sigbus;

		LoadHW(addr, value, res);
		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;

	case lw_op:
		if (!access_ok(VERIFY_READ, addr, 4))
			goto sigbus;

		LoadW(addr, value, res);
		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;

	case lhu_op:
		if (!access_ok(VERIFY_READ, addr, 2))
			goto sigbus;

		LoadHWU(addr, value, res);
		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;

	case sh_op:
		if (!access_ok(VERIFY_WRITE, addr, 2))
			goto sigbus;

		compute_return_epc(regs);
		value = regs->regs[insn.i_format.rt];
		StoreHW(addr, value, res);
		if (res)
			goto fault;
		break;

	case sw_op:
		if (!access_ok(VERIFY_WRITE, addr, 4))
			goto sigbus;

		compute_return_epc(regs);
		value = regs->regs[insn.i_format.rt];
		StoreW(addr, value, res);
		if (res)
			goto fault;
		break;

	case lwc1_op:
	case ldc1_op:
	case swc1_op:
	case sdc1_op:
#ifdef CONFIG_CPU_HAS_FPU
		die_if_kernel("Unaligned FP access in kernel code", regs);
		BUG_ON(!used_math());
		BUG_ON(!is_fpu_owner());

		lose_fpu(1);	/* Save FPU state for the emulator. */
		res = fpu_emulator_cop1Handler(regs, &current->thread.fpu, 1,
					       &fault_addr);
		own_fpu(1);	/* Restore FPU state. */

		/* Signal if something went wrong. */
		process_fpemu_return(res, fault_addr);

		if (res == 0)
			break;
		return;
#endif

	default:
		/*
		 * Pheeee...  We encountered an yet unknown instruction or
		 * cache coherence problem.  Die sucker, die ...
		 */
		goto sigill;
	}

#ifdef CONFIG_DEBUG_FS
	unaligned_instructions++;
#endif

	return;

fault:
	/* roll back jump/branch */
	regs->cp0_epc = origpc;
	regs->regs[31] = orig31;
	/* Did we have an exception handler installed? */
	if (fixup_exception(regs))
		return;

	die_if_kernel("Unhandled kernel unaligned access", regs);
	force_sig(SIGSEGV, current);

	return;

sigbus:
	die_if_kernel("Unhandled kernel unaligned access", regs);
	force_sig(SIGBUS, current);

	return;

sigill:
	die_if_kernel
	    ("Unhandled kernel unaligned access or invalid instruction", regs);
	force_sig(SIGILL, current);
}

/* Recode table from 16-bit register notation to 32-bit GPR. */
const int reg16to32[] = { 16, 17, 2, 3, 4, 5, 6, 7 };

/* Recode table from 16-bit STORE register notation to 32-bit GPR. */
const int reg16to32st[] = { 0, 17, 2, 3, 4, 5, 6, 7 };

static void emulate_load_store_MIPS16e(struct pt_regs *regs, void __user * addr)
{
	unsigned long value;
	unsigned int res;
	int reg;
	unsigned long orig31;
	u16 __user *pc16;
	unsigned long origpc;
	union mips16e_instruction mips16inst, oldinst;

	origpc = regs->cp0_epc;
	orig31 = regs->regs[31];
	pc16 = (unsigned short __user *)msk_isa16_mode(origpc);
	/*
	 * This load never faults.
	 */
	__get_user(mips16inst.full, pc16);
	oldinst = mips16inst;

	/* skip EXTEND instruction */
	if (mips16inst.ri.opcode == MIPS16e_extend_op) {
		pc16++;
		__get_user(mips16inst.full, pc16);
	} else if (delay_slot(regs)) {
		/*  skip jump instructions */
		/*  JAL/JALX are 32 bits but have OPCODE in first short int */
		if (mips16inst.ri.opcode == MIPS16e_jal_op)
			pc16++;
		pc16++;
		if (get_user(mips16inst.full, pc16))
			goto sigbus;
	}

	switch (mips16inst.ri.opcode) {
	case MIPS16e_swsp_op:
	case MIPS16e_lwpc_op:
	case MIPS16e_lwsp_op:
		reg = reg16to32[mips16inst.ri.rx];
		break;

	case MIPS16e_i8_op:
		if (mips16inst.i8.func != MIPS16e_swrasp_func)
			goto sigbus;
		reg = 29;	/* GPRSP */
		break;

	default:
		reg = reg16to32[mips16inst.rri.ry];
		break;
	}

	switch (mips16inst.ri.opcode) {

	case MIPS16e_lb_op:
	case MIPS16e_lbu_op:
	case MIPS16e_sb_op:
		goto sigbus;

	case MIPS16e_lh_op:
		if (!access_ok(VERIFY_READ, addr, 2))
			goto sigbus;

		LoadHW(addr, value, res);
		if (res)
			goto fault;
		MIPS16e_compute_return_epc(regs, &oldinst);
		regs->regs[reg] = value;
		break;

	case MIPS16e_lhu_op:
		if (!access_ok(VERIFY_READ, addr, 2))
			goto sigbus;

		LoadHWU(addr, value, res);
		if (res)
			goto fault;
		MIPS16e_compute_return_epc(regs, &oldinst);
		regs->regs[reg] = value;
		break;

	case MIPS16e_lw_op:
	case MIPS16e_lwpc_op:
	case MIPS16e_lwsp_op:
		if (!access_ok(VERIFY_READ, addr, 4))
			goto sigbus;

		LoadW(addr, value, res);
		if (res)
			goto fault;
		MIPS16e_compute_return_epc(regs, &oldinst);
		regs->regs[reg] = value;
		break;

	case MIPS16e_sh_op:
		if (!access_ok(VERIFY_WRITE, addr, 2))
			goto sigbus;

		MIPS16e_compute_return_epc(regs, &oldinst);
		value = regs->regs[reg];
		StoreHW(addr, value, res);
		if (res)
			goto fault;
		break;

	case MIPS16e_sw_op:
	case MIPS16e_swsp_op:
	case MIPS16e_i8_op:	/* actually - MIPS16e_swrasp_func */
		if (!access_ok(VERIFY_WRITE, addr, 4))
			goto sigbus;

		MIPS16e_compute_return_epc(regs, &oldinst);
		value = regs->regs[reg];
		StoreW(addr, value, res);
		if (res)
			goto fault;
		break;

	default:
		/*
		 * Pheeee...  We encountered an yet unknown instruction or
		 * cache coherence problem.  Die sucker, die ...
		 */
		goto sigill;
	}

#ifdef CONFIG_DEBUG_FS
	unaligned_instructions++;
#endif

	return;

fault:
	/* roll back jump/branch */
	regs->cp0_epc = origpc;
	regs->regs[31] = orig31;
	/* Did we have an exception handler installed? */
	if (fixup_exception(regs))
		return;

	die_if_kernel("Unhandled kernel unaligned access", regs);
	force_sig(SIGSEGV, current);

	return;

sigbus:
	die_if_kernel("Unhandled kernel unaligned access", regs);
	force_sig(SIGBUS, current);

	return;

sigill:
	die_if_kernel
	    ("Unhandled kernel unaligned access or invalid instruction", regs);
	force_sig(SIGILL, current);
}

asmlinkage void do_ade(struct pt_regs *regs)
{
	enum ctx_state prev_state;
	unsigned int __user *pc;
	mm_segment_t seg;

	prev_state = exception_enter();
	perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS,
			1, regs, regs->cp0_badvaddr);
	/*
	 * Did we catch a fault trying to load an instruction?
	 */
	if (regs->cp0_badvaddr == regs->cp0_epc)
		goto sigbus;

	if (user_mode(regs) && !test_thread_flag(TIF_FIXADE))
		goto sigbus;
	if (unaligned_action == UNALIGNED_ACTION_SIGNAL)
		goto sigbus;

	/*
	 * Do branch emulation only if we didn't forward the exception.
	 * This is all so but ugly ...
	 */

	/*
	 * Are we running in MIPS16 mode?
	 */
	if (get_isa16_mode(regs->cp0_epc)) {
		/*
		 * Did we catch a fault trying to load an instruction in
		 * 16-bit mode?
		 */
		if (regs->cp0_badvaddr == msk_isa16_mode(regs->cp0_epc))
			goto sigbus;
		if (unaligned_action == UNALIGNED_ACTION_SHOW)
			show_registers(regs);

		if (cpu_has_mips16) {
			seg = get_fs();
			if (!user_mode(regs))
				set_fs(KERNEL_DS);
			emulate_load_store_MIPS16e(regs,
				(void __user *)regs->cp0_badvaddr);
			set_fs(seg);

			return;
		}

		goto sigbus;
	}

	if (unaligned_action == UNALIGNED_ACTION_SHOW)
		show_registers(regs);
	pc = (unsigned int __user *)exception_epc(regs);

	seg = get_fs();
	if (!user_mode(regs))
		set_fs(KERNEL_DS);
	emulate_load_store_insn(regs, (void __user *)regs->cp0_badvaddr, pc);
	set_fs(seg);

	return;

sigbus:
	die_if_kernel("Kernel unaligned instruction access", regs);
	force_sig(SIGBUS, current);

	/*
	 * XXX On return from the signal handler we should advance the epc
	 */
	exception_exit(prev_state);
}

#ifdef CONFIG_DEBUG_FS
extern struct dentry *mips_debugfs_dir;
static int __init debugfs_unaligned(void)
{
	struct dentry *d;

	if (!mips_debugfs_dir)
		return -ENODEV;
	d = debugfs_create_u32("unaligned_instructions", S_IRUGO,
			       mips_debugfs_dir, &unaligned_instructions);
	if (!d)
		return -ENOMEM;
	d = debugfs_create_u32("unaligned_action", S_IRUGO | S_IWUSR,
			       mips_debugfs_dir, &unaligned_action);
	if (!d)
		return -ENOMEM;
	return 0;
}
__initcall(debugfs_unaligned);
#endif
