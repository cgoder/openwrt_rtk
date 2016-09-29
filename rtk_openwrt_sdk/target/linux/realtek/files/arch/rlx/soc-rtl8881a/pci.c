/*
 * RTL8196B PCIE Host Controller Glue Driver
 * Author: ghhuang@realtek.com.tw
 *
 * Notes:
 * - Two host controllers available.
 * - Each host direcly connects to one device
 * - Supports PCI devices through PCIE-to-PCI bridges
 * - If no PCI devices are connected to RC. Timeout monitor shall be 
 *   enabled to prevent bus hanging.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <asm/rlxregs.h>
#include "bspchip.h"

#define PCI_8BIT_ACCESS    1
#define PCI_16BIT_ACCESS   2
#define PCI_32BIT_ACCESS   4
#define PCI_ACCESS_READ    8
#define PCI_ACCESS_WRITE   16

#define MAX_NUM_DEV  4

#define DEBUG_PRINTK 0
#define PIN_208 1
#define REG32(reg)      (*(volatile unsigned int   *)((unsigned int)reg))
static int pci0_bus_number = 0xff;
static int pci1_bus_number = 0xff;

static struct resource rtl8196b_pci0_io_resource = {
   .name   = "RTL8196B PCI0 IO",
   .flags  = IORESOURCE_IO,
   .start  = PADDR(BSP_PCIE0_D_IO),
   .end    = PADDR(BSP_PCIE0_D_IO + 0x1FFFFF)
};

static struct resource rtl8196b_pci0_mem_resource = {
   .name   = "RTL8196B PCI0 MEM",
   .flags  = IORESOURCE_MEM,
   .start  = PADDR(BSP_PCIE0_D_MEM),
   .end    = PADDR(BSP_PCIE0_D_MEM + 0xFFFFFF)
};

#ifdef PIN_208
static struct resource rtl8196b_pci1_io_resource = {
   .name   = "RTL8196B PCI1 IO",
   .flags  = IORESOURCE_IO,
   .start  = PADDR(BSP_PCIE1_D_IO),
   .end    = PADDR(BSP_PCIE1_D_IO + 0x1FFFFF)
};

static struct resource rtl8196b_pci1_mem_resource = {
   .name   = "RTL8196B PCI1 MEM",
   .flags  = IORESOURCE_MEM,
   .start  = PADDR(BSP_PCIE1_D_MEM),
   .end    = PADDR(BSP_PCIE1_D_MEM + 0xFFFFFF)
};
#endif
//HOST PCIE
#define PCIE0_RC_EXT_BASE (0xb8b01000)
#define PCIE1_RC_EXT_BASE (0xb8b21000)
//RC Extended register
#define PCIE0_MDIO	(PCIE0_RC_EXT_BASE+0x00)
#define PCIE1_MDIO	(PCIE1_RC_EXT_BASE+0x00)
//MDIO
#define PCIE_MDIO_DATA_OFFSET (16)
#define PCIE_MDIO_DATA_MASK (0xffff <<PCIE_MDIO_DATA_OFFSET)
#define PCIE_MDIO_REG_OFFSET (8)
#define PCIE_MDIO_RDWR_OFFSET (0)
int at2_mode=0;
void HostPCIe_SetPhyMdioWrite(unsigned int portnum, unsigned int regaddr, unsigned short val)
{
	unsigned int mdioaddr;

	if(portnum==0)		mdioaddr=PCIE0_MDIO;	
	else if(portnum==1)	mdioaddr=PCIE1_MDIO;
	else return 0;
	
	REG32(mdioaddr)= ( (regaddr&0x1f)<<PCIE_MDIO_REG_OFFSET) | ((val&0xffff)<<PCIE_MDIO_DATA_OFFSET)  | (1<<PCIE_MDIO_RDWR_OFFSET) ; 
	//delay 
	volatile int i;
	for(i=0;i<5555;i++)  ;
}

//----------------------------------------------------------------------------

void PCIE_MDIO_Reset(unsigned int portnum)
{
        #define SYS_PCIE_PHY0   (0xb8000000 +0x50)
        #define SYS_PCIE_PHY1   (0xb8000000 +0x54)	
	 
	unsigned int sys_pcie_phy;

	if(portnum==0)	sys_pcie_phy=SYS_PCIE_PHY0;
	else if(portnum==1)	sys_pcie_phy=SYS_PCIE_PHY1;
	else return;
		
       // 3.MDIO Reset
 	   REG32(sys_pcie_phy) = (1<<3) |(0<<1) | (0<<0);     //mdio reset=0,     	    
 	   REG32(sys_pcie_phy) = (1<<3) |(0<<1) | (1<<0);     //mdio reset=1,   
 	   REG32(sys_pcie_phy) = (1<<3) |(1<<1) | (1<<0);     //bit1 load_done=1

}
//------------------------------------------------------------------------
void PCIE_PHY_Reset(unsigned int portnum)
{
	 #define PCIE_PHY0 	0xb8b01008
	 #define PCIE_PHY1 	0xb8b21008
	 
	unsigned int pcie_phy;

	if(portnum==0)	pcie_phy=PCIE_PHY0;
	else if(portnum==1)	pcie_phy=PCIE_PHY1;
	else return;

        //4. PCIE PHY Reset       
	REG32(pcie_phy) = 0x01;	//bit7:PHY reset=0   bit0: Enable LTSSM=1
	REG32(pcie_phy) = 0x81;   //bit7: PHY reset=1   bit0: Enable LTSSM=1
	
}
//------------------------------------------------------------------------
int PCIE_Check_Link(unsigned int portnum)
{
	unsigned int dbgaddr;
	unsigned int cfgaddr;
	
	if(portnum==0)	dbgaddr=0xb8b00728;
	else if(portnum==1)	dbgaddr=0xb8b20728;
	else return;	

  //wait for LinkUP
#ifdef CONFIG_RTK_VOIP
	// accelerate when no pcie card 
	int i=3;
#else
	int i=20;
#endif
	while(--i)
	{
	      if( (REG32(dbgaddr)&0x1f)==0x11)
		  	break;
      		mdelay(300);		  

	}
	if(i==0)
	{	if(at2_mode==0)  //not auto test, show message
		printk("i=%x  Cannot LinkUP \n",i);
		return 0;
	}
	else
	{
		if(portnum==0) cfgaddr=0xb8b10000;
		else if(portnum==1) cfgaddr=0xb8b30000;

		REG32(cfgaddr+0x04)=0x00100007;

		if(at2_mode==0)
		{
		printk("Find Port=%x Device:Vender ID=%x\n", portnum, REG32(cfgaddr) );
		REG32(cfgaddr);
		mdelay(1);

		#ifdef CONFIG_RTL_819XD
		if (portnum == 0)
			REG32(BSP_GIMR) |= BSP_PCIE_IE;
		else
			REG32(BSP_GIMR) |= BSP_PCIE2_IE;
		#endif
		}
	}
	return 1;
}
//------------------------------------------------------------------------
#if 0
void PCIE_Device_PERST(void)
{
	 #define CLK_MANAGE 	0xb8000010
        // 6. PCIE Device Reset       
     REG32(CLK_MANAGE) &= ~(1<<26);    //perst=0 off.    
        mdelay(500);   //PCIE standadrd: poweron: 100us, after poweron: 100ms
        mdelay(500);  		
    REG32(CLK_MANAGE) |=  (1<<26);   //PERST=1
 	mdelay(500);
}
#endif
static void PCIE_Device_PERST(int portnum)
{
 #define CLK_MANAGE 	0xb8000010
 #define GPIO_BASE			0xB8003500
 #define PEFGHCNR_REG		(0x01C + GPIO_BASE)     /* Port EFGH control */
 #define PEFGHPTYPE_REG		(0x020 + GPIO_BASE)     /* Port EFGH type */
 #define PEFGHDIR_REG		(0x024 + GPIO_BASE)     /* Port EFGH direction */
 #define PEFGHDAT_REG		(0x028 + GPIO_BASE)     /* Port EFGH data */
	if (portnum==0)
	{
		REG32(CLK_MANAGE) &= ~(1<<26);    //perst=0 off.    
		mdelay(500);   //PCIE standadrd: poweron: 100us, after poweron: 100ms
		mdelay(500);  		
		REG32(CLK_MANAGE) |=  (1<<26);   //PERST=1
	}
	else if (portnum==1)
	{
	/*	PCIE Device Reset
	*	The pcei1 slot reset register depends on the hw
	*/
#if 1//defined(CONFIG_RTL_DUAL_PCIESLOT_BIWLAN) || (RTL_USED_PCIE_SLOT==1) || defined(CONFIG_RTL_DUAL_PCIESLOT_BIWLAN_D) 
		REG32(PEFGHDAT_REG) &= ~(0x1000);    //perst=0 off.  
		mdelay(300);   //PCIE standadrd: poweron: 100us, after poweron: 100ms
		mdelay(300); 
		REG32(PEFGHDAT_REG) |=  (0x1000);   //PERST=1
#elif defined(CONFIG_RTL_92D_SUPPORT)
		REG32(CLK_MANAGE) &= ~(1<<26);    //perst=0 off.    
		mdelay(500);   //PCIE standadrd: poweron: 100us, after poweron: 100ms
		mdelay(500);  		
		REG32(CLK_MANAGE) |=  (1<<26);   //PERST=1
#endif
	}
	else
		return;
}

