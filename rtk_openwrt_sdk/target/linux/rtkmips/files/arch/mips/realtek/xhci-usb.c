/*
 * Realtek Semiconductor Corp.
 *
 * bsp/usb.c:
 *     bsp USB initialization code
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

#include "usb.h"

//USB 3.0 phy init  
#define USB2_PHY_DELAY { mdelay(10); }
//#define USB3_PHY_DELAY  { while( !(REG32(0xb8140000)&0x10)) {}; }
#define USB3_PHY_DELAY { mdelay(5); }

//#define REG32(reg)   (*(volatile unsigned int *)((unsigned int)reg))

static u32 read_reg(unsigned char *addr)
////static unsigned int  read_reg(unsigned char *addr)
{
#if 0  //little
	volatile u32 tmp;
	u32 addv=(u32)addr;
	tmp=REG32(addv);
	printk("=>R:r=%x, v=%x\n",addr,cpu_to_le32(tmp));
	return cpu_to_le32(tmp);
#else
	volatile u32 tmp;
	u32 addv=(u32)addr;
	tmp=REG32(addv);
	//printk("=>R:r=%x, v=%x\n",addr,tmp);
	return tmp;
#endif
}
//----------------------------------------------------------------------------
static void write_reg(unsigned char *addr,u32 value)
{
#if 0  //little
	u32 addv=(u32)addr;
	REG32(addv)=cpu_to_le32(value);
	printk("=>W:r=%x, v=%x\n",addr,value);
#else
	u32 addv=(u32)addr;
	REG32(addv)=value;
	//printk("=>W:r=%x, v=%x\n",addr,value);
#endif
}
//================================================================


void set_u2_phy(unsigned char reg, unsigned char val)
{	
	//#define	USB2_PHY_DELAY	{mdelay(5);}
	//8196C demo board: 0xE0:99, 0xE1:A8, 0xE2:98, 0xE3:C1,  0xE5:91, 	
	#define SYS_USB_PHY 0xb8000090 	
 	int oneportsel=1;
	unsigned int tmp;
/*
	if((reg < 0xE0) || (reg > 0xF6) || ((reg>0xE7)&&(reg<0xF0))) {
		printk("XHCI: Wrong register address: 0x%02x\n", reg);
		return;
	}
*/
	tmp = REG32(SYS_USB_PHY);  //8672 only	
	//tmp = tmp & ~((0xff<<11)|(0xff<<0));
	tmp = tmp & ~(0xff<<11);

	
	if(oneportsel==0)
	{	REG32(SYS_USB_PHY) = (val << 0) | tmp;   //phy 0
	}
	else
	{	REG32(SYS_USB_PHY) = (val << 11) | tmp;  //phy1
	}

	USB2_PHY_DELAY;
	
	unsigned char reg_h=(reg &0xf0)>>4;
	unsigned char reg_l=(reg &0x0f);
#if 0	//little endian	
	REG32(0xb804C280) = (reg_l  << 16) | 0x00004002; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_l  << 16) | 0x00004000; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_l  << 16) | 0x00004002; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_h << 16) | 0x00004002; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_h << 16) | 0x00004000; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_h << 16) | 0x00004002; USB2_PHY_DELAY;
#else
	REG32(0xb804C280) = ((reg_l  << 8) | 0x02000000); USB2_PHY_DELAY;
	REG32(0xb804C280) = ((reg_h << 8) | 0x02000000); USB2_PHY_DELAY;
#endif
	return;	
	
}
//---------------------------------------------------------------------------
unsigned char get_u2_phy(unsigned char reg)
{
	//#define	USB2_PHY_DELAY	{mdelay(5);}
	unsigned char val = 0;	
	unsigned char reg_h=((reg &0xf0)>>4)-2;
	unsigned char reg_l=(reg &0x0f);
/*	
	if((reg < 0xE0) || (reg > 0xF6) || ((reg>0xE7)&&(reg<0xF0))) {
		printk("XHCI: Wrong register address: 0x%02x\n", reg);
		return 0;
	}
*/	

#if 0	//little endian	
	REG32(0xb804C280) = (reg_l  << 16)  | 0x00004002; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_l  << 16)  | 0x00004000; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_l  << 16)  | 0x00004002; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_h << 16)  | 0x00004002; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_h << 16)  | 0x00004000; USB2_PHY_DELAY;
	REG32(0xb804C280) = (reg_h << 16)  | 0x00004002; USB2_PHY_DELAY;

	val = (REG32(0xb804C280) & 0xFF000000) >> 24;
	//printk("XHCI: phy(0x%02x) = 0x%02x\n", reg + 0x20, val);
#else
	REG32(0xb804C280) = ((reg_l  << 8)  | 0x02000000); USB2_PHY_DELAY;
	REG32(0xb804C280) = ((reg_h << 8)  | 0x02000000); USB2_PHY_DELAY;

	val = REG32(0xb804C280) & 0xFF ;
	//printk("XHCI: phy(0x%02x) = 0x%02x\n", reg + 0x20, val);

