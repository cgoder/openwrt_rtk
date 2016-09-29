/*
 * Realtek Semiconductor Corp.
 *
 * bsp/irq.c
 *   bsp interrupt initialization and handler code
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/timex.h>
#include <linux/random.h>
#include <linux/irq.h>
//#include <linux/version.h> //mark_bb

#include <asm/bitops.h>
#include <asm/bootinfo.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/irq_cpu.h>
#include <asm/irq_vec.h>
//#include <asm/system.h>
#include <asm/rlxregs.h>

#include "bspchip.h"


irqreturn_t bsp_ictl_irq_dispatch(int, void *);

static struct irqaction irq_cascade = { 
	.handler = bsp_ictl_irq_dispatch,
	.name = "cascade",
};

#ifdef CONFIG_WRT_BARRIER_BREAKER
static void bsp_ictl_irq_mask(struct irq_data *d)
{
	REG32(BSP_GIMR) &= ~(1 << (d->irq - BSP_IRQ_ICTL_BASE));
}

static void bsp_ictl_irq_unmask(struct irq_data *d)
{
	REG32(BSP_GIMR) |= (1 << (d->irq - BSP_IRQ_ICTL_BASE));
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
	REG32(BSP_GIMR) &= ~(1 << (irq - BSP_IRQ_ICTL_BASE));
}

static void bsp_ictl_irq_unmask(unsigned int irq)
{
	REG32(BSP_GIMR) |= (1 << (irq - BSP_IRQ_ICTL_BASE));
}

static struct irq_chip bsp_ictl_irq = {
	.name = "ICTL",
	.ack = bsp_ictl_irq_mask,
	.mask = bsp_ictl_irq_mask,
	.unmask = bsp_ictl_irq_unmask,
};
#endif

irqreturn_t bsp_ictl_irq_dispatch(int cpl, void *dev_id)
{
	unsigned int pending;

	pending = REG32(BSP_GIMR) & REG32(BSP_GISR) & BSP_IRQ_ICTL_MASK;

	//if (pending & BSP_UART0_IP)
	//	do_IRQ(BSP_UART0_IRQ); //for test
	//else if (pending & BSP_TC1_IP)
	//    do_IRQ(BSP_TC1_IRQ);
	//else {
		printk("Spurious Interrupt2:0x%x\n",pending);
		spurious_interrupt();
	//}
	return IRQ_HANDLED;
}

void bsp_irq_dispatch(void)
{
	unsigned int pending;

	pending = read_c0_cause() & read_c0_status() & ST0_IM;

	if (pending & CAUSEF_IP0)
		do_IRQ(0);
	else if (pending & CAUSEF_IP1)
		do_IRQ(1);
	else {
		printk("Spurious Interrupt:0x%x\n",pending);
		spurious_interrupt();
	}
}

static void __init bsp_ictl_irq_init(unsigned int irq_base)
{
	int i;

#ifdef CONFIG_WRT_BARRIER_BREAKER
	for (i=0; i < BSP_IRQ_ICTL_NUM; i++)
		irq_set_chip_and_handler(irq_base + i, &bsp_ictl_irq, handle_level_irq);
#else
	for (i=0; i < BSP_IRQ_ICTL_NUM; i++)
		set_irq_chip_and_handler(irq_base + i, &bsp_ictl_irq, handle_level_irq);
#endif

	//enable cascade
	setup_irq(BSP_ICTL_IRQ, &irq_cascade);
}

void __init bsp_irq_init(void)
{
	/* disable ict interrupt */
	REG32(BSP_GIMR) = 0;

	/* initialize IRQ action handlers */
	rlx_cpu_irq_init(BSP_IRQ_CPU_BASE);
	rlx_vec_irq_init(BSP_IRQ_LOPI_BASE);
	bsp_ictl_irq_init(BSP_IRQ_ICTL_BASE);

	/* Set IRR */
	REG32(BSP_IRR0) = BSP_IRR0_SETTING;
	REG32(BSP_IRR1) = BSP_IRR1_SETTING;
	REG32(BSP_IRR2) = BSP_IRR2_SETTING;
	REG32(BSP_IRR3) = BSP_IRR3_SETTING;  

	/* enable global interrupt mask */
	REG32(BSP_GIMR) = BSP_TC0_IE | BSP_UART0_IE;

#if defined(CONFIG_RTL8192CD) || defined(CONFIG_PCI) || defined(CONFIG_WLAN)
	REG32(BSP_GIMR) |= BSP_PCIE_IE;
#endif
#ifdef CONFIG_USB
	REG32(BSP_GIMR) |= BSP_USB_H_IE;
#endif
#ifdef CONFIG_DWC_OTG  //wei add
	REG32(BSP_GIMR) |= BSP_OTG_IE;  //mac
#endif
#ifdef CONFIG_RTL_819X_SWCORE
	REG32(BSP_GIMR) |= (BSP_SW_IE);
#endif
	//printk("BSP_IRQ_ICTL_MASK=0x%X\n", BSP_IRQ_ICTL_MASK);
}