//------------------------------------------------------------------------

int  OnlyOneReset()
{

	int result=0;
	int portnum=0;
	printk("PCIE RESET Only Once\n");


	#define CLK_MANAGE 	0xb8000010
#ifdef CONFIG_RTL_819XD
        REG32(CLK_MANAGE)|= (1<<12)|(1<<13)|(1<<19)|(1<<20)|(1<<18)|(1<<16);
#endif	
	REG32(CLK_MANAGE) &=  (~(1<<14));        //disable active_pcie0	
	REG32(CLK_MANAGE) |=  (1<<14); 		//enable active_pcie0 	

        #define PAD_CONTROL 0xb8000048
        REG32(PAD_CONTROL)|=(1<<27);   //switch to rc	
	REG32(CLK_MANAGE) &=  (~(1<<16));        //disable active_pcie1          
	REG32(CLK_MANAGE) |=  (1<<16); 		//enable active_pcie1 
	
	//PERST=1
	//REG32(CLK_MANAGE) |=  (1<<26);   
	//PCIE_Device_PERST(0); 
	

	
	for(portnum=0; portnum<2; portnum++)	
		PCIE_MDIO_Reset(portnum);
  	 mdelay(500);		
			
	for(portnum=0; portnum<2; portnum++)
	{
				#if 1//def RTL8198_FORMALCHIP_A
						HostPCIe_SetPhyMdioWrite(portnum, 0, 0xD087);  //bokai tell, and fix

						HostPCIe_SetPhyMdioWrite(portnum, 1, 0x0003);
						HostPCIe_SetPhyMdioWrite(portnum, 2, 0x4d18);
				#ifdef CONFIG_PHY_EAT_40MHZ				
						HostPCIe_SetPhyMdioWrite(portnum, 5, 0x0BCB);   //40M
				#endif

				#ifdef  CONFIG_PHY_EAT_40MHZ
						HostPCIe_SetPhyMdioWrite(portnum, 6, 0xF148);  //40M
				#else
						HostPCIe_SetPhyMdioWrite(portnum, 6, 0xf848);  //25M
				#endif

						HostPCIe_SetPhyMdioWrite(portnum, 7, 0x31ff);
	
				#ifdef CONFIG_RTL_819XD
						HostPCIe_SetPhyMdioWrite(portnum, 8, 0x18d6);  //peisi tune
				#else
						HostPCIe_SetPhyMdioWrite(portnum, 8, 0x18d7);  //peisi tune
				#endif
						HostPCIe_SetPhyMdioWrite(portnum, 0x09, 0x539c); 	
						HostPCIe_SetPhyMdioWrite(portnum, 0x0a, 0x20eb); 	
						HostPCIe_SetPhyMdioWrite(portnum, 0x0d, 0x1766);   
						//HostPCIe_SetPhyMdioWrite(portnum, 0x0d, 0x1464); 	//wei add		

						HostPCIe_SetPhyMdioWrite(portnum, 0x0b, 0x0511);   //for sloving low performance

						
						HostPCIe_SetPhyMdioWrite(portnum, 0xf, 0x0a00);	
						HostPCIe_SetPhyMdioWrite(portnum, 0x19, 0xFCE0);
						
						HostPCIe_SetPhyMdioWrite(portnum, 0x1a, 0x7e40);   //formal chip, reg 0x1a.4=0
						HostPCIe_SetPhyMdioWrite(portnum, 0x1b, 0xFC01);   //formal chip	 reg 0x1b.0=1		
						 
						HostPCIe_SetPhyMdioWrite(portnum, 0x1e, 0xC280);	

				#endif	
	}
	
	PCIE_Device_PERST(0);
        mdelay(500);		
	for(portnum=0; portnum<2; portnum++)	
		PCIE_PHY_Reset(portnum);
			  
        mdelay(500);
        mdelay(500);
        mdelay(500);        
      
      	
	for(portnum=0; portnum<2; portnum++)
	{	result=PCIE_Check_Link(portnum);
		if(result!=1)
			continue;

		
  #if 1	 //wei add patch
 
        //add compatible, slove sata pcie card.
	if(portnum==0)	  REG32(0xb8b0100c)=(1<<3);  //set target Device Num=1;
	if(portnum==1)	  REG32(0xb8b2100c)=(2<<3);  //set target Device Num=1;
	  
	unsigned int rc_cfg, cfgaddr;
	unsigned int iomapaddr;
	unsigned int memmapaddr;
	
#define PCIE0_RC_CFG_BASE (0xb8b00000)
#define PCIE0_RC_EXT_BASE (PCIE0_RC_CFG_BASE + 0x1000)
#define PCIE0_EP_CFG_BASE (0xb8b10000)

#define PCIE1_RC_CFG_BASE (0xb8b20000)
#define PCIE1_RC_EXT_BASE (PCIE1_RC_CFG_BASE + 0x1000)
#define PCIE1_EP_CFG_BASE (0xb8b30000)


#define PCIE0_MAP_IO_BASE  (0xb8c00000)
#define PCIE0_MAP_MEM_BASE (0xb9000000)

#define PCIE1_MAP_IO_BASE  (0xb8e00000)
#define PCIE1_MAP_MEM_BASE (0xba000000)		

#define MAX_READ_REQSIZE_128B    0x00
#define MAX_READ_REQSIZE_256B    0x10
#define MAX_READ_REQSIZE_512B    0x20
#define MAX_READ_REQSIZE_1KB     0x30
#define MAX_READ_REQSIZE_2KB     0x40
#define MAX_READ_REQSIZE_4KB     0x50

#define MAX_PAYLOAD_SIZE_128B    0x00
#define MAX_PAYLOAD_SIZE_256B    0x20
#define MAX_PAYLOAD_SIZE_512B    0x40
#define MAX_PAYLOAD_SIZE_1KB     0x60
#define MAX_PAYLOAD_SIZE_2KB     0x80
#define MAX_PAYLOAD_SIZE_4KB     0xA0
		
	if(portnum==0)
	{	rc_cfg=PCIE0_RC_CFG_BASE;
		cfgaddr=PCIE0_EP_CFG_BASE;
		iomapaddr=PCIE0_MAP_IO_BASE;
		memmapaddr=PCIE0_MAP_MEM_BASE;
	}
	else if(portnum==1)
	{	rc_cfg=PCIE1_RC_CFG_BASE;
		cfgaddr=PCIE1_EP_CFG_BASE;
		iomapaddr=PCIE1_MAP_IO_BASE;
		memmapaddr=PCIE1_MAP_MEM_BASE;	
	}
	//STATUS
	//bit 4: capabilties List

	//CMD
	//bit 2: Enable Bys master, 
	//bit 1: enable memmap, 
	//bit 0: enable iomap
	REG32(rc_cfg + 0x04)= 0x00100007;   

	//Device Control Register 
	//bit [7-5]  payload size
	REG32(rc_cfg + 0x78)= (REG32(rc_cfg + 0x78 ) & (~0xE0)) | MAX_PAYLOAD_SIZE_128B;  // Set MAX_PAYLOAD_SIZE to 128B,default	  
	REG32(cfgaddr + 0x04)= 0x00100007;    //0x00180007

	//bit 0: 0:memory, 1 io indicate
	//REG32(cfgaddr + 0x10)= (iomapaddr | 0x00000001) & 0x1FFFFFFF;  // Set BAR0

	//bit 3: prefetch
	//bit [2:1] 00:32bit, 01:reserved, 10:64bit 11:reserved
	//REG32(cfgaddr + 0x18)= (memmapaddr | 0x00000004) & 0x1FFFFFFF;  // Set BAR1  

	//offset 0x78 [7:5]
	REG32(cfgaddr + 0x78) = (REG32(cfgaddr + 0x78) & (~0xE0)) | (MAX_PAYLOAD_SIZE_128B);  // Set MAX_PAYLOAD_SIZE to 128B

	//offset 0x79: [6:4] 
	REG32(cfgaddr + 0x78) = (REG32(cfgaddr + 0x78) & (~0x7000)) | (MAX_READ_REQSIZE_256B<<8);  // Set MAX_REQ_SIZE to 256B,default
	
	//io and mem limit, setting to no litmit
	REG32(rc_cfg+ 0x1c) = (2<<4) | (0<<12);   //  [7:4]=base  [15:12]=limit
	REG32(rc_cfg+ 0x20) = (2<<4) | (0<<20);   //  [15:4]=base  [31:20]=limit	
	REG32(rc_cfg+ 0x24) = (2<<4) | (0<<20);   //  [15:4]=base  [31:20]=limit	
#endif	
	}

	return 1;
	
}
//=====================================================================
//#define PHY_EAT_40MHZ 1
#define CLK_MANAGE     0xb8000010
int  PCIE_reset_procedure(int portnum, int Use_External_PCIE_CLK, int mdio_reset)
{
 //	dprintf("port=%x, mdio_rst=%x \n", portnum, mdio_reset);
	int result=0;	

 	//first, Turn On PCIE IP
	 #define CLK_MANAGE 	0xb8000010
	if(portnum==0)		    REG32(CLK_MANAGE) |=  (1<<14);        //enable active_pcie0
	else if(portnum==1)	    REG32(CLK_MANAGE) |=  (1<<16);        //enable active_pcie1	
	else return result;
	if (portnum==0)
	{
		REG32(CLK_MANAGE) |=  (1<<26);   //PERST=1
	}
	else if (portnum==1)
	{
		REG32(0xb8000040)|=0x300;
		REG32(PEFGHCNR_REG) &= ~(0x1000);	/*port F bit 4 */
		REG32(PEFGHDIR_REG) |= (0x1000);	/*port F bit 4 */
		REG32(PEFGHDAT_REG) |=  (0x1000);   //PERST=1
	}    
#ifdef CONFIG_RTL_819XD
	REG32(CLK_MANAGE) |= (1<<12)| (1<<13)|(1<<18);
#endif
	mdelay(500);
  	#ifdef CONFIG_RTL8198_REVISION_B
                if(portnum==1)
                {
                        #define PAD_CONTROL 0xb8000048
                        REG32(PAD_CONTROL)|=(1<<27);
                }
        #endif
 

	if(mdio_reset)
	{
		if(at2_mode==0)  //no auto test, show message
			printk("Do MDIO_RESET\n");
		mdelay(1);
       	// 3.MDIO Reset
		PCIE_MDIO_Reset(portnum);
	}  
/*	
 	PCIE_PHY_Reset(portnum);	
 */	
        mdelay(500);
        mdelay(500);
 
	  //----------------------------------------
	  if(mdio_reset)
	  	{
			//fix 8198 test chip pcie tx problem.	
#if defined(CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD)
			if ((REG32(BSP_REVR) >= BSP_RTL8198_REVISION_B) || ((REG32(BSP_REVR)&0xfffff000) == BSP_RTL8197D))				
			{
				#if 1//def RTL8198_FORMALCHIP_A
						HostPCIe_SetPhyMdioWrite(portnum, 0, 0xD087);  //bokai tell, and fix

						HostPCIe_SetPhyMdioWrite(portnum, 1, 0x0003);
						HostPCIe_SetPhyMdioWrite(portnum, 2, 0x4d18);
				#ifdef CONFIG_PHY_EAT_40MHZ
						HostPCIe_SetPhyMdioWrite(portnum, 5, 0x0BCB);   //40M
				#endif

				#ifdef  CONFIG_PHY_EAT_40MHZ
						HostPCIe_SetPhyMdioWrite(portnum, 6, 0xF148);  //40M
				#else
						HostPCIe_SetPhyMdioWrite(portnum, 6, 0xf848);  //25M
				#endif

						HostPCIe_SetPhyMdioWrite(portnum, 7, 0x31ff);
						HostPCIe_SetPhyMdioWrite(portnum, 8, 0x18d5);  //peisi tune

				#if 0       //old,		
						HostPCIe_SetPhyMdioWrite(portnum, 9, 0x531c); 		
						HostPCIe_SetPhyMdioWrite(portnum, 0xd, 0x1766); //peisi tune
				#else     //saving more power, 8196c pe-si tune
						HostPCIe_SetPhyMdioWrite(portnum, 0x09, 0x539c); 	
						HostPCIe_SetPhyMdioWrite(portnum, 0x0a, 0x20eb); 	
						HostPCIe_SetPhyMdioWrite(portnum, 0x0d, 0x1766); 			
				#endif
#ifdef CONFIG_RTL_819XD
						HostPCIe_SetPhyMdioWrite(portnum, 0x0b, 0x0711);   //for sloving low performance
#else
						HostPCIe_SetPhyMdioWrite(portnum, 0x0b, 0x0511);   //for sloving low performance
#endif
						
						HostPCIe_SetPhyMdioWrite(portnum, 0xf, 0x0a00);	
						HostPCIe_SetPhyMdioWrite(portnum, 0x19, 0xFCE0);
						
						HostPCIe_SetPhyMdioWrite(portnum, 0x1a, 0x7e4f);   //formal chip, reg 0x1a.4=0
						HostPCIe_SetPhyMdioWrite(portnum, 0x1b, 0xFC01);   //formal chip	 reg 0x1b.0=1		
						 
						HostPCIe_SetPhyMdioWrite(portnum, 0x1e, 0xC280);	

				#endif

			}
			else
#endif
			{
//#define PHY_USE_TEST_CHIP 1   // 1: test chip, 0: fib chip
//#define PHY_EAT_40MHZ 0   // 0: 25MHz, 1: 40MHz

		//HostPCIe_SetPhyMdioWrite(portnum, 0, 0xD187);//ori
		HostPCIe_SetPhyMdioWrite(portnum, 0, 0xD087);
		
		HostPCIe_SetPhyMdioWrite(portnum, 1, 0x0003);
		//HostPCIe_SetPhyMdioWrite(portnum, 2, 0x4d18);
		HostPCIe_SetPhyMdioWrite(portnum, 6, 0xf448); //new
		HostPCIe_SetPhyMdioWrite(portnum, 6, 0x408); 	//avoid noise infuse	 //15-12=0, 7-5=0,    0448
		
		HostPCIe_SetPhyMdioWrite(portnum, 7, 0x31ff);
		HostPCIe_SetPhyMdioWrite(portnum, 8, 0x18d5);  //new		
		HostPCIe_SetPhyMdioWrite(portnum, 9, 0x531c); 		

		//HostPCIe_SetPhyMdioWrite(portnum, 0xa, 0x00C9);
		//HostPCIe_SetPhyMdioWrite(portnum, 0xb, 0xe511);
		//HostPCIe_SetPhyMdioWrite(portnum, 0xc, 0x0820); 		
		HostPCIe_SetPhyMdioWrite(portnum, 0xd, 0x1766); 
		HostPCIe_SetPhyMdioWrite(portnum, 0xf, 0x0010);//ori
		// HostPCIe_SetPhyMdioWrite(portnum, 0xf, 0x0a00);				

		HostPCIe_SetPhyMdioWrite(portnum, 0x19, 0xFCE0); 
		HostPCIe_SetPhyMdioWrite(portnum, 0x1e, 0xC280);	


		
#if 0 //saving more power
		HostPCIe_SetPhyMdioWrite(0xa, 0xeb);
		HostPCIe_SetPhyMdioWrite(0x9, 0x538c);
		
//		HostPCIe_SetPhyMdioWrite(0xc, 0xC828);  //original 
//		HostPCIe_SetPhyMdioWrite(0x0, 0x502F);  //fix
		
		HostPCIe_SetPhyMdioWrite(0xc, 0x8828);  //new
		HostPCIe_SetPhyMdioWrite(0x0, 0x502F);  //fix		
#endif
			}
	  	}
 
	//---------------------------------------
	PCIE_Device_PERST(portnum);

	PCIE_PHY_Reset(portnum);	  
        mdelay(500);
        mdelay(500);
	result=PCIE_Check_Link(portnum);
	#if 0 
        if(portnum==0)
        {
        	if(result)
        	{
              WRITE_MEM32(BSP_PCIE0_H_PWRCR, READ_MEM32(BSP_PCIE0_H_PWRCR) & 0xFFFFFF7F);
           		mdelay(100);
           		WRITE_MEM32(BSP_PCIE0_H_PWRCR, READ_MEM32(BSP_PCIE0_H_PWRCR) | 0x00000080);
        	}
        }
        else
        {
        #ifdef PIN_208
                if(result)
   	        {
                   WRITE_MEM32(BSP_PCIE1_H_PWRCR, READ_MEM32(BSP_PCIE1_H_PWRCR) & 0xFFFFFF7F);
                   mdelay(100);
                   WRITE_MEM32(BSP_PCIE1_H_PWRCR, READ_MEM32(BSP_PCIE1_H_PWRCR) | 0x00000080);
        	}
        #endif
        }
  #endif
	return result;














}
//========================================================================================

