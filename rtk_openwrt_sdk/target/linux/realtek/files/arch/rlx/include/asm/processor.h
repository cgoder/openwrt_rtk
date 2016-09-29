/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 Waldorf GMBH
 * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Ralf Baechle
 * Copyright (C) 1996 Paul M. Antoine
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#ifndef _ASM_PROCESSOR_H
#define _ASM_PROCESSOR_H

#include <linux/cpumask.h>
#include <linux/threads.h>

#include <asm/cachectl.h>
#include <asm/cpu.h>
#include <asm/cpu-info.h>
#include <asm/rlxregs.h>
#include <asm/prefetch.h>

/*
 * Return current * instruction pointer ("program counter").
 */
#define current_text_addr() ({ __label__ _l; _l: &&_l;})

/*
 * MIPS does have an arch_pick_mmap_layout()
 */
#define HAVE_ARCH_PICK_MMAP_LAYOUT 1

/*
 * A special page (the vdso) is mapped into all processes at the very
 * top of the virtual memory space.
 */
#define SPECIAL_PAGES_SIZE PAGE_SIZE

#ifdef CONFIG_32BIT
#ifdef CONFIG_KVM_GUEST
/* User space process size is limited to 1GB in KVM Guest Mode */
#define TASK_SIZE	0x3fff8000UL
#else
/*
 * User space process size: 2GB. This is hardcoded into a few places,
 * so don't change it unless you know what you are doing.
 */
#define TASK_SIZE	0x7fff8000UL
#endif

#ifdef __KERNEL__
#define STACK_TOP_MAX	TASK_SIZE
#endif

#define TASK_IS_32BIT_ADDR 1

#endif

#ifdef CONFIG_64BIT
/*
 * User space process size: 1TB. This is hardcoded into a few places,
 * so don't change it unless you know what you are doing.  TASK_SIZE
 * is limited to 1TB by the R4000 architecture; R10000 and better can
 * support 16TB; the architectural reserve for future expansion is
 * 8192EB ...
 */
#define TASK_SIZE32	0x7fff8000UL
#define TASK_SIZE64	0x10000000000UL
#define TASK_SIZE (test_thread_flag(TIF_32BIT_ADDR) ? TASK_SIZE32 : TASK_SIZE64)

#ifdef __KERNEL__
#define STACK_TOP_MAX	TASK_SIZE64
#endif


#define TASK_SIZE_OF(tsk)						\
	(test_tsk_thread_flag(tsk, TIF_32BIT_ADDR) ? TASK_SIZE32 : TASK_SIZE64)

#define TASK_IS_32BIT_ADDR test_thread_flag(TIF_32BIT_ADDR)

#endif

#define STACK_TOP	((TASK_SIZE & PAGE_MASK) - SPECIAL_PAGES_SIZE)

/*
 * This decides where the kernel will search for a free chunk of vm
 * space during mmap's.
 */
#define TASK_UNMAPPED_BASE PAGE_ALIGN(TASK_SIZE / 3)


#define NUM_FPU_REGS	32

typedef __u64 fpureg_t;

/*
 * It would be nice to add some more fields for emulator statistics, but there
 * are a number of fixed offsets in offset.h and elsewhere that would have to
 * be recalculated by hand.  So the additional information will be private to
 * the FPU emulator for now.  See asm-mips/fpu_emulator.h.
 */

struct mips_fpu_struct {
	fpureg_t	fpr[NUM_FPU_REGS];
	unsigned int	fcr31;
};

#define INIT_CPUMASK { \
	{0,} \
}


#ifdef CONFIG_CPU_HAS_RADIAX
#define NUM_RADIAX_REGS    26

typedef __u32 radiaxreg_t;

struct mips_radiax_struct {
	radiaxreg_t radiaxr[NUM_RADIAX_REGS];
};
#endif

#ifdef CONFIG_CPU_HAS_WMPU
struct mips3264_watch_reg_state {
	/* The width of watchlo is 32 in a 32 bit kernel and 64 in a
	   64 bit kernel.  We use unsigned long as it has the same
	   property. */
	unsigned long watchlo[NUM_WATCH_REGS];
	/* Only the mask and IRW bits from watchhi. */
	u16 watchhi[NUM_WATCH_REGS];
	unsigned long wmpxmask[NUM_WATCH_REGS];
	unsigned long wmpvaddr;
};

union mips_watch_reg_state {
	struct mips3264_watch_reg_state mips3264;
};
#endif

typedef struct {
	unsigned long seg;
} mm_segment_t;

#define ARCH_MIN_TASKALIGN	8

struct mips_abi;

/*
 * If you change thread_struct remember to change the #defines below too!
 */
struct thread_struct {
	/* Saved main processor registers. */
	unsigned long reg16;
	unsigned long reg17, reg18, reg19, reg20, reg21, reg22, reg23;
	unsigned long reg29, reg30, reg31;

