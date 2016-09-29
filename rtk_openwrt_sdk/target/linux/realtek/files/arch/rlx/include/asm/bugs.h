/*
 * This is included by init/main.c to check for architecture-dependent bugs.
 *
 * Copyright (C) 2007  Maciej W. Rozycki
 *
 * Needs:
 *	void check_bugs(void);
 */
#ifndef _ASM_BUGS_H
#define _ASM_BUGS_H

#include <linux/bug.h>
#include <linux/delay.h>
#include <linux/smp.h>

#include <asm/cpu.h>
#include <asm/cpu-info.h>

static inline void check_bugs(void)
{
	unsigned int cpu = smp_processor_id();

	cpu_data[cpu].udelay_val = loops_per_jiffy;
}

#endif /* _ASM_BUGS_H */
