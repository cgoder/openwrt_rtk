/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2007 by Ralf Baechle
 *
 * Modified for RLX Linux for RLX
 * Copyright (C) 2008-2012 Tony Wu (tonywu@realtek.com)
 */
#include <linux/clocksource.h>
#include <linux/init.h>

#include <asm/time.h>

static cycle_t c0_hpt_read(struct clocksource *cs)
{
	return read_c0_count();
}

static struct clocksource clocksource_rlx = {
	.name		= "RLX",
	.read		= c0_hpt_read,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

int __init rlx_clocksource_init(void)
{
	/* Calculate a somewhat reasonable rating value */
	clocksource_rlx.rating = 200 + rlx_hpt_frequency / 10000000;

	clocksource_register_hz(&clocksource_rlx, rlx_hpt_frequency);

	return 0;
}
