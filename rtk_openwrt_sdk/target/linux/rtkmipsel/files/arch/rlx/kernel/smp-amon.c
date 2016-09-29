/*
 * Realtek Semiconductor Corp.
 *
 * bsp/amon.c:
 *
 * Copyright 2012  Tony Wu (tonywu@realtek.com)
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>

#include <asm/addrspace.h>
#include <asm/smp-boot.h>

int amon_cpu_avail(int cpu)
{
	struct smp_boot *smpboot = (struct smp_boot *) SMPBOOT;

	if (cpu < 0 || cpu >= NR_CPUS) {
		pr_debug("SMP-amon: cpu%d is out of range\n", cpu);
		return 0;
	}

	smpboot += cpu;
	if (!(smpboot->flags & SMP_LAUNCH_FREADY)) {
		pr_debug("SMP-amon: cpu%d is not ready\n", cpu);
		return 0;
	}
	if (smpboot->flags & (SMP_LAUNCH_FGO|SMP_LAUNCH_FGONE)) {
		pr_debug("SMP-amon: too late.. cpu%d is already gone\n", cpu);
		return 0;
	}

	return 1;
}

void amon_cpu_start(int cpu,
		    unsigned long pc, unsigned long sp,
		    unsigned long gp, unsigned long a0)
{
	volatile struct smp_boot *smpboot = (struct smp_boot *) SMPBOOT;

	if (!amon_cpu_avail(cpu))
		return;
	if (cpu == smp_processor_id()) {
		pr_debug("SMP-amon: I am cpu%d!\n", cpu);
		return;
	}
	smpboot += cpu;

	pr_debug("SMP-amon: starting cpu%d\n", cpu);

	smpboot->pc = pc;
	smpboot->gp = gp;
	smpboot->sp = sp;
	smpboot->a0 = a0;

	smp_wmb();              /* Target must see parameters before go */
	smpboot->flags |= SMP_LAUNCH_FGO;
	smp_wmb();              /* Target must see go before we poll  */

	while ((smpboot->flags & SMP_LAUNCH_FGONE) == 0)
		;
	smp_rmb();      /* Target will be updating flags soon */
	pr_debug("SMP-amon: cpu%d gone!\n", cpu);
}
