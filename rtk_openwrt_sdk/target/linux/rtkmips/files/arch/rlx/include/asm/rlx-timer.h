/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008 by Ralf Baechle (ralf@linux-mips.org)
 *
 * Modified for RLX Linux for RLX
 * Copyright (C) 2012  Tony Wu (tonywu@realtek.com)
 */
#ifndef __ASM_RLX_TYPES_H
#define __ASM_RLX_TYPES_H

#include <linux/compiler.h>

#ifdef CONFIG_SYNC_RLX

extern void synchronise_count_master(int cpu);
extern void synchronise_count_slave(int cpu);

#else

static inline void synchronise_count_master(int cpu)
{
}

static inline void synchronise_count_slave(int cpu)
{
}

#endif

#endif /* __ASM_RLX_TYPES_H */
