/*
 *  Realte rtl819x USB host device support
 *
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15 BSP
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>

#include "bspchip.h"
#include "dev_usb.h"

/*
 * OHCI (USB full speed host controller)
 */
static struct resource rtl819x_ohci_resources[] = {
	[0] = {
		.start	= PADDR(OHCI_RTL819x_USB_BASE),
		.end	= PADDR(OHCI_RTL819x_USB_BASE) + OHCI_RTL819x_USB_REG_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= RTL819x_USB_IRQ,
		.end	= RTL819x_USB_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

static u64 rtl819x_ohci_dmamask = RTL819x_DMA_MASK;
static struct platform_device rtl819x_ohci_device = {
	.name			= "rtl819x-ohci",
	.id				= -1,
	.resource		= rtl819x_ohci_resources,
	.num_resources	= ARRAY_SIZE(rtl819x_ohci_resources),
	.dev = {
		.dma_mask			= &rtl819x_ohci_dmamask,
		.coherent_dma_mask	= RTL819x_DMA_MASK,
	},
};

/*
 * EHCI (USB high/full speed host controller)
 */
static struct resource rtl819x_ehci_resources[] = {
	[0] = {
		.start	= PADDR(EHCI_RTL819x_USB_BASE),
		.end	= PADDR(EHCI_RTL819x_USB_BASE) + EHCI_RTL819x_USB_REG_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= RTL819x_USB_IRQ,
		.end	= RTL819x_USB_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

static u64 rtl819x_ehci_dmamask = RTL819x_DMA_MASK;

struct rtl819x_ehci_platform_data { 
    u8      is_rtl819x;
};

static struct rtl819x_ehci_platform_data rtl819x_ehci_data;

static struct platform_device rtl819x_ehci_device = {
	.name			= "rtl819x-ehci",
	.id				= -1,
	.resource		= rtl819x_ehci_resources,
	.num_resources	= ARRAY_SIZE(rtl819x_ehci_resources),
	.dev = {
		.dma_mask			= &rtl819x_ehci_dmamask,
		.coherent_dma_mask	= RTL819x_DMA_MASK,
		.platform_data		= &rtl819x_ehci_data,
	},
};

void SetUSBPhy(unsigned char reg, unsigned char val)
{
	
	#define	USB2_PHY_DELAY	{mdelay(5);}

	//8196C demo board: 0xE0:99, 0xE1:A8, 0xE2:98, 0xE3:C1,  0xE5:91, 	
	
#if !CONFIG_RTL_819XD //8198	
	REG32(0xb8000034) = (0x1f00 | val); USB2_PHY_DELAY;
#else  //8196D
	#define SYS_USB_SIE 0xb8000034
	#define SYS_USB_PHY 0xb8000090 	
 	int oneportsel=(REG32(SYS_USB_SIE) & (1<<18))>>18;
	
	unsigned int tmp = REG32(SYS_USB_PHY);  //8672 only	
	tmp = tmp & ~((0xff<<11)|(0xff<<0));

	
	if(oneportsel==0)
	{	REG32(SYS_USB_PHY) = (val << 0) | tmp;   //phy 0
	}
	else
	{	REG32(SYS_USB_PHY) = (val << 11) | tmp;  //phy1
	}

	USB2_PHY_DELAY;
#endif
	//printk("0xb8000034=%08x\n", REG32(0xb8000034));		
	
	unsigned char reg_h=(reg &0xf0)>>4;
	unsigned char reg_l=(reg &0x0f);
		
	mdelay(100);	
	REG32(0xb80210A4) = (0x00300000 | (reg_l<<16)); USB2_PHY_DELAY;
	REG32(0xb80210A4) = (0x00200000 | (reg_l<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00300000 | (reg_l<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00300000 | (reg_h<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00200000 | (reg_h<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00300000 | (reg_h<<16)); USB2_PHY_DELAY;
}

unsigned char GetUSBPhy(unsigned char reg)
{
	#define	USB2_PHY_DELAY	{mdelay(5);}

	unsigned char reg_h=((reg &0xf0)>>4)-2;
	unsigned char reg_l=(reg &0x0f);
		
	REG32(0xb80210A4) = (0x00300000 | (reg_l<<16)); USB2_PHY_DELAY;
	REG32(0xb80210A4) = (0x00200000 | (reg_l<<16)); USB2_PHY_DELAY;
	REG32(0xb80210A4) = (0x00300000 | (reg_l<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00300000 | (reg_h<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00200000 | (reg_h<<16)); USB2_PHY_DELAY;	
	REG32(0xb80210A4) = (0x00300000 | (reg_h<<16)); USB2_PHY_DELAY;	
	
	unsigned char val;
	val=REG32(0xb80210A4)>>24;
	//printk("reg=%x val=%x\n",reg, val);
	return val;
}

static void synopsys_usb_patch(void)
{

#define	USB2_PHY_DELAY	{int i=100; while(i>0) {i--;}}
	/* Patch: for USB 2.0 PHY */
#if !defined(CONFIG_RTL_8196C)
	/* For Port-0 */
	REG32(0xb8003314) = 0x0000000E;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00340000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00240000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00340000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x003E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x002E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x003E0000;	USB2_PHY_DELAY;
	REG32(0xb8003314) = 0x000000D8;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00360000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00260000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00360000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x003E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x002E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x003E0000;	USB2_PHY_DELAY;

	/* For Port-1 */
	REG32(0xb8003314) = 0x000E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00540000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00440000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00540000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x005E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x004E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x005E0000;	USB2_PHY_DELAY;
	REG32(0xb8003314) = 0x00D80000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00560000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00460000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x00560000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x005E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x004E0000;	USB2_PHY_DELAY;
	REG32(0xb80210A4) = 0x005E0000;	USB2_PHY_DELAY;
	
	printk("USB 2.0 Phy Patch(D): &0xb80210A4 = %08x\n", REG32(0xb80210A4));	/* A85E0000 */	

#elif defined(CONFIG_RTL_8196C)

	//disable Host chirp J-K
	SetUSBPhy(0xf4,0xe3);	GetUSBPhy(0xf4);
	//8196C demo board: 0xE0:99, 0xE1:A8, 0xE2:98, 0xE3:C1,  0xE5:91, 
	SetUSBPhy(0xe0,0x99);   if(GetUSBPhy(0xe0)!=0x99) printk("reg 0xe0 not correct\n");
	SetUSBPhy(0xe1,0xa8);	if(GetUSBPhy(0xe1)!=0xa8) printk("reg 0xe1 not correct\n");
	SetUSBPhy(0xe2,0x98);	if(GetUSBPhy(0xe2)!=0x98) printk("reg 0xe2 not correct\n");
	SetUSBPhy(0xe3,0xc1);	if(GetUSBPhy(0xe3)!=0xc1) printk("reg 0xe3 not correct\n");
	SetUSBPhy(0xe5,0x91);	if(GetUSBPhy(0xe5)!=0x91) printk("reg 0xe5 not correct\n");			
	
	//test packet.	
	/*
	REG32(0xb8021054)=0x85100000;
	REG32(0xb8021010)=0x08000100;
	REG32(0xb8021054)=0x85180400;
	*/
	printk("USB 2.0 PHY Patch Done.\n");

#else
	printk("========================== NO PATCH USB 2.0 PHY =====================\n");
#endif
	return;
}
//--------------------------------------------
void EnableUSBPHY(int portnum)
{
	if(portnum==0)
	{
	//phy0
	  REG32(0xb8000090) |= (1<<8);	 //USBPHY_EN=1
	  REG32(0xb8000090) |=   (1<<9);	 //usbphy_reset=1, active high		  
	  REG32(0xb8000090) &= ~(1<<9);	 //usbphy_reset=0, active high	  	  
	  REG32(0xb8000090) |= (1<<10);	 //active_usbphyt=1	  
	}
	else
	{
	//phy1
	  REG32(0xb8000090) |= (1<<19);	 //USBPHY_EN=1
	  REG32(0xb8000090) |=   (1<<20);	 //usbphy_reset=1, active high	 	  
	  REG32(0xb8000090) &= ~(1<<20);	 //usbphy_reset=0, active high	  
	  REG32(0xb8000090) |= (1<<21);	 //active_usbphyt=1	  
	}
}
 
static void __init rtl819x_usb_setup(void)
{

#if !defined(CONFIG_RTL_819XD)  //8198
	 REG32(0xb8000010)=REG32(0xb8000010)|(1<<17);
#else //8196D

	//one port sel
	//is 0: phy#1 connect OTG  mac, EHCI is in phy0	
	//is 1: phy#1 connect EHCI mac
	
#ifdef CONFIG_RTL_USB_OTG
	int oneportsel=0;
	REG32(0xb8000034) &= ~(1<<18);	 //one port sel=0
#else
#if 1  //software force
	int oneportsel=1;
	if(oneportsel==1)
	{	 REG32(0xb8000034) |= (1<<18);	 //one port sel=1
	}
	else
	{	REG32(0xb8000034) &= ~(1<<18);	 //one port sel=0
	}
#else  //read-back decide
	int oneportsel= (REG32(0xb8000034) & (1<<18))>>18;
	printk("EHCI: one_port_host_sel=%d, EHCI in Port %s\n", oneportsel, (oneportsel==0) ? "0": "1");
#endif
#endif
	 //sie
	 REG32(0xb8000034) |= (1<<11);	 //s_utmi_suspend0=1
	 REG32(0xb8000034) |= (1<<12);	 //en_usbhost=1	 
	 REG32(0xb8000034) |= (1<<17);	 //enable pgbndry_disable=1	 

	 if(oneportsel==1)
	 {
	 	EnableUSBPHY(1);
	 }	 
	 else 
	 {
	 	//phy0, phy1
#ifdef CONFIG_RTL_OTGCTRL	 
	 	extern unsigned int  TurnOn_OTGCtrl_Interrupt(unsigned int);
		unsigned int old= TurnOn_OTGCtrl_Interrupt(0);
#endif	
		EnableUSBPHY(0);
		EnableUSBPHY(1);
#ifdef CONFIG_RTL_OTGCTRL		  
	  TurnOn_OTGCtrl_Interrupt(old);
#endif	  
	 }
		 
	//ip clock mgr
	REG32(0xb8000010) |= (1<<12)|(1<<13)|(1<<19)|(1<<20);	 //enable lx1, lx2
	REG32(0xb8000010) |= (1<<21);	 //enable host ip

	mdelay(100);
	//printk("b8021000=%x\n", REG32(0xb8021000) );
	//printk("b8021054=%x\n", REG32(0xb8021054) );
#endif	 

	/*register platform device*/
	platform_device_register(&rtl819x_ehci_device);
	platform_device_register(&rtl819x_ohci_device);

#if defined(CONFIG_RTL_8196C)
	synopsys_usb_patch();
#endif


#if 0 //wei add
	//dump
	int i;
	for(i=0xe0;i<=0xe7; i++)
		printk("reg %x=%x\n", i,GetUSBPhy(i) );
	for(i=0xf0;i<=0xf6; i++)
		printk("reg %x=%x\n", i,GetUSBPhy(i) );	
#endif

	return 0;
}

void __init rtl819x_add_device_usb(void)
{
	rtl819x_usb_setup();
}

