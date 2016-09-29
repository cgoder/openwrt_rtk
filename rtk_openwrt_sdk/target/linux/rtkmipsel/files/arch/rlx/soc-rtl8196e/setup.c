/*
 * Realtek Semiconductor Corp.
 *
 * bsp/setup.c
 *     bsp setup code
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

#include <asm/bootinfo.h>
#include <asm/time.h>
#include <asm/reboot.h>

#include "bspchip.h"

static void shutdown_netdev(void)
{
	struct net_device *dev;
	
	printk("Shutdown network interface\n");
	read_lock(&dev_base_lock);

	for_each_netdev(&init_net, dev)
	{
		if(dev->flags &IFF_UP) 
		{
			printk("%s:===>\n",dev->name);			
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
	read_unlock(&dev_base_lock);
}

static void bsp_machine_restart(char *command)
{
	local_irq_disable();
	REG32(BSP_GIMR)=0;

#ifdef CONFIG_NET
	shutdown_netdev();
#endif

	REG32(BSP_WDTCNR) = 0; //enable watch dog
	while (1) ;
}
                                                                                                    
static void bsp_machine_halt(void)
{
	printk("System halted.\n");
	while(1);
}
                                                                                                    
static void bsp_machine_power_off(void)
{
	printk("System halted. Please power off.\n");
	while(1);
}

/*
 * callback function
 */
void __init bsp_setup(void)
{
	extern void bsp_serial_init(void);

	/* define io/mem region */
	ioport_resource.start = 0x18000000;
	ioport_resource.end = 0x1fffffff;

	iomem_resource.start = 0x18000000;
	iomem_resource.end = 0x1fffffff;

	/* set reset vectors */
	_machine_restart = bsp_machine_restart;
	_machine_halt = bsp_machine_halt;
	pm_power_off = bsp_machine_power_off;

#if defined(CONFIG_RTL_DUAL_PCIESLOT_BIWLAN_D) 
{
	unsigned int tmp=0,tmp1=0,tmp2=0;
	tmp1=REG32(0xb8001004);
	if((REG32(0xb8001000)&0x80000000)==0x80000000)
	{	
		//REG32(0xb8001008)=0x6d13a4c0;
		REG32(0xb8001004)=tmp1;
	}
}
#endif

	/* initialize uart */
	bsp_serial_init();

}
#ifdef CONFIG_OPENWRT_SDK
void bsp_reboot(void)
{
#define BSP_TC_BASE         0xB8003100
#define BSP_WDTCNR          (BSP_TC_BASE + 0x1C)


        REG32(BSP_GIMR)=0;

        local_irq_disable();
        REG32(BSP_WDTCNR) = 0; //enable watch dog

        printk("System halted.\n");
        while(1);
}
#endif
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

