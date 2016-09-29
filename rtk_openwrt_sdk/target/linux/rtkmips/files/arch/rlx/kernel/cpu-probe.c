/*
 * Processor capabilities determination functions.
 *
 * Copyright (C) xxxx  the Anonymous
 * Copyright (C) 1994 - 2006 Ralf Baechle
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 * Copyright (C) 2001, 2004, 2011, 2012	 MIPS Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * Modified for RLX Processors
 * Copyright (C) 2008-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/ptrace.h>
#include <linux/stddef.h>
#include <linux/export.h>

#include <asm/cpu.h>
#include <asm/fpu.h>
#include <asm/rlxregs.h>
#include <asm/watch.h>

/*
 * Get the FPU Implementation/Revision.
 */
#ifdef CONFIG_CPU_HAS_FPU
static inline unsigned long cpu_get_fpu_id(void)
{
	unsigned long tmp, fpu_id;

	tmp = read_c0_status();
	__enable_fpu();
	fpu_id = read_32bit_cp1_register(CP1_REVISION);
	write_c0_status(tmp);
	return fpu_id;
}
#endif

void __cpuinit cpu_probe(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;

	c->options = MIPS_CPU_TLB | MIPS_CPU_3K_CACHE;
	c->tlbsize = cpu_tlb_entry;  /* defined in bspcpu.h */
	c->processor_id = read_c0_prid();
	c->fpu_id = FPIR_IMP_NONE;
#ifdef CONFIG_CPU_HAS_FPU
	c->options |= MIPS_CPU_FPU;
	c->options |= MIPS_CPU_32FPR;
	c->fpu_id = cpu_get_fpu_id();
#else
	c->options |= MIPS_CPU_NOFPUEX;
#endif

#ifdef CONFIG_CPU_HAS_WMPU
	c->options |= MIPS_CPU_WATCH;
	rlx_probe_watch_registers(c);
	c->watch_reg_use_cnt = c->watch_reg_count / 2;
#endif
}

void __cpuinit cpu_report(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;

	printk(KERN_INFO "CPU revision is: %08x\n", c->processor_id);
#ifdef CONFIG_CPU_HAS_FPU
	printk(KERN_INFO "FPU revision is: %08x\n", c->fpu_id);
#endif
}
