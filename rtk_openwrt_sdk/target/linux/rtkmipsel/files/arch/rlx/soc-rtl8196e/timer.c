/*
 * Realtek Semiconductor Corp.
 *
 * bsp/timer.c:
 *     bsp timer initialization
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
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

#include "bspchip.h"

#ifdef CONFIG_CEVT_EXT
void inline bsp_timer_ack(void)
{
	REG32(BSP_TCIR) |= BSP_TC0IP;
}

void __init bsp_timer_init(void)
{
	/* Clear Timer IP status */
	REG32(BSP_TCIR) = (BSP_TC0IP | BSP_TC1IP);
            
	/* disable timer */
	REG32(BSP_TCCNR) = 0; /* disable timer before setting CDBR */

	/* initialize timer registers */
	REG32(BSP_CDBR)=(BSP_DIVISOR) << BSP_DIVF_OFFSET;
	REG32(BSP_TC0DATA) = (((BSP_SYS_CLK_RATE/BSP_DIVISOR)/HZ)) << BSP_TCD_OFFSET;

#ifdef CONFIG_RTL_WTDOG
	//disable watchdog and clear counter and indicator
	//OVSEL[3:2], OVSEL[1:0] = 1001: 2**24
	REG32(BSP_WDTCNR) = (0xA5<<24) | (1 << 23) | (1 << 20) | (0x02 << 17) | (0x01 << 21);
#endif

	/* hook up timer interrupt handler */
	ext_clockevent_init(BSP_TC0_IRQ);
    
	/* enable timer */
	REG32(BSP_TCCNR) = BSP_TC0EN | BSP_TC0MODE_TIMER;
	REG32(BSP_TCIR) = BSP_TC0IE;

#ifdef CONFIG_RTL_WTDOG
	REG32(BSP_WDTCNR) &= (0x00ffffff);
#endif
}
#endif

#ifdef CONFIG_CEVT_RLX
unsigned int __cpuinit get_c0_compare_int(void)
{
	return BSP_COMPARE_IRQ;
}

void __init bsp_timer_init(void)
{
	rlx_hpt_frequency = BSP_CPU0_FREQ;

	write_c0_count(0);
	clear_c0_cause(CAUSEF_DC);
	rlx_clockevent_init(BSP_COMPARE_IRQ);
	rlx_clocksource_init();
}
#endif
