/*
 * Realtek Semiconductor Corp.
 *
 * bsp/irq-ictl.c
 *     DesignWare ICTL intialization and handlers
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)
static void bsp_ictl_irq_mask(struct irq_data *d)
{
	REG32(BSP_ICTL_MASK) |= (1 << (d->irq - BSP_IRQ_ICTL_BASE));
}

static void bsp_ictl_irq_unmask(struct irq_data *d)
{
	REG32(BSP_ICTL_MASK) &= ~(1 << (d->irq - BSP_IRQ_ICTL_BASE));
}

static struct irq_chip bsp_ictl_irq = {
	.name = "Sheipa ICTL",
	.irq_ack = bsp_ictl_irq_mask,
	.irq_mask = bsp_ictl_irq_mask,
	.irq_unmask = bsp_ictl_irq_unmask,
};
#else
static void bsp_ictl_irq_mask(unsigned int irq)
{
	REG32(BSP_ICTL_MASK) |= (1 << (irq - BSP_IRQ_ICTL_BASE));
}

static void bsp_ictl_irq_unmask(unsigned int irq)
{
	REG32(BSP_ICTL_MASK) &= ~(1 << (irq - BSP_IRQ_ICTL_BASE));
}

static struct irq_chip bsp_ictl_irq = {
	.name = "Sheipa ICTL",
	.ack = bsp_ictl_irq_mask,
	.mask = bsp_ictl_irq_mask,
	.unmask = bsp_ictl_irq_unmask,
};
#endif

irqreturn_t bsp_ictl_irq_dispatch(int cpl, void *dev_id)
{
	unsigned int pending = REG32(BSP_ICTL_FINALSTATUS);
	int irq;

	irq = irq_ffs(pending, 0);
	if (irq >= 0)
		do_IRQ(BSP_IRQ_ICTL_BASE + irq);
	else
		spurious_interrupt();

	return IRQ_HANDLED;
}

static struct irqaction irq_cascade = {
	.handler = bsp_ictl_irq_dispatch,
	.name = "Sheipa IRQ cascade",
};

static void __init bsp_ictl_irq_init(unsigned int irq_base)
{
	int i;

	/* disable ICTL inten */
	REG32(BSP_ICTL_INTEN) = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)
	for (i=0; i < BSP_IRQ_ICTL_NUM; i++)
		irq_set_chip_and_handler(irq_base + i, &bsp_ictl_irq, handle_level_irq);
#else
	for (i=0; i < BSP_IRQ_ICTL_NUM; i++)
		set_irq_chip_and_handler(irq_base + i, &bsp_ictl_irq, handle_level_irq);
#endif

	setup_irq(BSP_ICTL_IRQ, &irq_cascade);

	/* enable ICTL inten, mask everything initially */
	REG32(BSP_ICTL_MASK) = 0xffffffff;
	REG32(BSP_ICTL_INTEN) = 0xffffffff;
}