static int rtl8196b_pci_reset(void)
{
   /* If PCI needs to be reset, put code here.
    * Note: 
    *    Software may need to do hot reset for a period of time, say ~100us.
    *    Here we put 2ms.
    */
#if 1
//Modified for PCIE PHY parameter due to RD center suggestion by Jason 12252009 
WRITE_MEM32(0xb8000044, 0x9);//Enable PCIE PLL
mdelay(10);
//WRITE_MEM32(0xb8000010, 0x00FFFFD6);//Active LX & PCIE Clock in 8196B system register
WRITE_MEM32(0xb8000010, READ_MEM32(0xb8000010)|(1<<8)|(1<<9)|(1<<10));
#ifdef PIN_208
WRITE_MEM32(0xb8000010, READ_MEM32(0xb8000010)|(1<<12));
#endif
mdelay(10);
WRITE_MEM32(0xb800003C, 0x1);//PORT0 PCIE PHY MDIO Reset
mdelay(10);
WRITE_MEM32(0xb800003C, 0x3);//PORT0 PCIE PHY MDIO Reset
mdelay(10);
#ifdef PIN_208
WRITE_MEM32(0xb8000040, 0x1);//PORT1 PCIE PHY MDIO Reset
mdelay(10);
WRITE_MEM32(0xb8000040, 0x3);//PORT1 PCIE PHY MDIO Reset
mdelay(10);
#endif
WRITE_MEM32(0xb8b01008, 0x1);// PCIE PHY Reset Close:Port 0
mdelay(10);
WRITE_MEM32(0xb8b01008, 0x81);// PCIE PHY Reset On:Port 0
mdelay(10);
#ifdef PIN_208
WRITE_MEM32(0xb8b21008, 0x1);// PCIE PHY Reset Close:Port 1
mdelay(10);
WRITE_MEM32(0xb8b21008, 0x81);// PCIE PHY Reset On:Port 1
mdelay(10);
#endif
#ifdef OUT_CYSTALL
WRITE_MEM32(0xb8b01000, 0xcc011901);// PCIE PHY Reset On:Port 0
mdelay(10); 
#ifdef PIN_208
WRITE_MEM32(0xb8b21000, 0xcc011901);// PCIE PHY Reset On:Port 1
mdelay(10); 
#endif
#endif
//WRITE_MEM32(0xb8000010, 0x01FFFFD6);// PCIE PHY Reset On:Port 1
WRITE_MEM32(0xb8000010, READ_MEM32(0xb8000010)|(1<<24));
mdelay(10);
#endif
   WRITE_MEM32(BSP_PCIE0_H_PWRCR, READ_MEM32(BSP_PCIE0_H_PWRCR) & 0xFFFFFF7F);
#ifdef PIN_208
   WRITE_MEM32(BSP_PCIE1_H_PWRCR, READ_MEM32(BSP_PCIE1_H_PWRCR) & 0xFFFFFF7F);
#endif
   mdelay(100);
   WRITE_MEM32(BSP_PCIE0_H_PWRCR, READ_MEM32(BSP_PCIE0_H_PWRCR) | 0x00000080);
#ifdef PIN_208
   WRITE_MEM32(BSP_PCIE1_H_PWRCR, READ_MEM32(BSP_PCIE1_H_PWRCR) | 0x00000080);
#endif
   return 0;
}

