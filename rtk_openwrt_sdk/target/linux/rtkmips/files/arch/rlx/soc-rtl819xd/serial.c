/*
 * Copyright 2006, Realtek Semiconductor Corp.
 *
 * arch/rlx/rlxocp/serial.c
 *     RTL819xD serial port initialization
 *
 * Tony Wu (tonywu@realtek.com.tw)
 * Nov. 07, 2006
 */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/serial_8250.h>
#include <linux/string.h>

#include <asm/serial.h>

#include "bspchip.h"

void __init bsp_serial_init(void)
{
#ifdef CONFIG_SERIAL_SC16IS7X0
	extern void __init sc16is7x0_get_port( struct uart_port *port );
#endif
#if defined( CONFIG_SERIAL_SC16IS7X0 ) || defined( CONFIG_SERIAL_RTL8198_UART1 )
	unsigned int line = 0; 
#else
	const unsigned int line = 0; 
#endif

	struct uart_port s;

	/* clear memory */
	memset(&s, 0, sizeof(s));

    /*
     * UART0
     */
	s.line = line;
    s.type = PORT_16550A;
    s.irq = BSP_UART0_IRQ;
    s.iotype = UPIO_MEM;
    s.regshift = 2;
#if 1
	s.uartclk = BSP_SYS_CLK_RATE;
    s.fifosize = 16;
	//s.flags = UPF_SKIP_TEST | UPF_LOW_LATENCY;
	s.flags = UPF_SKIP_TEST;
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
		panic("RTL819xD: bsp_serial_init failed!");
	}

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
		panic("RTL819xD: bsp_serial_init UART1 failed!");
	}	
#endif

#ifdef CONFIG_SERIAL_SC16IS7X0
	sc16is7x0_get_port( &s );
	s.line = ++ line;

	if (early_serial_setup(&s) != 0) {
		panic("RTL819xD: bsp_serial_init i2c uart failed!");
	}
#endif

}
