/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 by Waldorf GMBH, written by Ralf Baechle
 * Copyright (C) 1995, 96, 97, 98, 99, 2000, 01, 02, 03 by Ralf Baechle
 *
 * Modified for RLX processors
 * Copyright (C) 2008-2011 Tony Wu (tonywu@realtek.com)
 */
#ifndef _ASM_IRQ_H
#define _ASM_IRQ_H

#include <linux/linkage.h>
#include <linux/smp.h>
#include <linux/irqdomain.h>

#include <irq.h>

#define irq_canonicalize(irq) (irq)	/* Sane hardware, sane code ... */

extern void do_IRQ(unsigned int irq);

extern void bsp_irq_init(void);
extern void spurious_interrupt(void);

extern int allocate_irqno(void);
extern void alloc_legacy_irqno(void);
extern void free_irqno(unsigned int irq);

#endif /* _ASM_IRQ_H */