#endif
	return val;	
}
//-------------------------------------------------------
void dump_u2_phy_parameter(void)
{
	int i, data;
       for(i=0xe0;i<=0xe7;i++)
	{
               data=get_u2_phy(i);
		    printk("R:r=%x v=%x\n",i, data);
	}
       for(i=0xf0;i<=0xf6;i++)
	{
               data=get_u2_phy(i);
		    printk("R:r=%x v=%x\n",i, data);
	}
}
//-------------------------------------------------------
void set_u2_phy_parameter(void)
{
	int t;
	int phy40M;
/*
	t=get_u2_phy(0xe3);
	set_u2_phy(0xe3, t|(2<<0));  //[2:0]    0x98->0x9f
*/

	phy40M=(REG32(0xb8000008)&(1<<24))>>24;
	//printk("UPHY: 8198c ASIC u2 of u3 %s phy patch\n", (phy40M==1) ? "40M" : "25M");

	set_u2_phy( 0xe0, 0x44);
	set_u2_phy( 0xe1, 0xe8);
	set_u2_phy( 0xe2, 0x9a);
	set_u2_phy( 0xe3, 0xa1);

	if(phy40M==0) set_u2_phy( 0xe4, 0x33);
	set_u2_phy( 0xe5, 0x95);
	set_u2_phy( 0xe6, 0x98);
	
	if(phy40M==0) set_u2_phy( 0xe7, 0x66);	
	set_u2_phy( 0xf5, 0x49);	

	if(phy40M==0)	set_u2_phy( 0xf7, 0x11);	
}

//=================================================================

void set_u3_phy(unsigned int addr,unsigned int value)
{
	unsigned int readback;
#if 1 //wei del

	//printk("W:reg=%x, v=%x\n", addr, value);

	REG32(0xb8140000)=(addr<<8);
	USB2_PHY_DELAY;
	readback=REG32(0xb8140000);
	USB2_PHY_DELAY;
	REG32(0xb8140000)=(value<<16)|(addr<<8)|1;
	USB2_PHY_DELAY;
	readback=REG32(0xb8140000);
	USB2_PHY_DELAY;
	REG32(0xb8140000)=(addr<<8);
	USB2_PHY_DELAY;
	readback=REG32(0xb8140000);
	USB2_PHY_DELAY;
	
	if(readback!=((value<<16)|(addr<<8)|0x10)) { printk("usb phy set error (addr=%x, value=%x read=%x)\n",addr,value,readback); }
#else
	//printk("W:r=%x, v=%x\n", addr, value);

	REG32(0xb8140000)=(value<<16)|(addr<<8)|(1<<0);
	USB3_PHY_DELAY;
	
	REG32(0xb8140000)=(addr<<8);	
	USB3_PHY_DELAY;
	
	readback=(REG32(0xb8140000)>>16)&0xffff;
	if(readback != value) printk(" =>Error, reg=%x, wdata=%x, rdata=%x\n", addr, value, readback);
#endif	

}

//-----------------------------------------------------------------------
static void get_u3_phy(unsigned int addr,unsigned int *value)
{
	unsigned int readback;
#if 1	//wei del
	unsigned int readback2;
	unsigned int readback3;    

	REG32(0xb8140000)=(addr<<8);
	USB2_PHY_DELAY;
	readback=REG32(0xb8140000);
	USB2_PHY_DELAY;
	////REG32(0xb8140000)=(value<<16)|(addr<<8)|1;////leory test
	////REG32(0xb8140000)=(value<<16)|(addr<<8);
	////USB2_PHY_DELAY;

	////readback=REG32(0xb8140000);
	USB2_PHY_DELAY;
	REG32(0xb8140000)=(addr<<8);
	USB2_PHY_DELAY;
	readback2=REG32(0xb8140000);
	USB2_PHY_DELAY;

    ////printk("addr:0x%x  ==>readback:0x%x val:0x%x addr:0x%x valid:0x%x\n",addr
     ////   ,readback,(readback>>16) ,((readback>>8)&0xFF),(readback&0xFF));
    //// printk("addr:0x%x  ==>readback2:0x%x val:0x%x addr:0x%x valid:0x%x\n",addr
    ////    ,readback2,(readback2>>16) ,((readback2>>8)&0xFF),(readback2&0xFF));   

    *value=((readback2>>16)&0xFFFF);

	////if(readback!=((value<<16)|(addr<<8)|0x10)) { printk("usb phy set error (addr=%x, value=%x read=%x)\n",addr,value,readback); }
#else

	REG32(0xb8140000)=(addr<<8)| (0<<0);  //read
	mdelay(100);
	readback=REG32(0xb8140000);
    *value=((readback>>16)&0xFFFF);
#endif	

}
//-------------------------------------------------------
void dump_u3_phy_parameter(void)
{
	int i, data;
       for(i=0;i<0x30;i++)
	{
               get_u3_phy(i,&data);
		    printk("R:r=%x v=%x\n",i, data);
	}

}
//-------------------------------------------------------
void U3_MDIOReset(int Reset_n)  //wei add
{
	#define U3_IPCFG 0xb8140008

	REG32(U3_IPCFG) |=   (1<<18);  //control by sys reg.

	if(Reset_n==0)     REG32(U3_IPCFG) &=~(1<<19);
	else		   		    REG32(U3_IPCFG) |=   (1<<19);
	mdelay(100);
		
}

