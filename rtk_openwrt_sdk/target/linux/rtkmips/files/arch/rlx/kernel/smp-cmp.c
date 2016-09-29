/*
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 * Copyright (C) 2007 MIPS Technologies, Inc.
 *    Chris Dearman (chris@mips.com)
 *
 * Modified for RLX Linux for RLX
 * Copyright (C) 2012 Tony Wu (tonywu@realtek.com)
 */

#undef DEBUG

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/smp.h>
#include <linux/cpumask.h>
#include <linux/interrupt.h>
#include <linux/compiler.h>

#include <linux/atomic.h>
#include <asm/cacheflush.h>
#include <asm/cpu.h>
#include <asm/processor.h>
#include <asm/hardirq.h>
#include <asm/mmu_context.h>
#include <asm/smp.h>
#include <asm/smp-boot.h>
#include <asm/time.h>
#include <asm/rlxregs.h>
#include <asm/mmcr.h>
#include <asm/gic.h>


static void ipi_call_function(unsigned int cpu)
{
	pr_debug("CPU%d: %s cpu %d status %08x\n",
		 smp_processor_id(), __func__, cpu, read_c0_status());

	gic_send_ipi(GIC_IPI_CALL(cpu));
}

static void ipi_resched(unsigned int cpu)
{
	pr_debug("CPU%d: %s cpu %d status %08x\n",
		 smp_processor_id(), __func__, cpu, read_c0_status());

	gic_send_ipi(GIC_IPI_RESCHED(cpu));
}

/*
 * The SMVP kernel could use GIC interrupts if available
 */
void cmp_send_ipi_single(int cpu, unsigned int action)
{
	unsigned long flags;

	local_irq_save(flags);

	switch (action) {
	case SMP_CALL_FUNCTION:
		ipi_call_function(cpu);
		break;

	case SMP_RESCHEDULE_YOURSELF:
		ipi_resched(cpu);
		break;
	}

	local_irq_restore(flags);
}

static void cmp_send_ipi_mask(const struct cpumask *mask, unsigned int action)
{
	unsigned int i;

	for_each_cpu(i, mask)
		cmp_send_ipi_single(i, action);
}

static void __cpuinit cmp_init_secondary(void)
{
	extern void bsp_smp_init_secondary(void);
#ifdef CONFIG_IRQ_VEC
	extern char handle_vec;

	write_lxc0_intvec(&handle_vec);
#endif
	/* Call bsp init_secondary hook */
	bsp_smp_init_secondary();
}

/*
 * called in smp.c:
 *
 * mp_ops->smp_finish;
 */
static void cmp_smp_finish(void)
{
	pr_debug("SMPCMP: CPU%d: %s\n", smp_processor_id(), __func__);

	/* CDFIXME: remove this? */
	write_c0_compare(read_c0_count() + (8 * rlx_hpt_frequency / HZ));

	local_irq_enable();
}

static void cmp_cpus_done(void)
{
	pr_debug("SMPCMP: CPU%d: %s\n", smp_processor_id(), __func__);
}

/*
 * Setup the PC, SP, and GP of a secondary processor and start it running
 * smp_bootstrap is the place to resume from
 * __KSTK_TOS(idle) is apparently the stack pointer
 * (unsigned long)idle->thread_info the gp
 */
static void __cpuinit cmp_boot_secondary(int cpu, struct task_struct *idle)
{
	struct thread_info *gp = task_thread_info(idle);
	unsigned long sp = __KSTK_TOS(idle);
	unsigned long pc = (unsigned long)&smp_bootstrap;
	unsigned long a0 = 0;

	pr_debug("SMPCMP: CPU%d: %s cpu %d\n", smp_processor_id(),
		__func__, cpu);

#if 0
	/* Needed? */
	flush_icache_range((unsigned long)gp,
			   (unsigned long)(gp + sizeof(struct thread_info)));
#endif

	mmcr_init_core(cpu);
	amon_cpu_start(cpu, pc, sp, (unsigned long)gp, a0);
}

/*
 * Common setup before any secondaries are started
 */
void __init cmp_smp_setup(void)
{
	int i;
	int ncpu = 0;

	pr_debug("SMPCMP: CPU%d: %s\n", smp_processor_id(), __func__);

	for (i = 1; i < NR_CPUS; i++) {
		if (amon_cpu_avail(i)) {
			set_cpu_possible(i, true);
			__cpu_number_map[i]	= ++ncpu;
			__cpu_logical_map[ncpu] = i;
		}
	}

	pr_info("Detected %i available secondary CPU(s)\n", ncpu);
}

void __init cmp_prepare_cpus(unsigned int max_cpus)
{
	pr_debug("SMPCMP: CPU%d: %s max_cpus=%d\n",
		 smp_processor_id(), __func__, max_cpus);
}

struct plat_smp_ops cmp_smp_ops = {
	.send_ipi_single	= cmp_send_ipi_single,
	.send_ipi_mask		= cmp_send_ipi_mask,
	.init_secondary		= cmp_init_secondary,
	.smp_finish		= cmp_smp_finish,
	.cpus_done		= cmp_cpus_done,
	.boot_secondary		= cmp_boot_secondary,
	.smp_setup		= cmp_smp_setup,
	.prepare_cpus		= cmp_prepare_cpus,
};
