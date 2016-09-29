/*
 * Copyright 2008-2011, Realtek Semiconductor Corp.
 *
 * cevt-rlx.h:
 *
 * Tony Wu (tonywu@realtek.com)
 */

#ifndef __ASM_CEVT_RLX_H
#define __ASM_CEVT_RLX_H

DECLARE_PER_CPU(struct clock_event_device, rlx_clockevent_device);

void rlx_event_handler(struct clock_event_device *dev);
int c0_compare_int_usable(void);
void rlx_set_clock_mode(enum clock_event_mode, struct clock_event_device *);
irqreturn_t c0_compare_interrupt(int, void *);

extern struct irqaction c0_compare_irqaction;

#endif /* __ASM_CEVT_RLX_H */