static int rtl8196b_pcibios_config_access(unsigned char access_type,
       unsigned int addr, unsigned int *data)
{
   /* Do 8bit/16bit/32bit access */
   if (access_type & PCI_ACCESS_WRITE)
   {
      if (access_type & PCI_8BIT_ACCESS)
         WRITE_MEM8(addr, *data);
      else if (access_type & PCI_16BIT_ACCESS)
         WRITE_MEM16(addr, *data);
      else
         WRITE_MEM32(addr, *data);
   }
   else if (access_type & PCI_ACCESS_READ)
   {
      if (access_type & PCI_8BIT_ACCESS) { 
      #ifdef CONFIG_RTL8198_REVISION_B  
         unsigned int data_temp=0;  int swap[4]={0,8,16,24};  int diff = addr&0x3;
        data_temp=READ_MEM32(addr);
        *data=(unsigned int)(( data_temp>>swap[diff])&0xff);

#else
         *data = READ_MEM8(addr);
#endif
       } else if (access_type & PCI_16BIT_ACCESS) { 
       #ifdef CONFIG_RTL8198_REVISION_B  
        unsigned int data_temp=0;  int swap[4]={0,8,16,24};  int diff = addr&0x3;
        data_temp=READ_MEM32(addr);
        *data=(unsigned int)(( data_temp>>swap[diff])&0xffff);

#else
         *data = READ_MEM16(addr);
#endif
      } else
         *data = READ_MEM32(addr);
   }

   /* If need to check for PCIE access timeout, put code here */
   /* ... */

   return 0;
}


