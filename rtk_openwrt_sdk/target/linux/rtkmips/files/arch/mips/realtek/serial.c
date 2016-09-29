/*
 * Realtek Semiconductor Corp.
 *
 * bsp/serial.c
 *     BSP serial port initialization
 *
 * Copyright 2006-2012 Tony Wu (tonywu@realtek.com)
 */
#ifdef CONFIG_USE_UAPI
#include <generated/uapi/linux/version.h>
#else
#include <linux/version.h>
#endif
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/serial_8250.h>
#include <linux/serial_reg.h>
#include <linux/tty.h>
#include <linux/irq.h>

#include <asm/serial.h>

#include <asm/mach-realtek/bspchip.h>

#if 0
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
unsigned int last_lcr;

unsigned int dwapb_serial_in(struct uart_port *p, int offset)
{
	offset <<= p->regshift;
	return readl(p->membase + offset);
}

void dwapb_serial_out(struct uart_port *p, int offset, int value)
{
	int save_offset = offset;
	offset <<= p->regshift;

	/* Save the LCR value so it can be re-written when a
	 * Busy Detect interrupt occurs. */
	if (save_offset == UART_LCR) {
		last_lcr = value;
	}
	writel(value, p->membase + offset);
	/* Read the IER to ensure any interrupt is cleared before
	 * returning from ISR. */
	if (save_offset == UART_TX || save_offset == UART_IER)
		value = p->serial_in(p, UART_IER);
}

static int dwapb_serial_irq(struct uart_port *p)
{
	unsigned int iir = readl(p->membase + (UART_IIR << p->regshift));

	if (serial8250_handle_irq(p, iir)) {
		return 1;
	} else if ((iir & UART_IIR_BUSY) == UART_IIR_BUSY) {
		/*
		 * The DesignWare APB UART has an Busy Detect (0x07) interrupt
		 * meaning an LCR write attempt occurred while the UART was
		 * busy. The interrupt must be cleared by reading the UART
		 * status register (USR) and the LCR re-written.
		 */
		(void)readl(p->membase + 0xc0);
		writel(last_lcr, p->membase + (UART_LCR << p->regshift));
		return 1;
	}

	return 0;
}
#endif

int __init bsp_serial_init(void)
{
	struct uart_port up;

	/* clear memory */
	memset(&up, 0, sizeof(up));

	/*
	 * UART0
	 */
	up.line = 0;
	up.type = PORT_16550A;
	up.uartclk = BSP_UART0_FREQ;
	up.fifosize = 16;
	up.irq = BSP_UART0_IRQ;
	up.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY;
	up.mapbase = BSP_UART0_MAPBASE;
	up.membase = ioremap_nocache(up.mapbase, BSP_UART0_MAPSIZE);
	up.regshift = 2;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
	up.iotype = UPIO_MEM32;
	up.serial_out = dwapb_serial_out;
	up.serial_in = dwapb_serial_in;
	up.handle_irq = dwapb_serial_irq;
#else
	up.iotype = UPIO_DWAPB;
	up.private_data = (void *)BSP_UART0_USR;
#endif

	if (early_serial_setup(&up) != 0) {
		panic("Sheipa: bsp_serial_init failed!");
	}

	return 0;
}
#endif

void __init bsp_serial_init(void)
{
	struct uart_port s;

	/* clear memory */
	memset(&s, 0, sizeof(s));

	/*
	 * UART0
	 */
	s.line = 0;
	s.type = PORT_16550A;
	s.irq = BSP_UART0_IRQ;
	s.iotype = UPIO_MEM;
	s.regshift = 2;
#if 1
	s.uartclk = BSP_SYS_CLK_RATE;
	s.fifosize = 16;
	s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY;
	s.mapbase = BSP_UART0_MAP_BASE;
	//s.membase = ioremap_nocache(s.mapbase, BSP_UART0_MAPSIZE);
	s.membase = ioremap_nocache(s.mapbase, 0x20);
#else
	s.uartclk = BSP_SYS_CLK_RATE - BSP_BAUDRATE * 24; //???
    s.fifosize = 1;                           //???
    s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY | UPF_SPD_CUST;
    s.membase = (unsigned char *)BSP_UART0_BASE;
    s.custom_divisor = BSP_SYS_CLK_RATE / (BSP_BAUDRATE * 16) - 1;
#endif

	if (early_serial_setup(&s) != 0) {
		panic("8198C: bsp_serial_init failed!");
	}
#ifdef CONFIG_SERIAL_RTL_UART1
	/*
	 * UART1
	 */
	s.line += 1;
	s.type = PORT_16550A;
	s.irq = BSP_UART1_IRQ;
	s.iotype = UPIO_MEM;
	s.regshift = 2;
#if 1
	s.uartclk = BSP_SYS_CLK_RATE;
	s.fifosize = 16;
	//s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY;
	s.flags = UPF_SKIP_TEST;
	s.mapbase = BSP_UART1_MAP_BASE;
	//s.membase = ioremap_nocache(s.mapbase, BSP_UART0_MAPSIZE);
	s.membase = ioremap_nocache(s.mapbase, 0x20);
#else
    s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY | UPF_SPD_CUST;
    s.membase = (unsigned char *)BSP_UART0_BASE;
    s.custom_divisor = BSP_SYS_CLK_RATE / (BSP_BAUDRATE * 16) - 1;
#endif

	if (early_serial_setup(&s) != 0) {
		panic("8198C: bsp_serial_init port 1 failed!");
	}
#endif

#ifdef CONFIG_SERIAL_RTL_UART2
	/*
	 * UART2
	 */
	s.line += 1;
	s.type = PORT_16550A;
	s.irq = BSP_UART2_IRQ;
	s.iotype = UPIO_MEM;
	s.regshift = 2;
#if 1
	s.uartclk = BSP_SYS_CLK_RATE;
	s.fifosize = 16;
	//s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY;
	s.flags = UPF_SKIP_TEST;
	s.mapbase = BSP_UART2_MAP_BASE;
	//s.membase = ioremap_nocache(s.mapbase, BSP_UART0_MAPSIZE);
	s.membase = ioremap_nocache(s.mapbase, 0x20);
#else
    s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY | UPF_SPD_CUST;
    s.membase = (unsigned char *)BSP_UART0_BASE;
    s.custom_divisor = BSP_SYS_CLK_RATE / (BSP_BAUDRATE * 16) - 1;
#endif

	if (early_serial_setup(&s) != 0) {
		panic("8198C: bsp_serial_init port 2 failed!");
	}
#endif

#ifdef CONFIG_SERIAL_RTL8198_UART1
	// UART1 
#define UART_BASE         0xB8000100  //0xb8002100 uart 1 
#define REG32(reg)       (*(volatile unsigned int *)(reg))
 REG32(0xb8000040)= (REG32(0xb8000040) & ~(0x3<<3)) | (0x01<<3);   //pin mux to UART1 
 REG32(0xb8002110) |= (1<<29);   //enable flow control
	s.line = ++ line;
    s.irq = BSP_UART1_IRQ;
	s.mapbase = BSP_UART1_MAP_BASE;
	s.membase = ioremap_nocache(s.mapbase, 0x20);
	
	if (early_serial_setup(&s) != 0) {
		panic("RTL8198: bsp_serial_init UART1 failed!");
	}	
#endif
	//printk("=>bsp_serial_init\n");
	return;
}

//=============================================================

