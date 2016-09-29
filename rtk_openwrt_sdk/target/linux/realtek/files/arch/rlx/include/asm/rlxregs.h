/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994, 1995, 1996, 1997, 2000, 2001 by Ralf Baechle
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Modified for further R[236]000 support by Paul M. Antoine, 1996.
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 */
#ifndef _ASM_RLXREGS_H_
#define _ASM_RLXREGS_H_

#include <linux/linkage.h>
#include <asm/hazards.h>

/*
 * The following macros are especially useful for __asm__
 * inline assembler.
 */
#ifndef __STR
#define __STR(x) #x
#endif
#ifndef STR
#define STR(x) __STR(x)
#endif

/*
 *  Configure language
 */
#ifdef __ASSEMBLY__
#define _ULCAST_
#else
#define _ULCAST_ (unsigned long)
#endif

/*
 * Coprocessor 0 register names
 */
#define CP0_INDEX $0
#define CP0_RANDOM $1
#define CP0_ENTRYLO0 $2
#define CP0_ENTRYLO1 $3
#define CP0_CONF $3
#define CP0_CONTEXT $4
#define CP0_PAGEMASK $5
#define CP0_WIRED $6
#define CP0_INFO $7
#define CP0_BADVADDR $8
#define CP0_COUNT $9
#define CP0_ENTRYHI $10
#define CP0_COMPARE $11
#define CP0_STATUS $12
#define CP0_CAUSE $13
#define CP0_EPC $14
#define CP0_PRID $15
#define CP0_CONFIG $16
#define CP0_LLADDR $17
#define CP0_WATCHLO $18
#define CP0_WATCHHI $19
#define CP0_XCONTEXT $20
#define CP0_FRAMEMASK $21
#define CP0_DIAGNOSTIC $22
#define CP0_DEBUG $23
#define CP0_DEPC $24
#define CP0_PERFORMANCE $25
#define CP0_ECC $26
#define CP0_CACHEERR $27
#define CP0_TAGLO $28
#define CP0_TAGHI $29
#define CP0_ERROREPC $30
#define CP0_DESAVE $31

/*
 * Coprocessor 1 (FPU) register names
 */
#define CP1_REVISION   $0
#define CP1_STATUS     $31

/*
 * FPU Status Register Values
 */
/*
 * Status Register Values
 */

#define FPU_CSR_FLUSH   0x01000000      /* flush denormalised results to 0 */
#define FPU_CSR_COND    0x00800000      /* $fcc0 */
#define FPU_CSR_COND0   0x00800000      /* $fcc0 */
#define FPU_CSR_COND1   0x02000000      /* $fcc1 */
#define FPU_CSR_COND2   0x04000000      /* $fcc2 */
#define FPU_CSR_COND3   0x08000000      /* $fcc3 */
#define FPU_CSR_COND4   0x10000000      /* $fcc4 */
#define FPU_CSR_COND5   0x20000000      /* $fcc5 */
#define FPU_CSR_COND6   0x40000000      /* $fcc6 */
#define FPU_CSR_COND7   0x80000000      /* $fcc7 */

/*
 * Bits 18 - 20 of the FPU Status Register will be read as 0,
 * and should be written as zero.
 */
#define FPU_CSR_RSVD	0x001c0000

/*
 * X the exception cause indicator
 * E the exception enable
 * S the sticky/flag bit
*/
#define FPU_CSR_ALL_X   0x0003f000
#define FPU_CSR_UNI_X   0x00020000
#define FPU_CSR_INV_X   0x00010000
#define FPU_CSR_DIV_X   0x00008000
#define FPU_CSR_OVF_X   0x00004000
#define FPU_CSR_UDF_X   0x00002000
#define FPU_CSR_INE_X   0x00001000

#define FPU_CSR_ALL_E   0x00000f80
#define FPU_CSR_INV_E   0x00000800
#define FPU_CSR_DIV_E   0x00000400
#define FPU_CSR_OVF_E   0x00000200
#define FPU_CSR_UDF_E   0x00000100
#define FPU_CSR_INE_E   0x00000080

#define FPU_CSR_ALL_S   0x0000007c
#define FPU_CSR_INV_S   0x00000040
#define FPU_CSR_DIV_S   0x00000020
#define FPU_CSR_OVF_S   0x00000010
#define FPU_CSR_UDF_S   0x00000008
#define FPU_CSR_INE_S   0x00000004

