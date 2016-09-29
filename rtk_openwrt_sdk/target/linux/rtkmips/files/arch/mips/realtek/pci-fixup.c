/*
 * Realtek Semiconductor Corp.
 *
 * bsp/pci-fixup.c
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/delay.h>

#include <asm/io.h>

//#include "bspchip.h"
#include <asm/mach-realtek/bspchip.h>

// -----------------------rtk PCI init part 
#define PCIE0_RC_EXT_BASE (0xb8b01000)
#define PCIE1_RC_EXT_BASE (0xb8b21000)
//RC Extended register
#define PCIE0_MDIO      (PCIE0_RC_EXT_BASE+0x00)
#define PCIE1_MDIO      (PCIE1_RC_EXT_BASE+0x00)
//MDIO
#define PCIE_MDIO_DATA_OFFSET (16)
#define PCIE_MDIO_DATA_MASK (0xffff <<PCIE_MDIO_DATA_OFFSET)
#define PCIE_MDIO_REG_OFFSET (8)
#define PCIE_MDIO_RDWR_OFFSET (0)

#define CLK_MANAGE 	0xb8000010
 #define GPIO_BASE			0xB8003500
 #define PEFGHCNR_REG		(0x01C + GPIO_BASE)     /* Port EFGH control */
 #define PEFGHPTYPE_REG		(0x020 + GPIO_BASE)     /* Port EFGH type */
 #define PEFGHDIR_REG		(0x024 + GPIO_BASE)     /* Port EFGH direction */
 #define PEFGHDAT_REG		(0x028 + GPIO_BASE)     /* Port EFGH data */
 

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

void HostPCIe_SetPhyMdioWrite(unsigned int portnum, unsigned int regaddr, unsigned short val)
{
	unsigned int mdioaddr;
	volatile int i;
	if(portnum==0)		mdioaddr=PCIE0_MDIO;	
	else if(portnum==1)	mdioaddr=PCIE1_MDIO;
	else return 0;
	
	REG32(mdioaddr)= ( (regaddr&0x1f)<<PCIE_MDIO_REG_OFFSET) | ((val&0xffff)<<PCIE_MDIO_DATA_OFFSET)  | (1<<PCIE_MDIO_RDWR_OFFSET) ; 
	//delay 
	
	for(i=0;i<5555;i++)  ;

	mdelay(1);
}

static void PCIE_Device_PERST(int portnum)
{
 
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
#if defined(CONFIG_RTL_8198C)
		printk("Port 1 DevRESET\r\n");
		REG32(0xb800010c)= (REG32(0xb800010c)&(~(7<<10)))|(3<<10);
	 	mdelay(500);
		
	 	REG32(PEFGHCNR_REG) &= ~(0x20000);		 /*port F bit 4 */
	 	REG32(PEFGHDIR_REG) |= (0x20000);		 /*port F bit 4 */
		
	    REG32(PEFGHDAT_REG) &= ~(20000);
	 	mdelay(500);
	 	mdelay(500);
		 REG32(PEFGHDAT_REG) |=  (0x20000);   //PERST=1
#endif		 
	}
	else
		return;
}

 void PCIE_PHY_Reset(unsigned int portnum)
{
         #define PCIE_PHY0      0xb8b01008
         #define PCIE_PHY1      0xb8b21008
 
        unsigned int pcie_phy;
 
        if(portnum==0)  pcie_phy=BSP_PCIE0_H_PWRCR;
        else if(portnum==1)     pcie_phy=BSP_PCIE1_H_PWRCR;
        else return;
 
        //PCIE PHY Reset
	REG32(pcie_phy) = 0x01; //bit7:PHY reset=0   bit0: Enable LTSSM=1
	REG32(pcie_phy) = 0x81;   //bit7: PHY reset=1   bit0: Enable LTSSM=1
}

 int PCIE_Check_Link(unsigned int portnum)
{
        unsigned int dbgaddr;
        unsigned int cfgaddr=0;
        int i=10;
 
        if(portnum==0)  dbgaddr=0xb8b00728;
        else if(portnum==1)     dbgaddr=0xb8b20728;
        else return 1;
 	
  //wait for LinkUP

        while(--i)
        {
              if( (REG32(dbgaddr)&0x1f)==0x11)
                        break;

                mdelay(100); 
        }

        if(i==0)        {     
                printk("i=%x  Cannot LinkUP \n",i);
                return 0;
        }
        else
        {
                if(portnum==0) cfgaddr=0xb8b10000;
                else if(portnum==1) cfgaddr=0xb8b30000; 
              
                printk("Find Port=%x Device:Vender ID=%x\n", portnum, REG32(cfgaddr) );
        }
        return 1;
}

int  PCIE_reset_procedure(int portnum, int Use_External_PCIE_CLK, int mdio_reset)
{
	int result=0;	
	printk("PCIE reset port = %d \n", portnum);
	
	#ifdef CONFIG_RTL_8198C
	REG32(0xb8000010)= REG32(0xb8000010) |(1<<12|1<<13|1<<14|1<<16|1<<19|1<<20);//(1<<14);
	#endif
	
	if(portnum==0)		    REG32(CLK_MANAGE) |=  (1<<14);        //enable active_pcie0
	else if(portnum==1)	    REG32(CLK_MANAGE) |=  (1<<16);        //enable active_pcie1	
	else return 0;

	mdelay(500);

	if(mdio_reset)
	{		
		printk("Do MDIO_RESET\n");
		// 3.MDIO Reset
		PCIE_MDIO_Reset(portnum);
	}  

	mdelay(500);
	mdelay(500);

	if(mdio_reset)
	{
		//fix 8198 test chip pcie tx problem.			
		//#if defined(CONFIG_RTL_8198C)		
		REG32(0xb8000104)=(REG32(0xb8000104)&(~0x3<<20))|(1<<20);  //PCIe MUX switch to PCIe reset

        {
                int phy40M;
                phy40M=(REG32(0xb8000008)&(1<<24))>>24;
                //printk("UPHY: 8198c ASIC u2 of u3 %s phy patch\n", (phy40M==1) ? "40M" : "25M");
            if(phy40M)
            {
                 mdelay(500);
                        HostPCIe_SetPhyMdioWrite(portnum, 0x3, 0x7b31);
                    HostPCIe_SetPhyMdioWrite(portnum, 0x6, 0xe258);// e2b8
                    HostPCIe_SetPhyMdioWrite(portnum, 0xF, 0x400F);
                    HostPCIe_SetPhyMdioWrite(portnum, 0xd, 0x1764);// e2b8
                    HostPCIe_SetPhyMdioWrite(portnum, 0x19, 0xFC70);
    
                   // printk("\r\n40MHz PCIe Parameters\r\n");
    
            }
            else
            {
                 HostPCIe_SetPhyMdioWrite(portnum, 0x3, 0x3031);
                 HostPCIe_SetPhyMdioWrite(portnum, 0x6, 0xe058); //Hannah
                     HostPCIe_SetPhyMdioWrite(portnum, 0xF, 0x400F);
                     HostPCIe_SetPhyMdioWrite(portnum, 0x19, 0xFC70);
                            // printk("\r\n25MHz PCIe Parameters\r\n");
    
                
            }
        }
		//#endif    
	}
	//---------------------------------------

	PCIE_Device_PERST(portnum);

	PCIE_PHY_Reset(portnum);	  
        mdelay(500);
        mdelay(500);
	result=PCIE_Check_Link(portnum);

	return result;
	
}
//EXPORT_SYMBOL(PCIE_reset_procedure);