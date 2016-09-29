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
#include <asm/mipsmtregs.h>
//#include <asm/smp-boot.h> //mark_bb

#ifdef CONFIG_RTL_8198C
#define PATT_READY  0x5555
#define PATT_MAGIC  0x7777
#define PATT_GO     0x9999		
#define LAUNCH_REG  0xb8000068		
#define POLLING_REG 0xb800006c
#define REG32(reg)		(*(volatile unsigned int   *)(reg))		

int	smpboot_pc;
int	smpboot_gp;
int	smpboot_sp;
int	smpboot_a0;
#endif		

int amon_cpu_avail(int cpu)
{
#ifdef CONFIG_RTL_8198C
	if(REG32(POLLING_REG) == PATT_READY) {
		pr_debug("SMP-amon: cpu%d is not ready\n", cpu);
		return 1;
	}
	//else if(REG32(POLLING_REG) == PATT_GO) {
	//	return 0;
	//}
	else
		return 0;
#else
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
#endif
}
	
void amon_cpu_start(int cpu,
		    unsigned long pc, unsigned long sp,
		    unsigned long gp, unsigned long a0)
{
#ifdef CONFIG_RTL_8198C
	if (!amon_cpu_avail(cpu))
		return;
	if (cpu == smp_processor_id()) {
		pr_debug("SMP-amon: I am cpu%d!\n", cpu);
		return;
	}

	pr_debug("SMP-amon: starting cpu%d\n", cpu);

	REG32(((unsigned int )&smpboot_pc)|0xa0000000)=pc;
	REG32(((unsigned int )&smpboot_gp)|0xa0000000)=gp;
	REG32(((unsigned int )&smpboot_sp)|0xa0000000)=sp;
	REG32(((unsigned int )&smpboot_a0)|0xa0000000)=a0;

	//REG32(LAUNCH_REG)=pc|0xa0000000;
	REG32(LAUNCH_REG)=pc;
		
	smp_wmb();              /* Target must see parameters before go */
	REG32(POLLING_REG)=PATT_MAGIC;
	smp_wmb();              /* Target must see go before we poll  */

	//while (REG32(POLLING_REG) == PATT_MAGIC) {};

	smp_rmb();      /* Target will be updating flags soon */
	pr_debug("SMP-amon: cpu%d gone!\n", cpu);

#else
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
#endif
}