/* Bits 0 and 1 of FPU Status Register specify the rounding mode */
#define FPU_CSR_RM	0x00000003
#define FPU_CSR_RN      0x0     /* nearest */
#define FPU_CSR_RZ      0x1     /* towards zero */
#define FPU_CSR_RU      0x2     /* towards +Infinity */
#define FPU_CSR_RD      0x3     /* towards -Infinity */

#define PM_4K		0x00000000
#define PM_DEFAULT_MASK	PM_4K
#define PL_4K		12

/*
 * Setting c0_status.co enables Hit_Writeback and Hit_Writeback_Invalidate
 * cacheops in userspace.  This bit exists only on RM7000 and RM9000
 * processors.
 */
#define ST0_CO			0x08000000

/*
 * Bitfields in the R[23]000 cp0 status register.
 */
#define ST0_IEC                 0x00000001
#define ST0_KUC			0x00000002
#define ST0_IEP			0x00000004
#define ST0_KUP			0x00000008
#define ST0_IEO			0x00000010
#define ST0_KUO			0x00000020
/* bits 6 & 7 are reserved on R[23]000 */
#define ST0_ISC			0x00010000
#define ST0_SWC			0x00020000
#define ST0_CM			0x00080000

/*
 * Status register bits available in all MIPS CPUs.
 */
#define ST0_IM			0x0000ff00
#define  STATUSB_IP0		8
#define  STATUSF_IP0		(_ULCAST_(1) <<  8)
#define  STATUSB_IP1		9
#define  STATUSF_IP1		(_ULCAST_(1) <<  9)
#define  STATUSB_IP2		10
#define  STATUSF_IP2		(_ULCAST_(1) << 10)
#define  STATUSB_IP3		11
#define  STATUSF_IP3		(_ULCAST_(1) << 11)
#define  STATUSB_IP4		12
#define  STATUSF_IP4		(_ULCAST_(1) << 12)
#define  STATUSB_IP5		13
#define  STATUSF_IP5		(_ULCAST_(1) << 13)
#define  STATUSB_IP6		14
#define  STATUSF_IP6		(_ULCAST_(1) << 14)
#define  STATUSB_IP7		15
#define  STATUSF_IP7		(_ULCAST_(1) << 15)
#define  STATUSB_IP8		0
#define  STATUSF_IP8		(_ULCAST_(1) <<  0)
#define  STATUSB_IP9		1
#define  STATUSF_IP9		(_ULCAST_(1) <<  1)
#define  STATUSB_IP10		2
#define  STATUSF_IP10		(_ULCAST_(1) <<  2)
#define  STATUSB_IP11		3
#define  STATUSF_IP11		(_ULCAST_(1) <<  3)
#define  STATUSB_IP12		4
#define  STATUSF_IP12		(_ULCAST_(1) <<  4)
#define  STATUSB_IP13		5
#define  STATUSF_IP13		(_ULCAST_(1) <<  5)
#define  STATUSB_IP14		6
#define  STATUSF_IP14		(_ULCAST_(1) <<  6)
#define  STATUSB_IP15		7
#define  STATUSF_IP15		(_ULCAST_(1) <<  7)
#define ST0_CH			0x00040000
#define ST0_SR			0x00100000
#define ST0_TS			0x00200000
#define ST0_BEV			0x00400000
#define ST0_RE			0x02000000
#define ST0_FR			0x04000000
#define ST0_CU			0xf0000000
#define ST0_CU0			0x10000000
#define ST0_CU1			0x20000000
#define ST0_CU2			0x40000000
#define ST0_CU3			0x80000000
#define ST0_XX			0x80000000	/* MIPS IV naming */

/*
 * Bitfields and bit numbers in the coprocessor 0 cause register.
 *
 * Refer to your MIPS R4xx0 manual, chapter 5 for explanation.
 */
