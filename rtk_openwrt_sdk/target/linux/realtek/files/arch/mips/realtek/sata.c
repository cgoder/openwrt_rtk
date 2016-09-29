/*
 * Realtek Semiconductor Corp.
 *
 * bsp/usb.c:
 *     bsp SATA initialization code
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>

#include <asm/mach-realtek/bspchip.h>


// PHY patch part , rtk's sata phy patch , by wei

//=================================================================
static u32 AUREG32_R(u32  reg)
{	volatile u32 tmp;
	tmp=REG32(reg);
	//printk("AR:(%x)=%x\n",(u32)reg,tmp);
	return tmp;
}
//-------------------------------------------------------
static void AUREG32_W(u32  reg,u32 value)
{
	//printk("AW:(%x)=%x\n",(u32)reg,value);
	REG32(reg)=(value);
}

static u32 sata_phy_read(u32 portnum, u32 addr)
{
	//AUREG32_W(0xb82ea008, (0<<31)|(1<<22) | (addr<<16) );	//patch
	u32 pmdio_addr;
	if(portnum==0)		pmdio_addr=0xb82ea008;
	else			pmdio_addr=0xb82ea008+0x20;
	
	AUREG32_W(pmdio_addr, (0<<31)|(1<<22) | (addr<<16) );	
	//mdelay(10);
	while( (AUREG32_R(pmdio_addr) &(1<<31))==0 ) {};  //auto reverse when hw complete. 

	u32 r=(AUREG32_R(pmdio_addr)&0xffff);
	return r;	
}
//--------------------------------------------------------------------
static void sata_phy_write(u32 portnum, u32 addr,u32 val)
{
	u32 tmp;
	u32 pmdio_addr;
	//AUREG32_W(0xb82ea008, (1<<31)|(1<<22)|(addr<<16)|(val&0xffff));   //patch
	
	if(portnum==0)		pmdio_addr=0xb82ea008;
	else			pmdio_addr=0xb82ea008+0x20;
	
	AUREG32_W(pmdio_addr, (1<<31)|(1<<22)|(addr<<16)|(val&0xffff)); 		
	printk("write reg=%x v=%x",addr,val);
		
	//mdelay(10*20);
	while( AUREG32_R(pmdio_addr) &(1<<31) ) {};  //auto reverse when hw complete. 
		
	tmp=sata_phy_read(portnum, addr);	
	
	if(tmp!=val) 	printk("  Error, read_back=%x\n",tmp);
	else		printk("\n");
	
//		printk("write addr=%x, value=%x, read_back=%x\n",addr,val,tmp);
}

static void sata_mdio_reset(u32 portnum)
{
	u32 aux_base = (void __iomem *)0xb82ea000;

	// Reset MDC/MDIO
	if(portnum==0)
	{
		AUREG32_W(aux_base, AUREG32_R(aux_base) & ~(1<<25)); //phy mdc/mdio reset
		mdelay(100);
		AUREG32_W(aux_base, AUREG32_R(aux_base) | (1<<25)); //phy mdc/mdio reset clear
		mdelay(100);
	}
	else
	{
		AUREG32_W(aux_base, AUREG32_R(aux_base) & ~(1<<11)); //phy mdc/mdio reset
		mdelay(100);
		AUREG32_W(aux_base, AUREG32_R(aux_base) | (1<<11)); //phy mdc/mdio reset clear
		mdelay(100);
	}
}

void set_sata_phy_param_for_port(u32 portnum)
{
spinlock_t my_lock;
 spin_lock_init(&my_lock);
 spin_lock(&my_lock);

        int i;
        printk("===========================\nSet PHY Parameter PORT %d\n", portnum);
        printk("SATA:0224 PHY parameter.\n");
        sata_phy_write(portnum, 0x00, 0x5144);
        sata_phy_write(portnum, 0x01, 0x0001);
        sata_phy_write(portnum, 0x02, 0x2308);
        sata_phy_write(portnum, 0x04, 0x2000);
        sata_phy_write(portnum, 0x06, 0xf438);
        sata_phy_write(portnum, 0x09, 0x538c);
        sata_phy_write(portnum, 0x0a, 0x2028);
        sata_phy_write(portnum, 0x0d, 0x1264);

//      sata_phy_write(portnum, 0x09, 0x9300); //wei add        , new
        //sata_phy_write(0x10, 0x1F80);   //phy dbg port

        AUREG32_W(0xb82ea000, AUREG32_R(0xb82ea000)| (0x7<<16));   //mac dbg port
        //AUREG32_W(0xb82ea00c, AUREG32_R(0xb82ea00c)| (1<<17));  //force phy reset

        AUREG32_W(0xb82ea000, AUREG32_R(0xb82ea000)& ~(0x3<<22));   //180 degree
        AUREG32_W(0xb82ea000, AUREG32_R(0xb82ea000)| (0x2<<22));   //
//dump all phy reg
#if 0
        for(i=0; i<=0x1f; i++)
        printk("=> phy reg %x, v=%x\n", i, sata_phy_read(portnum, i));
#endif

 spin_unlock(&my_lock);

}

static void realtek_sata_phypatch()
{
	u8 *base = (void __iomem *)0xb82e8000;
#if 0
        if((REG32_R(base+0x110)&0x80000080)==0x80000080)
        {
                REG32_W(base+0x110,0x80000080);
                mdelay(10);
        }

        printk("110=%x 118=%x hotplug_change=%d\n",REG32_R(base+0x110),REG32_R(base+0x118),hotplug_change);
        REG32(aux_base+0xc)=0x10011; //for hot-plug test (by hanyi: 10011:by outside signal, 10022:force 0, 10033: force 1)

#endif



        printk("set PHY Params\n");

#if 1
        //REG32(0xb8000010) &= ~(1<<11);  //disable switch
        REG32(0xb800010c)= (REG32(0xb800010c)&~(3<<21)) | (1<<21);  //P5TXC -> SATA
#endif

        #define CLK_MGR 0xb8000010
        REG32(CLK_MGR)|=(1<<24) | (1<<19) | (1<<20);  //enable sata ip

#ifndef SATA_REG_LITTLE_ENDIAN
        //swap register
        REG32(0xb82ea000) &= ~(1<<30);
#endif

        //enable sata phy power
        #define SYS_SATA_0 0xb8000040
        #define SYS_SATA_1 0xb8000044
/*
        REG32(SYS_SATA_0)|=(1<<0);
        REG32(SYS_SATA_1)|=(1<<0);
*/
        REG32(SYS_SATA_0)=0xff;
        REG32(SYS_SATA_1)=0xff;

