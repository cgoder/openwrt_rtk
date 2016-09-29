/*
 *  Copyright (C) 1995, 1996, 2001  Ralf Baechle
 *  Copyright (C) 2001, 2004  MIPS Technologies, Inc.
 *  Copyright (C) 2004	Maciej W. Rozycki
 */
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <asm/bootinfo.h>
#include <asm/cpu.h>
#include <asm/cpu-features.h>
#include <asm/idle.h>
#include <asm/rlxregs.h>
#include <asm/processor.h>
#include <asm/prom.h>

unsigned int vced_count, vcei_count;

static int show_cpuinfo(struct seq_file *m, void *v)
{
	unsigned long n = (unsigned long) v - 1;
#ifdef CONFIG_CPU_HAS_WMPU
	int i;
#endif

#ifdef CONFIG_SMP
	if (!cpu_online(n))
		return 0;
#endif

	/*
	 * For the first processor also print the system type
	 */
	if (n == 0) {
		seq_printf(m, "system type\t\t: %s\n", get_system_type());
		if (mips_get_machine_name())
			seq_printf(m, "machine\t\t\t: %s\n",
				   mips_get_machine_name());
	}

	seq_printf(m, "processor\t\t: %ld\n", n);
	seq_printf(m, "cpu model\t\t: %d\n", cpu_data[n].processor_id);
	seq_printf(m, "BogoMIPS\t\t: %d.%02d\n",
		   cpu_data[n].udelay_val / (500000/HZ),
		   (cpu_data[n].udelay_val / (5000/HZ)) % 100);

	seq_printf(m, "tlb_entries\t\t: %d\n", cpu_data[n].tlbsize);
	seq_printf(m, "mips16 implemented\t: yes\n");

#ifdef CONFIG_CPU_HAS_WMPU
	seq_printf(m, "hardware watchpoint\t: yes, ");
	seq_printf(m, "count: %d, address/irw mask: [", cpu_data[n].watch_reg_count);
	for (i = 0; i < cpu_data[n].watch_reg_count; i++)
		seq_printf(m, "%s0x%04x", i ? ", " : "" ,
			   cpu_data[n].watch_reg_masks[i]);
	seq_printf(m, "]\n");
#endif

	return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
	unsigned long i = *pos;

	return i < NR_CPUS ? (void *) (i + 1) : NULL;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	++*pos;
	return c_start(m, pos);
}

static void c_stop(struct seq_file *m, void *v)
{
}

const struct seq_operations cpuinfo_op = {
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};
