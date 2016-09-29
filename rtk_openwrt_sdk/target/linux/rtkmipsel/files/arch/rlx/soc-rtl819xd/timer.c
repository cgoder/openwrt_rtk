/*
 *  linux/arch/rlx/rlxocp/time.c
 *
 *  Copyright (C) 1999 Harald Koerfgen
 *  Copyright (C) 2000 Pavel Machek (pavel@suse.cz)
 *  Copyright (C) 2001 Steven J. Hill (sjhill@realitydiluted.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Time handling functinos for Philips Nino.
 */
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/param.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/timex.h>
#include <linux/delay.h>

#include <asm/time.h>
//#include <asm/rlxbsp.h>

#include  "bspchip.h"

#ifdef CONFIG_RTL_TIMER_ADJUSTMENT
#include <net/rtl/rtl_types.h>
#include <rtl865xc_asicregs.h>

void rtl865x_setupTimer1(void)
{
	WRITE_MEM32( TCCNR, READ_MEM32(TCCNR) & ~TC1EN );/* Disable timer1 */
	WRITE_MEM32( TC1DATA, 0xffffff00);	
	WRITE_MEM32( TCCNR, ( READ_MEM32(TCCNR) | TC1EN ) | TC1MODE_TIMER );/* Enable timer1 - timer mode */
	WRITE_MEM32( TCIR, READ_MEM32(TCIR) & ~TC1IE ); /* Disable timer1 interrupt */
}
#endif

void inline bsp_timer_ack(void)
{
    REG32(BSP_TCIR) |= BSP_TC0IP;
}

void __init bsp_timer_init(void)
{
	unsigned int sys_clock_rate;

    sys_clock_rate =  BSP_SYS_CLK_RATE;

   /* Clear Timer IP status */
   if (REG32(BSP_TCIR) & BSP_TC0IP)
      REG32(BSP_TCIR) |= BSP_TC0IP;
            
    /* disable timer */
    REG32(BSP_TCCNR) = 0; /* disable timer before setting CDBR */

    /* initialize timer registers */
	REG32(BSP_CDBR)=(BSP_DIVISOR) << BSP_DIVF_OFFSET;
	#if defined(CONFIG_RTL8198_REVISION_B) || defined(CONFIG_RTL_819XD)
	if ((REG32(BSP_REVR) >= BSP_RTL8198_REVISION_B) || ((REG32(BSP_REVR) & 0xFFFFF000) == BSP_RTL8197D))
		REG32(BSP_TC0DATA) = (((sys_clock_rate/BSP_DIVISOR)/HZ)) << 4;
	else
	#endif                                                                         
		REG32(BSP_TC0DATA) = (((sys_clock_rate/BSP_DIVISOR)/HZ)) << BSP_TCD_OFFSET;
	// extend timer base to 4 times
	//REG32(BSP_CDBR)=(BSP_DIVISOR*4) << BSP_DIVF_OFFSET;
	//REG32(BSP_TC0DATA) = (((sys_clock_rate/(BSP_DIVISOR*4))/HZ)) << BSP_TCD_OFFSET;
#ifdef CONFIG_RTL_TIMER_ADJUSTMENT
   	rtl865x_setupTimer1();
#endif   
#if defined(CONFIG_RTL_WTDOG)
#ifdef CONFIG_RTK_VOIP
	{
		extern void bsp_enable_watchdog( void );
		bsp_enable_watchdog();
	}
#else
	REG32(BSP_WDTCNR) = 0x00600000;
#endif
#endif

    /* hook up timer interrupt handler */
#ifdef CONFIG_CEVT_EXT
	ext_clockevent_init(BSP_TC0_IRQ);
#endif
#ifdef CONFIG_CEVT_RLX
	rlx_clockevent_init(BSP_TC0_IRQ);
#endif
    
    /* enable timer */
	REG32(BSP_TCCNR) = BSP_TC0EN | BSP_TC0MODE_TIMER;
	REG32(BSP_TCIR) = BSP_TC0IE;
}

#ifdef CONFIG_RTK_VOIP
void timer1_enable(void)
{
	printk( "timer1_enable not implement!!\n" );
}

void timer1_disable(void)
{
	printk( "timer1_disable not implement!!\n" );
}

#ifdef CONFIG_RTL_WTDOG
int bBspWatchdog = 0;

void bsp_enable_watchdog( void )
{
	bBspWatchdog = 1;
	*(volatile unsigned long *)(0xb800311C)=0x00600000;
}

void bsp_disable_watchdog( void )
{
	*(volatile unsigned long *)(0xb800311C)=0xA5600000;
	bBspWatchdog = 0;
}
#endif // CONFIG_RTL_WTDOG

#endif  // CONFIG_RTK_VOIP
