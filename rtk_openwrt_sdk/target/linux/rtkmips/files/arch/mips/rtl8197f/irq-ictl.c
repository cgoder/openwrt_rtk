/*
 * Realtek Semiconductor Corp.
 *
 * bsp/irq-ictl.c
 *     DesignWare ICTL intialization and handlers
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */

static void bsp_ictl_irq_mask(struct irq_data *d)
{
	if (d->irq >= BSP_IRQ_ICTL_BASE2)
		REG32(BSP_GIMR2) &= ~(1 << (d->irq - BSP_IRQ_ICTL_BASE2));
	else
		REG32(BSP_GIMR) &= ~(1 << (d->irq - BSP_IRQ_ICTL_BASE));
}

static void bsp_ictl_irq_unmask(struct irq_data *d)
{
	if (d->irq >= BSP_IRQ_ICTL_BASE2)
		REG32(BSP_GIMR2) |= (1 << (d->irq - BSP_IRQ_ICTL_BASE2));
	else
		REG32(BSP_GIMR) |= (1 << (d->irq - BSP_IRQ_ICTL_BASE));
}

static struct irq_chip bsp_ictl_irq = {
	.name = "ICTL",
	.irq_ack = bsp_ictl_irq_mask,
	.irq_mask = bsp_ictl_irq_mask,
	.irq_unmask = bsp_ictl_irq_unmask,
};

irqreturn_t bsp_ictl_irq_dispatch(int cpl, void *dev_id)
{
	unsigned int pending = REG32(BSP_GISR) & REG32(BSP_GIMR) & (~(BSP_GIMR_TOCPU_MASK));
	int irq;

	irq = irq_ffs(pending, 0);
	if (irq >= 0) {
		if (irq == 31) {
			unsigned int pending2 = REG32(BSP_GISR2) & REG32(BSP_GIMR2) & (~(BSP_GIMR_TOCPU_MASK2));
			irq = irq_ffs(pending2, 0);
			if (irq >= 0)
				do_IRQ(BSP_IRQ_ICTL_BASE2 + irq);
			else
				spurious_interrupt();
		}
		else {
			do_IRQ(BSP_IRQ_ICTL_BASE + irq);
		}
	}
	else {
		spurious_interrupt();
	}
	return IRQ_HANDLED;
}

static struct irqaction irq_cascade = {
	.handler = bsp_ictl_irq_dispatch,
	.name = "IRQ cascade",
};

static void __init bsp_ictl_irq_init(unsigned int irq_base)
{
	int i;

	for (i=0; i < BSP_IRQ_ICTL_NUM; i++)
		irq_set_chip_and_handler(irq_base + i, &bsp_ictl_irq, handle_level_irq);

	setup_irq(BSP_ICTL_IRQ, &irq_cascade);
}