//-------------------------------------------------------
void U3_PhyReset(int Reset_n)  //wei add
{
	#define U3_IPCFG 0xb8140008
	//U3_PhyReset
	REG32(U3_IPCFG) |=   (1<<9);  //control by sys reg.

	if(Reset_n==0)     REG32(U3_IPCFG) &=~(1<<10);
	else				    REG32(U3_IPCFG) |=   (1<<10);	
  
	mdelay(100);
	
}
//-------------------------------------------------------
void U2_PhyReset(int Reset_n)  //wei add
{
	#define U3_IPCFG 0xb8140008
	//U3_PhyReset
	REG32(U3_IPCFG) |=   (1<<7);  //control by sys reg.

	if(Reset_n==0)     REG32(U3_IPCFG) &=~(1<<8);
	else				    REG32(U3_IPCFG) |=   (1<<8);	
  
	mdelay(100);
	
}
//-------------------------------------------------------
void U3_MacBusReset(int Reset_n)
{
	#define U3_IPCFG 0xb8140008
   //u3 total reset
    REG32(U3_IPCFG) |=   (1<<20);  //control by sys reg.
	if(Reset_n==0)		REG32(U3_IPCFG) &=~(1<<21);
	else				    REG32(U3_IPCFG) |=   (1<<21);	
    mdelay(100);

}


//=========================================================
void U3_AutoCalc_TRxPhase(void)
{
	int old_uphy;
	get_u3_phy(0x1c, &old_uphy);
       set_u3_phy(0x1c, old_uphy|(1<<10) );   //bit 10:SLB


	int old_ext_reg;
	old_ext_reg=REG32(0xb8140008);

	REG32(0xb8140008) = old_ext_reg | (0<<16) |(1<<15);   //[17:16]=pattern sel, b15=enable


	int tx,rx, t;
	int okcnt1, okcnt2;
	int failcnt1, failcnt2;	
	int shit=0, stx, srx;
	for(tx=0; tx<4; tx++)
	{
		printk("(TX,RX):  ");
		for(rx=0; rx<4; rx++)
		{
			t=REG32(0xb8140008) & ~((3<<22)|(3<<25));			
			REG32(0xb8140008) = t | (tx<<22) | (rx<<25);
			okcnt1=0;  okcnt2=0;
			failcnt1=0; failcnt2=0;
			
			mdelay(0x30);		
			failcnt1=REG32(0xb8140010);
			okcnt1=REG32(0xb8140014);
			
			mdelay(0x30);
			failcnt2=REG32(0xb8140010);
			okcnt2=REG32(0xb8140014);			

			if( (failcnt1==failcnt2) && (okcnt1!=okcnt2) ) 
			{	printk("(%d,%d)=O  ", tx,rx ); 
				if(shit==0) { stx=tx, srx=rx; shit=1; }   //only first point to save
			}
			else    printk("(%d,%d)=X  ", tx,rx );
		}
		printk("\n");
	}

	//restore
	REG32(0xb8140008) =old_ext_reg | (stx<<22) | (srx<<25) ;
	set_u3_phy(0x1c, old_uphy);

	
}