//========================================================================================
/*
 * RTL8196b supports config word read access for 8/16/32 bit
 *
 * FIXME: currently only utilize 32bit access
 */
static int rtl8196b_pcibios0_read(struct pci_bus *bus, unsigned int devfn,
                                  int where, int size, unsigned int *val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   if (pci0_bus_number == 0xff)
      pci0_bus_number = bus->number;
   #if DEBUG_PRINTK
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci0_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_H_CFG + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            *val = (data >> ((where & 3) << 3)) & 0xff;
         else if (size == 2)
            *val = (data >> ((where & 3) << 3)) & 0xffff;
         else
            *val = data;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci0_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE0_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE0_D_CFG1 + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
REG32(0xb8000014)=0x800200;
   #if DEBUG_PRINTK
   printk("0xb8000014:%x\n",REG32(0xb8000014));
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Read Value: 0x%08X\n", *val);
   #endif

   return PCIBIOS_SUCCESSFUL;
}

//========================================================================================
static int rtl8196b_pcibios0_write(struct pci_bus *bus, unsigned int devfn,
                                   int where, int size, unsigned int val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   static int pci0_bus_number = 0xff;
   if (pci0_bus_number == 0xff)
      pci0_bus_number = bus->number;

   #if DEBUG_PRINTK
   //printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci0_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_H_CFG + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            data = (data & ~(0xff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else if (size == 2)
            data = (data & ~(0xffff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else
            data = val;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_WRITE | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci0_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE0_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE0_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE0_D_CFG1 + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }

   return PCIBIOS_SUCCESSFUL;
}
//========================================================================================

/*
 * RTL8196b supports config word read access for 8/16/32 bit
 *
 * FIXME: currently only utilize 32bit access
 */
#ifdef PIN_208
static int rtl8196b_pcibios1_read(struct pci_bus *bus, unsigned int devfn,
                                  int where, int size, unsigned int *val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   if (pci1_bus_number == 0xff)
      pci1_bus_number = bus->number;

   #if DEBUG_PRINTK
   printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   printk("Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif

   if (bus->number == pci1_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_H_CFG + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            *val = (data >> ((where & 3) << 3)) & 0xff;
         else if (size == 2)
            *val = (data >> ((where & 3) << 3)) & 0xffff;
         else
            *val = data;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci1_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE1_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE1_D_CFG1 + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | size, addr, val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }

   #if DEBUG_PRINTK
   printk("0xb8000014:%x\n",REG32(0xb8000014));
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Read Value: 0x%08X\n", *val);
   #endif

   return PCIBIOS_SUCCESSFUL;
}

//========================================================================================
static int rtl8196b_pcibios1_write(struct pci_bus *bus, unsigned int devfn,
                                   int where, int size, unsigned int val)
{
   unsigned int data = 0;
   unsigned int addr = 0;

   static int pci1_bus_number = 0xff;

   if (pci1_bus_number == 0xff)
      pci1_bus_number = bus->number;

   #if DEBUG_PRINTK
   printk("0xb8000014:%x\n",REG32(0xb8000014));
	//printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   //printk("Bus: %d, Slot: %d, Func: %d, Where: %d, Size: %d\n", bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size);
   #endif


   if (bus->number == pci1_bus_number)
   {
      /* PCIE host controller */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_H_CFG + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_READ | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;

         if (size == 1)
            data = (data & ~(0xff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else if (size == 2)
            data = (data & ~(0xffff << ((where & 3) << 3))) | (val << ((where & 3) << 3));
         else
            data = val;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_WRITE | PCI_32BIT_ACCESS, addr & ~(0x3), &data))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else if (bus->number == (pci1_bus_number + 1))
   {
      /* PCIE devices directly connected */
      if (PCI_SLOT(devfn) == 0)
      {
         addr = BSP_PCIE1_D_CFG0 + (PCI_FUNC(devfn) << 12) + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }
   else
   {
      /* Devices connected through bridge */
      if (PCI_SLOT(devfn) < MAX_NUM_DEV)
      {
         WRITE_MEM32(BSP_PCIE1_H_IPCFG, ((bus->number) << 8) | (PCI_SLOT(devfn) << 3) | PCI_FUNC(devfn));
         addr = BSP_PCIE1_D_CFG1 + where;

         if (rtl8196b_pcibios_config_access(PCI_ACCESS_WRITE | size, addr, &val))
            return PCIBIOS_DEVICE_NOT_FOUND;
      }
      else
         return PCIBIOS_DEVICE_NOT_FOUND;
   }

   return PCIBIOS_SUCCESSFUL;
}
#endif
//========================================================================================
struct pci_ops rtl8196b_pci0_ops = {
   .read = rtl8196b_pcibios0_read,
   .write = rtl8196b_pcibios0_write
};

#ifdef PIN_208
struct pci_ops rtl8196b_pci1_ops = {
   .read = rtl8196b_pcibios1_read,
   .write = rtl8196b_pcibios1_write
};
#endif

static struct pci_controller rtl8196b_pci0_controller = {
   .pci_ops        = &rtl8196b_pci0_ops,
   .mem_resource   = &rtl8196b_pci0_mem_resource,
   .io_resource    = &rtl8196b_pci0_io_resource,
};

#ifdef PIN_208
static struct pci_controller rtl8196b_pci1_controller = {
   .pci_ops        = &rtl8196b_pci1_ops,
   .mem_resource   = &rtl8196b_pci1_mem_resource,
   .io_resource    = &rtl8196b_pci1_io_resource,
};
#endif
//========================================================================================
int pcibios_map_irq(struct pci_dev *dev, u8 slot, u8 pin)
{
   #if DEBUG_PRINTK
   printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   printk("**Slot: %d\n", slot);
   printk("**Pin: %d\n", pin);
   printk("**Dev->BUS->Number: %d\n", dev->bus->number);
   #endif

   if (dev->bus->number < pci1_bus_number)
      return BSP_PCIE_IRQ;
   else
      return BSP_PCIE2_IRQ;
}
//========================================================================================
/* Do platform specific device initialization at pci_enable_device() time */
int pcibios_plat_dev_init(struct pci_dev *dev)
{
   #if DEBUG_PRINTK
   printk("File: %s, Function: %s, Line: %d\n", __FILE__, __FUNCTION__, __LINE__);
   #endif

   return 0;
}

static __init int bsp_pcie_init(void)
{
	int Use_External_PCIE_CLK=0;
	int result=0,result1=0;
	 printk("<<<<<Register 1st PCI Controller>>>>>\n");
	mdelay(1);

#ifndef CONFIG_RTL_DUAL_PCIESLOT_BIWLAN_D
#ifndef PIN_208
   	result=PCIE_reset_procedure(0, Use_External_PCIE_CLK, 1);
#else
	result=PCIE_reset_procedure(0, Use_External_PCIE_CLK, 1);
	mdelay(1);
	result1=PCIE_reset_procedure(1, Use_External_PCIE_CLK, 1);
#endif
#else //wei add
	OnlyOneReset();
	
	result=PCIE_Check_Link(0);
	result1=PCIE_Check_Link(1);

#endif

#if DEBUG_PRINTK
   printk("<<<<<Register 1st PCI Controller>>>>>\n");
#ifdef PIN_208
   printk("<<<<<Register 2nd PCI Controller>>>>>\n");
#endif
#endif
	mdelay(1);
#ifndef CONFIG_RTL_DUAL_PCIESLOT_BIWLAN_D
   if(result)
   register_pci_controller(&rtl8196b_pci0_controller);
   else
   {
	 REG32(CLK_MANAGE) &=  (~(1<<14));        //disable active_pcie0
   }
#ifdef PIN_208
   if(result1)
   register_pci_controller(&rtl8196b_pci1_controller);
   else
   {
	REG32(CLK_MANAGE) &=  (~(1<<16));        //disable active_pcie1
   }
#endif
#else

   if(result1)
   register_pci_controller(&rtl8196b_pci1_controller);
   else
   {	REG32(CLK_MANAGE) &=  (~(1<<16));        //disable active_pcie1
   }


   if(result)
   register_pci_controller(&rtl8196b_pci0_controller);
   else
   {	 REG32(CLK_MANAGE) &=  (~(1<<14));        //disable active_pcie0
   }


#endif
   return 0;
}

arch_initcall(bsp_pcie_init);
