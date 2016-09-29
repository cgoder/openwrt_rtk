/*
 * Realtek Semiconductor Corp.
 *
 *
 * Copyright 2012  Tony Wu (tonywu@realtek.com)
 */

#ifndef _SMP_BOOT_H_
#define _SMP_BOOT_H_

#ifndef __ASSEMBLY__

struct smp_boot {
	unsigned long	pc;
	unsigned long	gp;
	unsigned long	sp;
	unsigned long	a0;
	unsigned long	_pad[3]; /* pad to cache line size to avoid thrashing */
	unsigned long	flags;
};

#else

#define LOG2CPULAUNCH		5
#define	SMP_LAUNCH_PC		0
#define	SMP_LAUNCH_GP		4
#define	SMP_LAUNCH_SP		8
#define	SMP_LAUNCH_A0		12
#define	SMP_LAUNCH_FLAGS	28

#endif

#define SMP_LAUNCH_FREADY	1
#define SMP_LAUNCH_FGO		2
#define SMP_LAUNCH_FGONE	4

#define SMPBOOT			0xa0000f00

/* Polling period in count cycles for secondary CPU's */
#define SMP_LAUNCH_PERIOD	10000

extern int amon_cpu_avail(int);
extern void amon_cpu_start(int, unsigned long, unsigned long,
			   unsigned long, unsigned long);
#endif