//===========================================================
////#define REG32(reg)   (*(volatile unsigned int *)((unsigned int)reg)) //tysu test
//#define NEW_PHY_PARAM 1
//#define TINA_20110901 1
void set_u3_phy_parameter(void) //just for rle0371
{
	int phy40M;

	#define CLK_MGR 0xb8000010	
    REG32(CLK_MGR)|=(1<<21) | (1<<19) | (1<<20);  //enable usb 3 ip
    
	#define U3_IPCFG 0xb8140008
	REG32(U3_IPCFG)&=~(1<<6);   //u3 reg big endia
	
    U3_MacBusReset(0);
    U3_MacBusReset(1);	

#if 1
	//setting u2 of u3 phy
	REG32(0xb8000090) &= ~(1<<20);
	REG32(0xb8000090) |= (1<<19)|(1<<21);        //0x00280500;
#endif

//RLE0705D > 0403 > 0363	(old)
    //printk("=>USB PHY Patch\n"); 
//------------------------------------------------------------
	
#if 0    ////leroy, 8198B realchip
////new parameter from RDC +
    set_u3_phy(0x00, 0x1278);
    set_u3_phy(0x01, 0x0003);
    set_u3_phy(0x02, 0x2D18); //RX CCO= LC-VCO
    set_u3_phy(0x03, 0x6D70);
    set_u3_phy(0x04, 0x7000);
    set_u3_phy(0x05, 0x0304);
    set_u3_phy(0x06, 0xB054);
    set_u3_phy(0x07, 0x4CC1);
    set_u3_phy(0x08, 0x31D2);
    set_u3_phy(0x09, 0x923C);
    //enable debug port, LFPS: DPHY period is most like U55
    set_u3_phy(0x0a, 0x9240);
    set_u3_phy(0x0b, 0xC51D);
    set_u3_phy(0x0c, 0x68AB);
    set_u3_phy(0x0d, 0x27A6);
    set_u3_phy(0x0e, 0x9B01);
    set_u3_phy(0x0f, 0x051A);
    set_u3_phy(0x10, 0x000C);

    set_u3_phy(0x11, 0x4C00);
    set_u3_phy(0x12, 0xFC00);
    set_u3_phy(0x13, 0x0C81);
    set_u3_phy(0x14, 0xDE01);
    set_u3_phy(0x15, 0x0000);
    set_u3_phy(0x16, 0x0000);
    set_u3_phy(0x17, 0x0000);
    set_u3_phy(0x18, 0x0000);
    set_u3_phy(0x19, 0xA000);
    set_u3_phy(0x1a, 0x6DE1);
    set_u3_phy(0x1b, 0xA027);
    set_u3_phy(0x1c, 0xC300);
    //set_u3_phy(0x1c, 0xC81C); //RX negtive edge & slew rate slow $ 4mA
    set_u3_phy(0x1d, 0xA03E);
    set_u3_phy(0x1e, 0xC2A0);
    
    set_u3_phy(0x1f, 0x0000);
    
    set_u3_phy(0x20, 0xE39F);
    
    set_u3_phy(0x21, 0xD51B);
    set_u3_phy(0x22, 0x0836);
    set_u3_phy(0x23, 0x4FA2);
    set_u3_phy(0x24, 0x13F1);
    set_u3_phy(0x25, 0x03DD);
    set_u3_phy(0x26, 0x64CA);
    set_u3_phy(0x27, 0x00F9);
    set_u3_phy(0x28, 0x48B0);
    set_u3_phy(0x29, 0x0000);////???
    set_u3_phy(0x2a, 0x3080);
    set_u3_phy(0x2b, 0x2018);
    set_u3_phy(0x2c, 0x0000);////???
    set_u3_phy(0x2d, 0x0000);////???
    set_u3_phy(0x2e, 0x0000);////???
    set_u3_phy(0x2f, 0x0000);////???
    set_u3_phy(0x04, 0x7000);
 

    set_u3_phy(0x1c, 0x0000);////???
    set_u3_phy(0x0a, 0x0000);////???
    set_u3_phy(0x1c, 0x0000);////???
    set_u3_phy(0x0a, 0x0000);////???
    set_u3_phy(0x0a, 0x9A40);
    set_u3_phy(0x0a, 0x9A44);
    set_u3_phy(0x0a, 0x9240);
    set_u3_phy(0x09, 0x923C);
    set_u3_phy(0x09, 0x903C);
    set_u3_phy(0x09, 0x923C);
////new parameter from RDC -
#endif


//------------------------------------------------------------


#if 0    //tony, FPGA, RLE0363
	printk("UPHY: RLE0363\n");
#ifdef NEW_PHY_PARAM
        set_u3_phy(0x00, 0x1218);
#else
        set_u3_phy(0x00, 0x1278);
#endif
        set_u3_phy(0x01, 0x0003);
        set_u3_phy(0x02, 0x2D18);
        set_u3_phy(0x03, 0x6D66); //org
//      set_u3_phy(0x03, 0x6D64); //test
        set_u3_phy(0x04, 0x5000);
        set_u3_phy(0x05, 0x0304);
        set_u3_phy(0x06, 0x6054);
        set_u3_phy(0x07, 0x4CC1);
        set_u3_phy(0x08, 0x31D2); //org
//      set_u3_phy(0x08, 0x31D6); //debug test
        set_u3_phy(0x09, 0x921C);
        set_u3_phy(0x0a, 0x5280);
        set_u3_phy(0x0b, 0xC51D);
        set_u3_phy(0x0c, 0xA8AB);
        set_u3_phy(0x0d, 0x27A6);
        set_u3_phy(0x0e, 0x94C5);
        set_u3_phy(0x0f, 0x051A);
        set_u3_phy(0x10, 0x000C);
        set_u3_phy(0x11, 0x4C00);
        set_u3_phy(0x12, 0xFC00);
        set_u3_phy(0x13, 0x0C81);
        set_u3_phy(0x14, 0xDE01);
        set_u3_phy(0x15, 0x0000);
        set_u3_phy(0x16, 0x0000);
        set_u3_phy(0x17, 0x0000);
        set_u3_phy(0x18, 0x0000);
        set_u3_phy(0x19, 0xa000);
        set_u3_phy(0x1a, 0x6DE1);
        set_u3_phy(0x1b, 0x3F00);
        set_u3_phy(0x1c, 0xC3C0);
        set_u3_phy(0x1d, 0xA03E);
        set_u3_phy(0x1e, 0xC2A0);
        set_u3_phy(0x1f, 0x0000);
        set_u3_phy(0x20, 0xE39F);
        set_u3_phy(0x21, 0xD51B);
        set_u3_phy(0x22, 0x0836);
        set_u3_phy(0x23, 0x4FA2);
        set_u3_phy(0x24, 0x13F1);
        set_u3_phy(0x25, 0x03DD);
        set_u3_phy(0x26, 0x65BA);
        set_u3_phy(0x27, 0x00F9);
        set_u3_phy(0x28, 0x48B0);
//      set_u3_phy(0x29, 0x0);
        set_u3_phy(0x2a, 0x3000);
        set_u3_phy(0x2b, 0x0000);
//      set_u3_phy(0x2c, 0x0000);
//      set_u3_phy(0x2d, 0x0000);
//      set_u3_phy(0x2e, 0x0000);
        set_u3_phy(0x2f, 0x0000);
        set_u3_phy(0x04, 0x7000);
 
#ifdef NEW_PHY_PARAM
        set_u3_phy(0x1c, 0xc301);
        set_u3_phy(0x0a, 0x1ae0);
        set_u3_phy(0x1c, 0xc300);
        set_u3_phy(0x0a, 0x1a80);
#endif
        set_u3_phy(0x0a, 0x5A80);
        set_u3_phy(0x0a, 0x5A84);
        set_u3_phy(0x0a, 0x5280);
        set_u3_phy(0x0a, 0x5280);
        set_u3_phy(0x0a, 0x5280);
        set_u3_phy(0x09, 0x921C);
        set_u3_phy(0x09, 0x901C);
        set_u3_phy(0x09, 0x921C);
 
#endif //end of if 1
 
//------------------------------------------------------------

#if 0   //#ifdef TINA_20110901

    printk("%s:%d TINA_20110901\n", __FUNCTION__,__LINE__); ////leroy +

    set_u3_phy(0x00, 0x4EF8);
    set_u3_phy(0x01, 0xE0CE);
    //set_u3_phy(0x02, 0xE148);
    set_u3_phy(0x02, 0xE140); //RX CCO= LC-VCO
    set_u3_phy(0x03, 0x2770);
    set_u3_phy(0x04, 0x7000);
    set_u3_phy(0x05, 0x6852);
    set_u3_phy(0x06, 0x3130);
    set_u3_phy(0x07, 0x2E20);
    set_u3_phy(0x08, 0xC351);
    //set_u3_phy(0x09, 0x521C);
    set_u3_phy(0x09, 0x523D);
    //enable debug port, LFPS: DPHY period is most like U55
    set_u3_phy(0x0a, 0x9640);
    set_u3_phy(0x0b, 0x8B14);
    set_u3_phy(0x0c, 0xCBEA);
    set_u3_phy(0x0d, 0x154A);
    set_u3_phy(0x0e, 0x9B61);
    set_u3_phy(0x0f, 0x8000);
    set_u3_phy(0x10, 0x03D4);
    //set_u3_phy(0x10, 0x03A4);
    set_u3_phy(0x11, 0x4C00);
    set_u3_phy(0x12, 0xFC00);
    set_u3_phy(0x13, 0x0C81);
    set_u3_phy(0x14, 0xDE01);
    set_u3_phy(0x15, 0x0000);
    set_u3_phy(0x16, 0x0000);
    set_u3_phy(0x17, 0x0000);
    set_u3_phy(0x18, 0x0000);
    set_u3_phy(0x19, 0xE103);
    set_u3_phy(0x1a, 0x1263);
    set_u3_phy(0x1b, 0xC6A9);
    set_u3_phy(0x1c, 0xCB9C);
    //set_u3_phy(0x1c, 0xC81C); //RX negtive edge & slew rate slow $ 4mA
    set_u3_phy(0x1d, 0xA03F);
    set_u3_phy(0x1e, 0xC2E0);
    set_u3_phy(0x1f, 0xD800);
    set_u3_phy(0x20, 0xE3F0);
    set_u3_phy(0x21, 0x028F);
    set_u3_phy(0x22, 0x0836);
    set_u3_phy(0x23, 0x0640);
    set_u3_phy(0x24, 0x91FD);
    set_u3_phy(0x25, 0x11E9);
    set_u3_phy(0x26, 0xC86D);
    set_u3_phy(0x27, 0x8011);
    set_u3_phy(0x28, 0x2800);
    set_u3_phy(0x29, 0x3080);
    set_u3_phy(0x2a, 0x3080);
    set_u3_phy(0x2b, 0x2038);
    set_u3_phy(0x2c, 0x9734);
    set_u3_phy(0x2d, 0x7490);
    set_u3_phy(0x2e, 0x94B4);
    set_u3_phy(0x2f, 0x25F2);
#endif //end of tina
//------------------------------------------------------------

	


#if 0 //wei add, using SD1 GingZu support parameter. RLE0403
	printk("UPHY: RLE0403\n");
    set_u3_phy(0x00, 0x46F8);
    set_u3_phy(0x00, 0x4EF8);
	
    set_u3_phy(0x01, 0xE0CE);
    set_u3_phy(0x02, 0xE148);

    set_u3_phy(0x03, 0x2770);
//    set_u3_phy(0x04, 0x7000);
    set_u3_phy(0x04, 0x5000);	 //####2
	
    set_u3_phy(0x05, 0x60c2);	
    set_u3_phy(0x05, 0x6092);
	
    set_u3_phy(0x06, 0x3330);
    set_u3_phy(0x07, 0x2E20);
    set_u3_phy(0x08, 0x7a11);
    
    set_u3_phy(0x09, 0x523c);
	
//    set_u3_phy(0x0a, 0x9640);    //###disable dbg
    set_u3_phy(0x0a, 0x9240);
	
    set_u3_phy(0x0b, 0x8B14);
    set_u3_phy(0x0c, 0xCBEA);
    set_u3_phy(0x0d, 0x154A);
    set_u3_phy(0x0e, 0x9B61);
    set_u3_phy(0x0f, 0x8000);
//    set_u3_phy(0x10, 0x034D);  //####disable dbg
    set_u3_phy(0x10, 0x000C);	

    set_u3_phy(0x11, 0x4C00);
    set_u3_phy(0x12, 0xFC00);
    set_u3_phy(0x13, 0x0C81);
    set_u3_phy(0x14, 0xDE01);
    set_u3_phy(0x15, 0x0000);
    set_u3_phy(0x16, 0x0000);
    set_u3_phy(0x17, 0x0000);
    set_u3_phy(0x18, 0x0000);
	
    set_u3_phy(0x19, 0xE102);
    set_u3_phy(0x19, 0xE103);
	
    set_u3_phy(0x1a, 0x1263);
    set_u3_phy(0x1b, 0xC6A9);

    set_u3_phy(0x1c, 0xCB1d);	
    set_u3_phy(0x1c, 0xCB1C);
    set_u3_phy(0x1c, 0xCB9C);
	
    set_u3_phy(0x1d, 0xA03F);
	
    set_u3_phy(0x1e, 0xC200);	
    set_u3_phy(0x1e, 0xC2E0);
	
    set_u3_phy(0x1f, 0xD800);  //RO
    set_u3_phy(0x20, 0xE3F0);
    set_u3_phy(0x21, 0x028F);
    set_u3_phy(0x22, 0x0836);
    set_u3_phy(0x23, 0x0640);
    set_u3_phy(0x24, 0x91FD);
    set_u3_phy(0x25, 0x11E9);
    set_u3_phy(0x26, 0xfa6D);
    set_u3_phy(0x27, 0x802b);
    set_u3_phy(0x28, 0x2800);
    set_u3_phy(0x29, 0x3080);
    set_u3_phy(0x2a, 0x3080);
    set_u3_phy(0x2b, 0x2038);
    set_u3_phy(0x2c, 0x9734);
    set_u3_phy(0x2d, 0x7490);
    set_u3_phy(0x2e, 0x94B4);
    set_u3_phy(0x2f, 0x25F2);   //RO

    set_u3_phy(0x09, 0x523c);
    set_u3_phy(0x09, 0x503c);
    set_u3_phy(0x09, 0x523c);	
 #endif

//------------------------------------------------------------


#if 0 //wei add, RLE0705D, osc=40MHz
	printk("UPHY: RLE0705D\n");
    set_u3_phy(0x00, 0x4AF8);
	
    set_u3_phy(0x01, 0xE0CE);
    set_u3_phy(0x02, 0xE048);

    set_u3_phy(0x03, 0x2770);
    set_u3_phy(0x04, 0x7800);
//    set_u3_phy(0x04, 0x5000);	 //####2
	
    set_u3_phy(0x05, 0x60EC);	
	
    set_u3_phy(0x06, 0x8170);
    set_u3_phy(0x07, 0x3220);
    set_u3_phy(0x08, 0x4F63);
    
    set_u3_phy(0x09, 0xD23c);
	
//    set_u3_phy(0x0a, 0x9640);    //###disable dbg
    set_u3_phy(0x0a, 0x9240);
	
    set_u3_phy(0x0b, 0x8B15);
    set_u3_phy(0x0c, 0x4DEA);
    set_u3_phy(0x0d, 0x174A);
    set_u3_phy(0x0e, 0x9551);
    set_u3_phy(0x0f, 0x8000);
//    set_u3_phy(0x10, 0x034D);  //####disable dbg
    set_u3_phy(0x10, 0x000C);	

    set_u3_phy(0x11, 0x4C00);
    set_u3_phy(0x12, 0xFC00);
    set_u3_phy(0x13, 0x0C81);
    set_u3_phy(0x14, 0xDE01);
    set_u3_phy(0x15, 0x0000);
    set_u3_phy(0x16, 0x0000);
    set_u3_phy(0x17, 0x0000);
    set_u3_phy(0x18, 0x0000);
	
    set_u3_phy(0x19, 0xE102);
	
    set_u3_phy(0x1a, 0x1263);
    set_u3_phy(0x1b, 0xC6A9);

    set_u3_phy(0x1c, 0xCB80);	

    set_u3_phy(0x1d, 0xA03F);
	
    set_u3_phy(0x1e, 0xC200);	

	
    set_u3_phy(0x1f, 0x9000);  //RO
    set_u3_phy(0x20, 0xF7F0);
    set_u3_phy(0x21, 0x028F);
    set_u3_phy(0x22, 0x0836);
    set_u3_phy(0x23, 0x0460);
    set_u3_phy(0x24, 0x94EB);
    set_u3_phy(0x25, 0x14D7);
    set_u3_phy(0x26, 0xc86D);
    set_u3_phy(0x27, 0x8067);
    set_u3_phy(0x28, 0x2800);
    set_u3_phy(0x29, 0x3080);
    set_u3_phy(0x2a, 0x3080);
    set_u3_phy(0x2b, 0x2038);
    set_u3_phy(0x2c, 0x9E14);
    set_u3_phy(0x2d, 0x1124);
    set_u3_phy(0x2e, 0x97D3);
    set_u3_phy(0x2f, 0x25F2);   //RO

    set_u3_phy(0x09, 0xD23C);
    set_u3_phy(0x09, 0xD03C);
    set_u3_phy(0x09, 0xD23C);	

    set_u3_phy(0x1c, 0xCB80);
    set_u3_phy(0x1c, 0xCB00);
    set_u3_phy(0x1c, 0xCB00);
    set_u3_phy(0x1c, 0xCB80);
    set_u3_phy(0x1c, 0xCB80);	
 #endif
//--------------------------------------------------------------
#if 1  //8198C ASIC 40M
	phy40M=(REG32(0xb8000008)&(1<<24))>>24;
	printk("UPHY: 8198c ASIC u3 of u3 %s phy patch\n", (phy40M==1) ? "40M" : "25M");


	set_u3_phy(0x00, 0x4A78);
	set_u3_phy(0x01, 0xC0CE);
	set_u3_phy(0x02, 0xE048);
	set_u3_phy(0x03, 0x2770);
	set_u3_phy(0x04, (phy40M==1) ? 0x5800 : 0x5000);
	set_u3_phy(0x05, (phy40M==1) ? 0x60EA : 0x6182);
	set_u3_phy(0x06, (phy40M==1) ?0x4168 : 0x6178 );  //0108
	set_u3_phy(0x07, 0x2E40);
	set_u3_phy(0x08, (phy40M==1) ? 0x4F61 : 0x31B1);
	set_u3_phy(0x09, 0x923C);
	set_u3_phy(0x0A, 0x9240);
	set_u3_phy(0x0B, (phy40M==1) ? 0x8B15 : 0x8B1D);  //0108
	set_u3_phy(0x0C, 0xDC6A);
	set_u3_phy(0x0D, (phy40M==1) ? 0x148A : 0x158a);  //0108
	set_u3_phy(0x0E, (phy40M==1) ? 0x98E1 : 0xA8c9);  //0108
	set_u3_phy(0x0F, 0x8000);
	
	set_u3_phy(0x10, 0x000C);
	set_u3_phy(0x11, 0x4C00);
	set_u3_phy(0x12, 0xFC00);
	set_u3_phy(0x13, 0x0C81);
	set_u3_phy(0x14, 0xDE01);
	set_u3_phy(0x19, 0xE102);
	set_u3_phy(0x1A, 0x1263);
	set_u3_phy(0x1B, 0xC7FD);
	set_u3_phy(0x1C, 0xCB00);
	set_u3_phy(0x1D, 0xA03F);
	set_u3_phy(0x1E, 0xC2E0);
	
	set_u3_phy(0x20, 0xB7F0);
	set_u3_phy(0x21, 0x0407);
	set_u3_phy(0x22, 0x0016);
	set_u3_phy(0x23, 0x0CA1);
	set_u3_phy(0x24, 0x93F1);
	set_u3_phy(0x25, 0x2BDD);
	set_u3_phy(0x26, (phy40M==1) ? 0xA06D : 0x646F);  //0108
	set_u3_phy(0x27, (phy40M==1) ? 0x8068 : 0x8107);
	set_u3_phy(0x28, (phy40M==1) ? 0xE060 : 0xE020);  //0108
	set_u3_phy(0x29, 0x3080);
	set_u3_phy(0x2A, 0x3082);
	set_u3_phy(0x2B, 0x2038);
	set_u3_phy(0x2C, 0x7E30);
	set_u3_phy(0x2D, 0x15DC);
	set_u3_phy(0x2E, 0x792F);
	
	set_u3_phy(0x04, (phy40M==1) ? 0x7800 : 0x7000);
	set_u3_phy(0x09, 0x923C);
	set_u3_phy(0x09, 0x903C);
	set_u3_phy(0x09, 0x923C);
    
#endif
//--------------------------------------------------------------
//	U3_PhyReset();
//	dump_u3_phy_parameter();
    //printk("=>USB PHY END\n");


    //fpga tune
#if 0    
    //REG32(U3_IPCFG)|=(1<<22); //90
//    REG32(U3_IPCFG)|=(2<<22) | (0<<25); //180, [23:22]= tx, [26:25]=rx
    //REG32(U3_IPCFG)|=(3<<22); //270
#else
//	U3_AutoCalc_TRxPhase();
#endif


//    mdelay(100);
 
}

