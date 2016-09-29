/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2003, 04, 07 Ralf Baechle <ralf@linux-mips.org>
 * Copyright (C) MIPS Technologies, Inc.
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#ifndef _ASM_HAZARDS_H
#define _ASM_HAZARDS_H

#include <linux/stringify.h>

#define ___ssnop							\
	sll	$0, $0, 1

#define ___ehb								\
	sll	$0, $0, 3

/*
 * TLB hazards
 */
/*
 * Finally the catchall case for all other processors including R4000, R4400,
 * R4600, R4700, R5000, RM7000, NEC VR41xx etc.
 *
 * The taken branch will result in a two cycle penalty for the two killed
 * instructions on R4000 / R4400.  Other processors only have a single cycle
 * hazard so this is nice trick to have an optimal code for a range of
 * processors.
 */
#define __mtc0_tlbw_hazard
#define __tlbw_use_hazard
#define __tlb_probe_hazard
#define __irq_enable_hazard
#define __irq_disable_hazard
#define __back_to_back_c0_hazard
#define instruction_hazard() do { } while (0)


/* FPU hazards */

#define __enable_fpu_hazard
#define __disable_fpu_hazard

#ifdef __ASSEMBLY__

#define _ssnop ___ssnop
#define	_ehb ___ehb
#define mtc0_tlbw_hazard __mtc0_tlbw_hazard
#define tlbw_use_hazard __tlbw_use_hazard
#define tlb_probe_hazard __tlb_probe_hazard
#define irq_enable_hazard __irq_enable_hazard
#define irq_disable_hazard __irq_disable_hazard
#define back_to_back_c0_hazard __back_to_back_c0_hazard
#define enable_fpu_hazard __enable_fpu_hazard
#define disable_fpu_hazard __disable_fpu_hazard

#else

#define _ssnop()							\
do {									\
	__asm__ __volatile__(						\
	__stringify(___ssnop)						\
	);								\
} while (0)

#define	_ehb()								\
do {									\
	__asm__ __volatile__(						\
	__stringify(___ehb)						\
	);								\
} while (0)


#define mtc0_tlbw_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__mtc0_tlbw_hazard)					\
	);								\
} while (0)


#define tlbw_use_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__tlbw_use_hazard)					\
	);								\
} while (0)


#define tlb_probe_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__tlb_probe_hazard)					\
	);								\
} while (0)


#define irq_enable_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__irq_enable_hazard)				\
	);								\
} while (0)


#define irq_disable_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__irq_disable_hazard)				\
	);								\
} while (0)


#define back_to_back_c0_hazard() 					\
do {									\
	__asm__ __volatile__(						\
	__stringify(__back_to_back_c0_hazard)				\
	);								\
} while (0)


#define enable_fpu_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__enable_fpu_hazard)				\
	);								\
} while (0)


#define disable_fpu_hazard()						\
do {									\
	__asm__ __volatile__(						\
	__stringify(__disable_fpu_hazard)				\
	);								\
} while (0)

/*
 * MIPS R2 instruction hazard barrier.   Needs to be called as a subroutine.
 */
extern void mips_ihb(void);

#endif /* __ASSEMBLY__  */

#endif /* _ASM_HAZARDS_H */