	/* Saved cp0 stuff. */
	unsigned long cp0_status;

#ifdef CONFIG_CPU_HAS_FPU
	/* Saved fpu/fpu emulator stuff. */
	struct mips_fpu_struct fpu;
#endif

#ifdef CONFIG_CPU_HAS_WMPU
	/* Saved watch register state, if available. */
	union mips_watch_reg_state watch;
#endif

#ifdef CONFIG_CPU_HAS_RADIAX
	/* Saved radiax register state, if available. */
        struct mips_radiax_struct radiax;
#endif

	/* Other stuff associated with the thread. */
	unsigned long cp0_badvaddr;	/* Last user fault */
	unsigned long cp0_baduaddr;	/* Last kernel fault accessing USEG */
	unsigned long error_code;
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	struct octeon_cop2_state cp2 __attribute__ ((__aligned__(128)));
	struct octeon_cvmseg_state cvmseg __attribute__ ((__aligned__(128)));
#endif
	struct mips_abi *abi;
};

#ifdef CONFIG_CPU_HAS_WMPU
#define INIT_WATCH	.watch = {{{0,},},},
#else
#define INIT_WATCH
#endif

#ifdef CONFIG_CPU_HAS_FPU
#define INIT_FPU	.fpu = { \
				.fpr   = {0,},	\
				.fcr31 = 0,	\
			},
#else
#define INIT_FPU
#endif

#ifdef CONFIG_CPU_HAS_RADIAX
#define INIT_RADIAX	.radiax = {{0,},},
#else
#define INIT_RADIAX
#endif

#define INIT_THREAD  {						\
	/*							\
	 * Saved main processor registers			\
	 */							\
	.reg16			= 0,				\
	.reg17			= 0,				\
	.reg18			= 0,				\
	.reg19			= 0,				\
	.reg20			= 0,				\
	.reg21			= 0,				\
	.reg22			= 0,				\
	.reg23			= 0,				\
	.reg29			= 0,				\
	.reg30			= 0,				\
	.reg31			= 0,				\
	/*							\
	 * Saved cp0 stuff					\
	 */							\
	.cp0_status		= 0,				\
	/*							\
	 * Saved FPU/FPU emulator stuff				\
	 */							\
	INIT_FPU						\
	/*							\
	 * saved watch register stuff				\
	 */							\
	INIT_WATCH						\
	/*							\
	 * saved radiax register stuff				\
	 */							\
	INIT_RADIAX						\
	/*							\
	 * Other stuff associated with the process		\
	 */							\
	.cp0_badvaddr		= 0,				\
	.cp0_baduaddr		= 0,				\
	.error_code		= 0,				\
}

struct task_struct;

/* Free all resources held by a thread. */
#define release_thread(thread) do { } while(0)

extern unsigned long thread_saved_pc(struct task_struct *tsk);

/*
 * Do necessary setup to start up a newly executed thread.
 */
extern void start_thread(struct pt_regs * regs, unsigned long pc, unsigned long sp);

unsigned long get_wchan(struct task_struct *p);

#define __KSTK_TOS(tsk) ((unsigned long)task_stack_page(tsk) + \
			 THREAD_SIZE - 32 - sizeof(struct pt_regs))
#define task_pt_regs(tsk) ((struct pt_regs *)__KSTK_TOS(tsk))
#define KSTK_EIP(tsk) (task_pt_regs(tsk)->cp0_epc)
#define KSTK_ESP(tsk) (task_pt_regs(tsk)->regs[29])
#define KSTK_STATUS(tsk) (task_pt_regs(tsk)->cp0_status)

#define cpu_relax()	barrier()

/*
 * Return_address is a replacement for __builtin_return_address(count)
 * which on certain architectures cannot reasonably be implemented in GCC
 * (MIPS, Alpha) or is unusable with -fomit-frame-pointer (i386).
 * Note that __builtin_return_address(x>=1) is forbidden because GCC
 * aborts compilation on some CPUs.  It's simply not possible to unwind
 * some CPU's stackframes.
 *
 * __builtin_return_address works only for non-leaf functions.	We avoid the
 * overhead of a function call by forcing the compiler to save the return
 * address register on the stack.
 */
#define return_address() ({__asm__ __volatile__("":::"$31");__builtin_return_address(0);})

#ifdef CONFIG_CPU_HAS_PREFETCH

#define ARCH_HAS_PREFETCH
#define prefetch(x) __builtin_prefetch((x), 0, 1)

#define ARCH_HAS_PREFETCHW
#define prefetchw(x) __builtin_prefetch((x), 1, 1)

/*
 * See Documentation/scheduler/sched-arch.txt; prevents deadlock on SMP
 * systems.
 */
#define __ARCH_WANT_UNLOCKED_CTXSW

#endif

#endif /* _ASM_PROCESSOR_H */
