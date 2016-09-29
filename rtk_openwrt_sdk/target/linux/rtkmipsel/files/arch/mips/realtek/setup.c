/*
 * Realtek Semiconductor Corp.
 *
 * bsp/setup.c
 *     bsp interrult initialization and handler code
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/console.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/netdevice.h>
#include <linux/rtnetlink.h>

#include <asm/addrspace.h>
#include <asm/irq.h>
#include <asm/io.h>

#include <asm/time.h>
#include <asm/reboot.h>

#include <asm/mach-realtek/bspchip.h>

#if 0//def CONFIG_RTL8192CD_MODULE 
//this is for WIFI driver a static continuous big dma address for rtl8192cd.ko in openwrt platform.
#if (defined(CONFIG_RTL_8812_SUPPORT) && defined(CONFIG_WLAN_HAL_8192EE)) || (defined(CONFIG_RTL_8881A) )
unsigned char desc_buf[2][360000];
#else
unsigned char desc_buf[205120];
#endif
EXPORT_SYMBOL(desc_buf);
#endif


#ifndef REG8
#define REG8(reg) 				(*((volatile unsigned char *)(reg)))
#endif

void prom_putchar(char c)
{
#define UART0_BASE		0xB8002000
#define UART0_THR		(UART0_BASE + 0x000)
#define UART0_FCR		(UART0_BASE + 0x008)
#define UART0_LSR       (UART0_BASE + 0x014)
#define TXRST			0x04
#define CHAR_TRIGGER_14	0xC0
#define LSR_THRE		0x20
#define TxCHAR_AVAIL	0x00
#define TxCHAR_EMPTY	0x20

	unsigned int busy_cnt = 0;

	do
	{
		/* Prevent Hanging */
		if (busy_cnt++ >= 30000)
		{
			/* Reset Tx FIFO */
			REG8(UART0_FCR) = TXRST | CHAR_TRIGGER_14;
			return;
		}
	} while ((REG8(UART0_LSR) & LSR_THRE) == TxCHAR_AVAIL);

	/* Send Character */
	REG8(UART0_THR) = c;
	return;
}

static void shutdown_netdev(void)
{
	struct net_device *dev;

	printk("Shutdown network interface\n");
	read_lock(&dev_base_lock);

	for_each_netdev(&init_net, dev)
	{
		if(dev->flags &IFF_UP) 
		{
			rtnl_lock();
#if defined(CONFIG_COMPAT_NET_DEV_OPS)
			if(dev->stop)
				dev->stop(dev);
#else
			if ((dev->netdev_ops)&&(dev->netdev_ops->ndo_stop))
				dev->netdev_ops->ndo_stop(dev);
#endif
			rtnl_unlock();
		}
      	}
#if defined(CONFIG_RTL8192CD)
	{
		extern void force_stop_wlan_hw(void);
		force_stop_wlan_hw();
	}
#endif
#ifdef CONFIG_RTL_8367R_SUPPORT
	{	
	extern void rtl83XX_reset(void);
	rtl83XX_reset();
	}
#endif
	read_unlock(&dev_base_lock);
}

int is_kernel_reboot=0;

static void bsp_machine_restart(char *command)
{
#define BSP_TC_BASE         0xB8003100
#define BSP_WDTCNR          (BSP_TC_BASE + 0x1C)

	static void (*back_to_prom)(void) = (void (*)(void)) 0xbfc00000;
	
	REG32(BSP_GIMR)=0;
	
	local_irq_disable();
#ifdef CONFIG_NET    
	shutdown_netdev();
#endif 
	is_kernel_reboot=1;   
	REG32(BSP_WDTCNR) = 0; //enable watch dog
#ifdef CONFIG_SPI_3to4BYTES_ADDRESS_SUPPORT
{
        extern unsigned int ComSrlCmd_EX4B(unsigned char ucChip, unsigned int uiLen);
        ComSrlCmd_EX4B(0, 4);
}
#endif
	printk("System halted.\n");
	while(1);
	
	/* Reboot */
	back_to_prom();	
}
void bsp_reboot(void)
{
#define BSP_TC_BASE         0xB8003100
#define BSP_WDTCNR          (BSP_TC_BASE + 0x1C)
	

        REG32(BSP_GIMR)=0;

        local_irq_disable();
	is_kernel_reboot=1;
        REG32(BSP_WDTCNR) = 0; //enable watch dog

        printk("System halted.\n");
        while(1);
}

static void bsp_machine_halt(void)
{
	is_kernel_reboot=1;
	printk("System halted.\n");
	while(1);
}

/* callback function */
//void __init bsp_setup(void)
void __init plat_mem_setup(void)
{
	extern void bsp_serial_init(void);
	//extern void bsp_smp_init(void);

	/* define io/mem region */
	ioport_resource.start = 0x18000000;
	ioport_resource.end = 0x1fffffff;

	iomem_resource.start = 0x18000000;
	iomem_resource.end = 0x1fffffff;

	/* set reset vectors */
	_machine_restart = bsp_machine_restart;
	_machine_halt = bsp_machine_halt;
	pm_power_off = bsp_machine_halt;

	bsp_serial_init();

#ifdef CONFIG_RTL_8198C
	{
	extern void ado_refine(void);
	ado_refine();
	}
#endif
}

#ifdef CONFIG_RTL819X_WDT
#include <linux/platform_device.h>
static int __init  rtl819x_register_wdt(void)
{
        struct resource res;

        memset(&res, 0, sizeof(res));

        res.flags = IORESOURCE_MEM;
        res.start = PADDR(BSP_CDBR); // wdt clock control
        res.end = res.start + 0x8 - 1;	
	 platform_device_register_simple("rtl819x-wdt", -1, &res, 1);	
	 return 0;

}
arch_initcall(rtl819x_register_wdt);
#endif

