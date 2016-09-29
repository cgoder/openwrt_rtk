/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 * Copyright (c) 2003, 2004  Maciej W. Rozycki
 *
 * Common time service routines for MIPS machines.
 *
 * This program is free software; you can redistribute	it and/or modify it
 * under  the terms of	the GNU General	 Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */
#include <linux/bug.h>
#include <linux/clockchips.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/param.h>
#include <linux/time.h>
#include <linux/timex.h>
#include <linux/smp.h>
#include <linux/spinlock.h>
#include <linux/export.h>

#include <asm/cpu-features.h>
#include <asm/div64.h>
#include <asm/time.h>

/*
 * forward reference
 */
DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);

int __weak rtc_rlx_set_time(unsigned long sec)
{
	return 0;
}

int __weak rtc_rlx_set_mmss(unsigned long nowtime)
{
	return rtc_rlx_set_time(nowtime);
}

int update_persistent_clock(struct timespec now)
{
	return rtc_rlx_set_mmss(now.tv_sec);
}

/*
 * time_init() - it does the following things.
 *
 * 1) bsp_time_init() -
 *	a) (optional) set up RTC routines,
 *	b) (optional) calibrate and set the rlx_hpt_frequency
 *	    (only needed if you intended to use cpu counter as timer interrupt
 *	     source)
 * 2) calculate a couple of cached variables for later usage
 */

unsigned int rlx_hpt_frequency;

void __init time_init(void)
{
	extern void bsp_timer_init(void);
	bsp_timer_init();
}