#define  CAUSEB_EXCCODE		2
#define  CAUSEF_EXCCODE		(_ULCAST_(31)  <<  2)
#define  CAUSEB_IP		8
#define  CAUSEF_IP		(_ULCAST_(255) <<  8)
#define  CAUSEB_IP0		8
#define  CAUSEF_IP0		(_ULCAST_(1)   <<  8)
#define  CAUSEB_IP1		9
#define  CAUSEF_IP1		(_ULCAST_(1)   <<  9)
#define  CAUSEB_IP2		10
#define  CAUSEF_IP2		(_ULCAST_(1)   << 10)
#define  CAUSEB_IP3		11
#define  CAUSEF_IP3		(_ULCAST_(1)   << 11)
#define  CAUSEB_IP4		12
#define  CAUSEF_IP4		(_ULCAST_(1)   << 12)
#define  CAUSEB_IP5		13
#define  CAUSEF_IP5		(_ULCAST_(1)   << 13)
#define  CAUSEB_IP6		14
#define  CAUSEF_IP6		(_ULCAST_(1)   << 14)
#define  CAUSEB_IP7		15
#define  CAUSEF_IP7		(_ULCAST_(1)   << 15)
#define  CAUSEB_IV		23
#define  CAUSEF_IV		(_ULCAST_(1)   << 23)
#define  CAUSEB_DC		27
#define  CAUSEF_DC		(_ULCAST_(1)   << 27)
#define  CAUSEB_CE		28
#define  CAUSEF_CE		(_ULCAST_(3)   << 28)
#define  CAUSEB_TI		30
#define  CAUSEF_TI		(_ULCAST_(1)   << 30)
#define  CAUSEB_BD		31
#define  CAUSEF_BD		(_ULCAST_(1)   << 31)

#ifndef __ASSEMBLY__

/*
 * Macros for handling the ISA mode bit for MIPS16.
 */
#define get_isa16_mode(x)		((x) & 0x1)
#define msk_isa16_mode(x)		((x) & ~0x1)
#define set_isa16_mode(x)		do { (x) |= 0x1; } while(0)

/*
 * Macros to access the system control coprocessor
 */

#if defined(CONFIG_CPU_RLX5281) || defined(CONFIG_CPU_RLX4281)
#define __read_32bit_c0_register(source, sel)				\
({ int __res;								\
	__asm__ __volatile__(						\
		"mfc0\t%0, " #source ", " #sel "\n\t"			\
		: "=r" (__res));					\
	__res;								\
})
#else
#define __read_32bit_c0_register(source, sel)				\
({ int __res;								\
	__asm__ __volatile__(						\
		"mfc0\t%0, " #source "\n\t"				\
		: "=r" (__res));					\
	__res;								\
})
#endif

#if defined(CONFIG_CPU_RLX5281) || defined(CONFIG_CPU_RLX4281)
#define __write_32bit_c0_register(register, sel, value)			\
do {									\
	__asm__ __volatile__(						\
		"mtc0\t%z0, " #register ", " #sel "\n\t"		\
		: : "Jr" ((unsigned int)(value)));			\
} while (0)
#else
#define __write_32bit_c0_register(register, sel, value)			\
do {									\
	__asm__ __volatile__(						\
		"mtc0\t%z0, " #register "\n\t"				\
		: : "Jr" ((unsigned int)(value)));			\
} while (0)
#endif

#define __read_ulong_c0_register(reg, sel)				\
	(unsigned long) __read_32bit_c0_register(reg, sel)

#define __write_ulong_c0_register(reg, sel, val)			\
do {									\
	__write_32bit_c0_register(reg, sel, val);			\
} while (0)

#define read_c0_index()		__read_32bit_c0_register($0, 0)
#define write_c0_index(val)	__write_32bit_c0_register($0, 0, val)

#define read_c0_entrylo()	__read_ulong_c0_register($2, 0)
#define write_c0_entrylo(val)	__write_ulong_c0_register($2, 0, val)

#define read_c0_context()	__read_ulong_c0_register($4, 0)
#define write_c0_context(val)	__write_ulong_c0_register($4, 0, val)

#define read_c0_wired()		__read_32bit_c0_register($6, 0)
#define write_c0_wired(val)	__write_32bit_c0_register($6, 0, val)

#define read_c0_info()		__read_32bit_c0_register($7, 0)

#define read_c0_badvaddr()	__read_ulong_c0_register($8, 0)
#define write_c0_badvaddr(val)	__write_ulong_c0_register($8, 0, val)

#define read_c0_count()		__read_32bit_c0_register($9, 0)
#define write_c0_count(val)	__write_32bit_c0_register($9, 0, val)

