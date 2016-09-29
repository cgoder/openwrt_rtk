/*
 * MIPS idle loop and WAIT instruction support.
 *
 * Copyright (C) xxxx  the Anonymous
 * Copyright (C) 1994 - 2006 Ralf Baechle
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 * Copyright (C) 2001, 2004, 2011, 2012	 MIPS Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include <linux/export.h>
#include <linux/init.h>
#include <linux/irqflags.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <asm/cpu.h>
#include <asm/cpu-info.h>
#include <asm/idle.h>
#include <asm/rlxregs.h>

void arch_cpu_idle(void)
{
	cpu_wait();
}
