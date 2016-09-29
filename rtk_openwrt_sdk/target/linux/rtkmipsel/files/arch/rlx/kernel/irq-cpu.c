/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * Copyright (C) 2001 Ralf Baechle
 * Copyright (C) 2005  MIPS Technologies, Inc.	All rights reserved.
 *	Author: Maciej W. Rozycki <macro@mips.com>
 *
 * This file define the irq handler for MIPS CPU interrupts.
 *
 * This program is free software; you can redistribute	it and/or modify it
 * under  the terms of	the GNU General	 Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

/*
 * Almost all MIPS CPUs define 8 interrupt sources.  They are typically
 * level triggered (i.e., cannot be cleared from CPU; must be cleared from
 * device).  The first two are software interrupts which we don't really
 * use or support.  The last one is usually the CPU timer interrupt if
 * counter register is present or, for CPUs with an external FPU, by
 * convention it's the FPU exception interrupt.
 *
 * Don't even think about using this on SMP.  You have been warned.
 *
 * This file exports one global function:
 *	void rlx_cpu_irq_init(void);
 */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/irq.h>
#include <linux/irqdomain.h>

#include <asm/irq_cpu.h>
#include <asm/rlxregs.h>


static int rlx_cpu_irq_base;

static inline void unmask_rlx_irq(struct irq_data *d)
{
	set_c0_status(0x100 << (d->irq - rlx_cpu_irq_base));
	irq_enable_hazard();
}

static inline void mask_rlx_irq(struct irq_data *d)
{
	clear_c0_status(0x100 << (d->irq - rlx_cpu_irq_base));
	irq_disable_hazard();
}

static struct irq_chip rlx_cpu_irq_controller = {
	.name		= "RLX",
	.irq_ack	= mask_rlx_irq,
	.irq_mask	= mask_rlx_irq,
	.irq_mask_ack	= mask_rlx_irq,
	.irq_unmask	= unmask_rlx_irq,
	.irq_eoi	= unmask_rlx_irq,
};

void __init rlx_cpu_irq_init(int irq_base)
{
	int i;

	/* Mask interrupts. */
	clear_c0_status(ST0_IM);
	clear_c0_cause(CAUSEF_IP);

	rlx_cpu_irq_base = irq_base;
	for (i = irq_base + 2; i < irq_base + 8; i++)
		irq_set_chip_and_handler(i, &rlx_cpu_irq_controller,
					 handle_percpu_irq);
}

#ifdef CONFIG_IRQ_DOMAIN
static int mips_cpu_intc_map(struct irq_domain *d, unsigned int irq,
			     irq_hw_number_t hw)
{
	static struct irq_chip *chip;

	if (hw < 2 && cpu_has_mipsmt) {
		/* Software interrupts are used for MT/CMT IPI */
		chip = &mips_mt_cpu_irq_controller;
	} else {
		chip = &mips_cpu_irq_controller;
	}

	irq_set_chip_and_handler(irq, chip, handle_percpu_irq);

	return 0;
}

static const struct irq_domain_ops mips_cpu_intc_irq_domain_ops = {
	.map = mips_cpu_intc_map,
	.xlate = irq_domain_xlate_onecell,
};

int __init mips_cpu_intc_init(struct device_node *of_node,
			      struct device_node *parent)
{
	struct irq_domain *domain;

	/* Mask interrupts. */
	clear_c0_status(ST0_IM);
	clear_c0_cause(CAUSEF_IP);

	domain = irq_domain_add_legacy(of_node, 8, MIPS_CPU_IRQ_BASE, 0,
				       &mips_cpu_intc_irq_domain_ops, NULL);
	if (!domain)
		panic("Failed to add irqdomain for MIPS CPU\n");

	return 0;
}
#endif /* CONFIG_IRQ_DOMAIN */