#define read_c0_entryhi()	__read_ulong_c0_register($10, 0)
#define write_c0_entryhi(val)	__write_ulong_c0_register($10, 0, val)

#define read_c0_compare()	__read_32bit_c0_register($11, 0)
#define write_c0_compare(val)	__write_32bit_c0_register($11, 0, val)

#define read_c0_status()	__read_32bit_c0_register($12, 0)
#define write_c0_status(val)	__write_32bit_c0_register($12, 0, val)

#define read_c0_cause()		__read_32bit_c0_register($13, 0)
#define write_c0_cause(val)	__write_32bit_c0_register($13, 0, val)

#define read_c0_epc()		__read_ulong_c0_register($14, 0)
#define write_c0_epc(val)	__write_ulong_c0_register($14, 0, val)

#define read_c0_prid()		__read_32bit_c0_register($15, 0)

/*
 * The WatchLo register.  There may be upto 8 of them.
 */
#define read_c0_watchlo0()	__read_ulong_c0_register($18, 0)
#define read_c0_watchlo1()	__read_ulong_c0_register($18, 1)
#define read_c0_watchlo2()	__read_ulong_c0_register($18, 2)
#define read_c0_watchlo3()	__read_ulong_c0_register($18, 3)
#define read_c0_watchlo4()	__read_ulong_c0_register($18, 4)
#define read_c0_watchlo5()	__read_ulong_c0_register($18, 5)
#define read_c0_watchlo6()	__read_ulong_c0_register($18, 6)
#define read_c0_watchlo7()	__read_ulong_c0_register($18, 7)

#define write_c0_watchlo0(val)	__write_ulong_c0_register($18, 0, val)
#define write_c0_watchlo1(val)	__write_ulong_c0_register($18, 1, val)
#define write_c0_watchlo2(val)	__write_ulong_c0_register($18, 2, val)
#define write_c0_watchlo3(val)	__write_ulong_c0_register($18, 3, val)
#define write_c0_watchlo4(val)	__write_ulong_c0_register($18, 4, val)
#define write_c0_watchlo5(val)	__write_ulong_c0_register($18, 5, val)
#define write_c0_watchlo6(val)	__write_ulong_c0_register($18, 6, val)
#define write_c0_watchlo7(val)	__write_ulong_c0_register($18, 7, val)

/*
 * The WatchHi register.  There may be upto 8 of them.
 */
#define read_c0_watchhi0()	__read_32bit_c0_register($19, 0)
#define read_c0_watchhi1()	__read_32bit_c0_register($19, 1)
#define read_c0_watchhi2()	__read_32bit_c0_register($19, 2)
#define read_c0_watchhi3()	__read_32bit_c0_register($19, 3)
#define read_c0_watchhi4()	__read_32bit_c0_register($19, 4)
#define read_c0_watchhi5()	__read_32bit_c0_register($19, 5)
#define read_c0_watchhi6()	__read_32bit_c0_register($19, 6)
#define read_c0_watchhi7()	__read_32bit_c0_register($19, 7)

#define write_c0_watchhi0(val)	__write_32bit_c0_register($19, 0, val)
#define write_c0_watchhi1(val)	__write_32bit_c0_register($19, 1, val)
#define write_c0_watchhi2(val)	__write_32bit_c0_register($19, 2, val)
#define write_c0_watchhi3(val)	__write_32bit_c0_register($19, 3, val)
#define write_c0_watchhi4(val)	__write_32bit_c0_register($19, 4, val)
#define write_c0_watchhi5(val)	__write_32bit_c0_register($19, 5, val)
#define write_c0_watchhi6(val)	__write_32bit_c0_register($19, 6, val)
#define write_c0_watchhi7(val)	__write_32bit_c0_register($19, 7, val)

#define read_c0_xcontext()	__read_ulong_c0_register($20, 0)
#define write_c0_xcontext(val)	__write_ulong_c0_register($20, 0, val)

#define read_c0_intcontrol()	__read_32bit_c0_ctrl_register($20, 0)
#define write_c0_intcontrol(val) __write_32bit_c0_ctrl_register($20, 0, val)

#define read_c0_framemask()	__read_32bit_c0_register($21, 0)
#define write_c0_framemask(val)	__write_32bit_c0_register($21, 0, val)

