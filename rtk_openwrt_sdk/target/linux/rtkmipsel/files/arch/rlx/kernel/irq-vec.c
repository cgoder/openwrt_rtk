/*
 * Realtek Semiconductor Corp.
 *
 * This file define the irq handler for RLX CPU interrupts.
 *
 * Tony Wu (tonywu@realtek.com.tw)
 * Feb. 28, 2008
 */

#include <linux/irq.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>

#include <asm/irq_vec.h>
#include <asm/rlxregs.h>

static int rlx_vec_irq_base;
extern asmlinkage void rlx_do_IRQ(int);

static inline void unmask_rlx_vec_irq(struct irq_data *d)
{
	set_lxc0_estatus(0x10000 << (d->irq - rlx_vec_irq_base));
	irq_enable_hazard();
}

static inline void mask_rlx_vec_irq(struct irq_data *d)
{
	clear_lxc0_estatus(0x10000 << (d->irq - rlx_vec_irq_base));
	irq_disable_hazard();
}

static struct irq_chip rlx_vec_irq_controller = {
	.name		= "RLX LOPI",
	.irq_ack	= mask_rlx_vec_irq,
	.irq_mask	= mask_rlx_vec_irq,
	.irq_mask_ack	= mask_rlx_vec_irq,
	.irq_unmask	= unmask_rlx_vec_irq,
	.irq_eoi	= unmask_rlx_vec_irq,
};

static struct irq_desc *rlx_vec_irq_desc;

void __init rlx_vec_irq_init(int irq_base)
{
	int i;
	extern char handle_vec;

	/* Mask interrupts. */
	clear_lxc0_estatus(EST0_IM);
	clear_lxc0_ecause(ECAUSEF_IP);

	rlx_vec_irq_base = irq_base;
	rlx_vec_irq_desc = irq_desc + irq_base;

	for (i = irq_base; i < irq_base + 8; i++)
		irq_set_chip_and_handler(i, &rlx_vec_irq_controller,
					 handle_percpu_irq);

	write_lxc0_intvec(&handle_vec);
}

asmlinkage void rlx_do_lopi_IRQ(int irq_offset)
{
	do_IRQ(rlx_vec_irq_base + irq_offset);
}
