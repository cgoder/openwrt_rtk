/*
 * Realtek Semiconductor Corp.
 *
 * bsp/serial.c
 *     BSP serial port initialization
 *
 * Copyright 2006-2012 Tony Wu (tonywu@realtek.com)
 */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>
#include <linux/serial_8250.h>
#include <linux/serial_reg.h>
#include <linux/tty.h>
#include <linux/irq.h>
#include <linux/string.h>
#include <asm/serial.h>

#include "bspchip.h"

#if 0
static struct resource bsp_uart_resources[] = {
	{
		.start = BSP_UART0_MAP_BASE,
		.end = BSP_UART0_MAP_BASE+0x20,
		.flags = IORESOURCE_MEM,
	},
};

//#define BSP_UART_FLAGS (UPF_FIXED_TYPE | UPF_SKIP_TEST | UPF_LOW_LATENCY | UPF_IOREMAP)
#define BSP_UART_FLAGS (UPF_FIXED_TYPE | UPF_SKIP_TEST | UPF_IOREMAP)

static struct plat_serial8250_port bsp_uart_data[] = {
	{
                .mapbase        = BSP_UART0_MAP_BASE,
                .irq            = BSP_UART0_IRQ,
                .flags          = BSP_UART_FLAGS,
                .iotype         = UPIO_MEM,
                .regshift       = 2,
                .uartclk        = BSP_SYS_CLK_RATE,
                .type		= PORT_16550A,
	},
        { },
};

static struct platform_device bsp_uart = {
	 .name               = "serial8250",
        .id                 = 0,
        .dev.platform_data  = bsp_uart_data,
        .num_resources      = 1, 
        .resource           = bsp_uart_resources

};

static struct platform_device *bsp_platform_devices[] __initdata = {
	&bsp_uart
};

int __init bsp_serial_init(void)
{
	int ret;

	ret = platform_add_devices(bsp_platform_devices, 
                                ARRAY_SIZE(bsp_platform_devices));
        if (ret < 0) {
        	panic("bsp_serial_init failed!");
	}
	return ret;
}

arch_initcall(bsp_serial_init);

#else
void __init bsp_serial_init(void)
{
	struct uart_port up;

	/* clear memory */
	memset(&up, 0, sizeof(up));

	/*
	 * UART0
	 */
	up.line = 0;
	up.type = PORT_16550A;
	up.irq = BSP_UART0_IRQ;
	up.iotype = UPIO_MEM;
	up.regshift = 2;
#if 1
	up.uartclk = BSP_SYS_CLK_RATE;
	up.fifosize = 16;
	//up.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY;
	up.flags = UPF_SKIP_TEST; 
	up.mapbase = BSP_UART0_MAP_BASE;
	//up.membase = ioremap_nocache(up.mapbase, BSP_UART0_MAPSIZE);
	up.membase = ioremap_nocache(up.mapbase, 0x20);
#else
	up.uartclk = BSP_SYS_CLK_RATE - BSP_BAUDRATE * 24; //???
	up.fifosize = 1;                           //???
	up.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY | UPF_SPD_CUST;
	up.membase = (unsigned char *)BSP_UART0_BASE;
	up.custom_divisor = BSP_SYS_CLK_RATE / (BSP_BAUDRATE * 16) - 1;
#endif
	if (early_serial_setup(&up) != 0) {
		panic("bsp_serial_init failed!");
	}
}
#endif