//-------------------------------------------------------------------------------

void U3PHYTrainning()
{
    	u8 *base=(u32 *)0xb8040000;

	static int test_count_u3=0;

    	while(1)
    	{
    		volatile u32 tmp;
            test_count_u3++;
            if(test_count_u3>100)
                break;

    		//printk("dump 0x430=%x\n",read_reg(base+0x430));		
    		//printk("dump 0x420=%x\n",read_reg(base+0x420));

#if 1
    		if((read_reg(base+0x430)&0x1000)==0x1000) 
            {
    		    printk("%s %d SS device found!\n",__FUNCTION__,__LINE__);
#if 1
		//clear U3 WRC & CSC 
    		tmp=read_reg(base+0x430);
    		tmp|=(1<<17)|(1<<19);  // WRC CSC.
    		tmp&=~(1<<1); // don't disable port
    		write_reg(base+0x430,tmp);
#endif					
    		    printk("%s %d 0x420=%x\n",__FUNCTION__,__LINE__,read_reg(base+0x420));				
    		    printk("%s %d 0x430=%x\n",__FUNCTION__,__LINE__,read_reg(base+0x430));	
				
                break;  // SS device found!
    		}

    		//warm port reset for USB 3.0
    		//printk("Do Warm Reset for U3\n");
    		tmp=read_reg(base+0x430);
    		tmp|=(1<<31)|(1<<0);  // warm port reset and set CCS.
    		tmp&=~(1<<1); // don't disable port
    		write_reg(base+0x430,tmp);
			
    		mdelay(500);			

    		if((read_reg(base+0x430)&0xfff)==0x2a0) 
    		{
#if 1    		
    			//try USB 2.0 Port Reset
    			//printk("try Port Reset for U2\n");
    			write_reg(base+0x420,read_reg(base+0x420)|0x10);
    			mdelay(200);

    			// stop USB 2.0 Port Enable
    			write_reg(base+0x420,read_reg(base+0x420)|0x2);
    			mdelay(200);				
#endif  		
#if 1
		//clear U3 WRC & CSC 
    		tmp=read_reg(base+0x430);
    		tmp|=(1<<17)|(1<<19);  // WRC CSC.
    		tmp&=~(1<<1); // don't disable port
    		write_reg(base+0x430,tmp);
#endif			
    			break;
    		}
		
#endif
           
    	}   
 
}