#define read_lxc0_userlocal()		__read_32bit_lxc0_register($8, 0)
#define write_lxc0_userlocal(val)	__write_32bit_lxc0_register($8, 0, val)

#define mfhi0()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mfhi	%0, $ac0		\n"			\
	"	.word	0x00000810		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mfhi1()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mfhi	%0, $ac1		\n"			\
	"	.word	0x00200810		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mfhi2()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mfhi	%0, $ac2		\n"			\
	"	.word	0x00400810		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mfhi3()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mfhi	%0, $ac3		\n"			\
	"	.word	0x00600810		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mflo0()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mflo	%0, $ac0		\n"			\
	"	.word	0x00000812		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mflo1()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mflo	%0, $ac1		\n"			\
	"	.word	0x00200812		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mflo2()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mflo	%0, $ac2		\n"			\
	"	.word	0x00400812		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mflo3()								\
({									\
	unsigned long __treg;						\
									\
	__asm__ __volatile__(						\
	"	.set	push			\n"			\
	"	.set	noat			\n"			\
	"	# mflo	%0, $ac3		\n"			\
	"	.word	0x00600812		\n"			\
	"	move	%0, $1			\n"			\
	"	.set	pop			\n"			\
	: "=r" (__treg));						\
	__treg;								\
})

#define mthi0(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mthi	$1, $ac0				\n"	\
	"	.word	0x00200011				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mthi1(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mthi	$1, $ac1				\n"	\
	"	.word	0x00200811				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mthi2(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mthi	$1, $ac2				\n"	\
	"	.word	0x00201011				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mthi3(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mthi	$1, $ac3				\n"	\
	"	.word	0x00201811				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mtlo0(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mtlo	$1, $ac0				\n"	\
	"	.word	0x00200013				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mtlo1(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mtlo	$1, $ac1				\n"	\
	"	.word	0x00200813				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mtlo2(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mtlo	$1, $ac2				\n"	\
	"	.word	0x00201013				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

#define mtlo3(x)							\
do {									\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mtlo	$1, $ac3				\n"	\
	"	.word	0x00201813				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (x));							\
} while (0)

/*
 * TLB operations.
 *
 * It is responsibility of the caller to take care of any TLB hazards.
 */
static inline void tlb_probe(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbp\n\t"
		".set reorder");
}

static inline void tlb_read(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbr\n\t"
		".set reorder");
}

static inline void tlb_write_indexed(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbwi\n\t"
		".set reorder");
}

static inline void tlb_write_random(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbwr\n\t"
		".set reorder");
}

/*
 * Manipulate bits in a c0 register.
 */
#define __BUILD_SET_C0(name)					\
static inline unsigned int					\
set_c0_##name(unsigned int set)					\
{								\
	unsigned int res;					\
								\
	res = read_c0_##name();					\
	res |= set;						\
	write_c0_##name(res);					\
								\
	return res;						\
}								\
								\
static inline unsigned int					\
clear_c0_##name(unsigned int clear)				\
{								\
	unsigned int res;					\
								\
	res = read_c0_##name();					\
	res &= ~clear;						\
	write_c0_##name(res);					\
								\
	return res;						\
}								\
								\
static inline unsigned int					\
change_c0_##name(unsigned int change, unsigned int new)		\
{								\
	unsigned int res;					\
								\
	res = read_c0_##name();					\
	res &= ~change;						\
	res |= (new & change);					\
	write_c0_##name(res);					\
								\
	return res;						\
}

__BUILD_SET_C0(status)
__BUILD_SET_C0(cause)

#endif /* !__ASSEMBLY__ */

/*
 * RLX CP0 register names
 */
#define LXCP0_ESTATUS		$0
#define LXCP0_ECAUSE		$1
#define LXCP0_INTVEC		$2
#define LXCP0_CVSTAG		$3
#define LXCP0_BPCTL		$4
#define LXCP0_WMPCTL		$5
#define LXCP0_WMPSTATUS		$6
#define LXCP0_WMPVADDR		$7
#define LXCP0_TLPTR		$8
#define LXCP0_WMPEXTRAMASK	$19
#define LXCP0_CCTL		$20

#define CCTL_DInval		0x00000001
#define CCTL_IInval		0x00000002
#define CCTL_IMEM0FILL		0x00000010
#define CCTL_IMEM0OFF		0x00000020
#define CCTL_IMEM0ON		0x00000040
#define CCTL_DWB		0x00000100
#define CCTL_DWBInval		0x00000200
#define CCTL_DMEM0ON		0x00000400
#define CCTL_DMEM0OFF		0x00000800