#if 1 //I'm BIOS setting HWInit & HOTPLUG
        //HWINIT
        writel( (1<<28),base+0x00);     //CAP
        writel( (1<<20)|(1<<19),base+0x118);    //P0CMD
        writel( (1<<20)|(1<<19),base+0x198);    //P1CMD

#endif
        sata_mdio_reset(0);
        set_sata_phy_param_for_port(0);
        sata_mdio_reset(1);
        set_sata_phy_param_for_port(1);
/*
        REG32(base)=REG32(base)|0x10000000; //enable mp switch
*/
        //printk("power on ...wait port reset\n");
        //mdelay(1000);
		

}
// BSP part
static void realtek_sata_phy_init(void)
{
	realtek_sata_phypatch();
}

/* SATA Host Controller */

static struct resource bsp_sata_resource[] = {
	[0] = {
		.start = BSP_SATA_MAPBASE,
		.end = BSP_SATA_MAPBASE + BSP_SATA_MAPSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = BSP_PS_SATA_IRQ,
		.end = BSP_PS_SATA_IRQ,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 bsp_sata_dmamask = 0xFFFFFFFFUL;

struct platform_device bsp_sata_device = {
	//.name = "dwc_sata",
	.name = "ahci", //name should match to ahci driver
	.id = -1,
	.num_resources = ARRAY_SIZE(bsp_sata_resource),
	.resource = bsp_sata_resource,
	.dev = {
		.dma_mask = &bsp_sata_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

static struct platform_device *bsp_sata_devs[] __initdata = {	&bsp_sata_device,  };

static int __init bsp_sata_init(void)
{
	int ret;

	printk("INFO: initializing SATA devices ...\n");

	realtek_sata_phy_init();

	ret = platform_add_devices(bsp_sata_devs, ARRAY_SIZE(bsp_sata_devs));
	if (ret < 0) {
		printk("ERROR: unable to add devices\n");
		return ret;
	}

	return 0;
}
arch_initcall(bsp_sata_init);