void rtk_usb3_phyinit(void)
{

	set_u3_phy_parameter();
	set_u2_phy_parameter();
	

	U3_PhyReset(0);
	U3_PhyReset(1);

	U2_PhyReset(0);
	U2_PhyReset(1);	

	U3PHYTrainning();
}

//below are original usb platform impement
/* USB Host Controller */

static struct resource bsp_usb3_resource[] = {
	[0] = {
		.start = BSP_USB_USB3_MAPBASE,
		.end = BSP_USB_USB3_MAPBASE + BSP_USB_USB3_MAPSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = BSP_PS_USB_IRQ_USB3,
		.end = BSP_PS_USB_IRQ_USB3,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 bsp_usb_dmamask = 0xFFFFFFFFUL;

struct platform_device bsp_usb3_device = {
	//.name = "dwc_usb3",
	.name = "xhci-hcd", //mark_u3
	.id = -1,
	.num_resources = ARRAY_SIZE(bsp_usb3_resource),
	.resource = bsp_usb3_resource,
	.dev = {
		.dma_mask = &bsp_usb_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

static struct platform_device *bsp_usb_devs[] __initdata = {
	&bsp_usb3_device,
};

static int __init bsp_usb_init(void)
{
	int ret;

	printk("INFO: initializing USB devices ...\n");
#if 0 //wei add for FPGA sata test	
	return -1;
#endif	
	rtk_usb3_phyinit();
	ret = platform_add_devices(bsp_usb_devs, ARRAY_SIZE(bsp_usb_devs));
	if (ret < 0) {
		printk("ERROR: unable to add devices\n");
		return ret;
	}

	return 0;
}
arch_initcall(bsp_usb_init);