/*
 * RLX status register bits
 */
#define EST0_IM			0x00ff0000
#define ESTATUSF_IP0		(_ULCAST_(1) << 16)
#define ESTATUSF_IP1		(_ULCAST_(1) << 17)
#define ESTATUSF_IP2		(_ULCAST_(1) << 18)
#define ESTATUSF_IP3		(_ULCAST_(1) << 19)
#define ESTATUSF_IP4		(_ULCAST_(1) << 20)
#define ESTATUSF_IP5		(_ULCAST_(1) << 21)
#define ESTATUSF_IP6		(_ULCAST_(1) << 22)
#define ESTATUSF_IP7		(_ULCAST_(1) << 23)

#define ECAUSEF_IP		(_ULCAST_(255) << 16)
#define ECAUSEF_IP0		(_ULCAST_(1)   << 16)
#define ECAUSEF_IP1		(_ULCAST_(1)   << 17)
#define ECAUSEF_IP2		(_ULCAST_(1)   << 18)
#define ECAUSEF_IP3		(_ULCAST_(1)   << 19)
#define ECAUSEF_IP4		(_ULCAST_(1)   << 20)
#define ECAUSEF_IP5		(_ULCAST_(1)   << 21)
#define ECAUSEF_IP6		(_ULCAST_(1)   << 22)
#define ECAUSEF_IP7		(_ULCAST_(1)   << 23)

/*
 * WMPU CTRL register
 */
#define WMPCTLF_MS		(_ULCAST_(1) << 0)
#define WMPCTLF_KE		(_ULCAST_(1) << 1)

#define WMPCTLF_EE0		(_ULCAST_(1) << 16)
#define WMPCTLF_EE1		(_ULCAST_(1) << 17)
#define WMPCTLF_EE2		(_ULCAST_(1) << 18)
#define WMPCTLF_EE3		(_ULCAST_(1) << 19)
#define WMPCTLF_EE4		(_ULCAST_(1) << 20)
#define WMPCTLF_EE5		(_ULCAST_(1) << 21)
#define WMPCTLF_EE6		(_ULCAST_(1) << 22)
#define WMPCTLF_EE7		(_ULCAST_(1) << 23)

/*
 * WMPU status register
 */
#define WMPSTATUSF_II		(_ULCAST_(1) << 0)
#define WMPSTATUSF_DR		(_ULCAST_(1) << 1)
#define WMPSTATUSF_DW		(_ULCAST_(1) << 2)

#define WMPSTATUSF_EM0		(_ULCAST_(1) << 16)
#define WMPSTATUSF_EM1		(_ULCAST_(1) << 17)
#define WMPSTATUSF_EM2		(_ULCAST_(1) << 18)
#define WMPSTATUSF_EM3		(_ULCAST_(1) << 19)
#define WMPSTATUSF_EM4		(_ULCAST_(1) << 20)
#define WMPSTATUSF_EM5		(_ULCAST_(1) << 21)
#define WMPSTATUSF_EM6		(_ULCAST_(1) << 22)
#define WMPSTATUSF_EM7		(_ULCAST_(1) << 23)

#ifndef __ASSEMBLY__

/*
 * Macros to access the system control coprocessor
 */

#define __read_32bit_lxc0_register(source, sel)			\
({ int __res;							\
 	if (sel == 0)						\
		__asm__ __volatile__(				\
			"mflxc0\t%0, " #source "\n\t"		\
			: "=r" (__res));			\
 	else							\
		__asm__ __volatile__(				\
			"mflxc0\t%0, " #source ", " #sel "\n\t"	\
			: "=r" (__res));			\
	__res;							\
})

#define __write_32bit_lxc0_register(target, sel, value)		\
do {								\
	if (sel == 0)						\
		__asm__ __volatile__(				\
			"mtlxc0\t%z0, " #target "\n\t"		\
			: : "Jr" ((unsigned int)(value)));	\
	else							\
		__asm__ __volatile__(				\
			"mtlxc0\t%z0, " #target ", " #sel "\n"	\
			: : "Jr" ((unsigned int)(value)));	\
} while (0)


#define read_lxc0_estatus()	__read_32bit_lxc0_register($0, 0)
#define read_lxc0_ecause()	__read_32bit_lxc0_register($1, 0)
#define read_lxc0_intvec()	__read_32bit_lxc0_register($2, 0)
#define write_lxc0_estatus(val)	__write_32bit_lxc0_register($0, 0, val)
#define write_lxc0_ecause(val)	__write_32bit_lxc0_register($1, 0, val)
#define write_lxc0_intvec(val)	__write_32bit_lxc0_register($2, 0, val)

/*
 * The WMPCTL, WMPSTATUS and WMPVADDR register
 */
#define read_lxc0_wmpctl()	__read_32bit_lxc0_register($5, 0)
#define write_lxc0_wmpctl(val)	__write_32bit_lxc0_register($5, 0, val)

#define read_lxc0_wmpstatus()	__read_32bit_lxc0_register($6, 0)
#define read_lxc0_wmpvaddr()	__read_32bit_lxc0_register($7, 0)

/*
 * The WMPEXTRAMASK register.
 */ 
#define read_lxc0_wmpxmask0()	__read_32bit_lxc0_register($19, 0)
#define read_lxc0_wmpxmask1()	__read_32bit_lxc0_register($19, 1)
#define read_lxc0_wmpxmask2()	__read_32bit_lxc0_register($19, 2)
#define read_lxc0_wmpxmask3()	__read_32bit_lxc0_register($19, 3)
#define read_lxc0_wmpxmask4()	__read_32bit_lxc0_register($19, 4)
#define read_lxc0_wmpxmask5()	__read_32bit_lxc0_register($19, 5)
#define read_lxc0_wmpxmask6()	__read_32bit_lxc0_register($19, 6)
#define read_lxc0_wmpxmask7()	__read_32bit_lxc0_register($19, 7)

#define write_lxc0_wmpxmask0(val) __write_32bit_lxc0_register($19, 0, val)
#define write_lxc0_wmpxmask1(val) __write_32bit_lxc0_register($19, 1, val)
#define write_lxc0_wmpxmask2(val) __write_32bit_lxc0_register($19, 2, val)
#define write_lxc0_wmpxmask3(val) __write_32bit_lxc0_register($19, 3, val)
#define write_lxc0_wmpxmask4(val) __write_32bit_lxc0_register($19, 4, val)
#define write_lxc0_wmpxmask5(val) __write_32bit_lxc0_register($19, 5, val)
#define write_lxc0_wmpxmask6(val) __write_32bit_lxc0_register($19, 6, val)
#define write_lxc0_wmpxmask7(val) __write_32bit_lxc0_register($19, 7, val)

/*
 * Macros to access the floating point coprocessor control registers
 */
#define read_32bit_cp1_register(source)				\
({ int __res;							\
	__asm__ __volatile__(					\
	".set\tpush\n\t"					\
	".set\treorder\n\t"					\
	"cfc1\t%0,"STR(source)"\n\t"				\
	".set\tpop"						\
	: "=r" (__res));					\
	__res;})

/*
 * Manipulate bits in a lxc0 register.
 */
#define __BUILD_SET_LXC0(name)					\
static inline unsigned int					\
set_lxc0_##name(unsigned int set)				\
{								\
	unsigned int res;					\
								\
	res = read_lxc0_##name();				\
	res |= set;						\
	write_lxc0_##name(res);					\
								\
	return res;						\
}								\
								\
static inline unsigned int					\
clear_lxc0_##name(unsigned int clear)				\
{								\
	unsigned int res;					\
								\
	res = read_lxc0_##name();				\
	res &= ~clear;						\
	write_lxc0_##name(res);					\
								\
	return res;						\
}								\
								\
static inline unsigned int					\
change_lxc0_##name(unsigned int change, unsigned int new)	\
{								\
	unsigned int res;					\
								\
	res = read_lxc0_##name();				\
	res &= ~change;						\
	res |= (new & change);					\
	write_lxc0_##name(res);					\
								\
	return res;						\
}

__BUILD_SET_LXC0(intvec)
__BUILD_SET_LXC0(estatus)
__BUILD_SET_LXC0(ecause)
__BUILD_SET_LXC0(wmpctl)

#endif /* !__ASSEMBLY__ */

#endif /* _ASM_RLXREGS_H */
