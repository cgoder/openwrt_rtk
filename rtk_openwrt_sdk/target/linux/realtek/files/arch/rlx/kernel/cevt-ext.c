/*
 * Copyright 2008, Realtek Semiconductor Corp.
 *
 * Tony Wu (tonywu@realtek.com)
 * Dec. 07, 2008
 */
#include <linux/clockchips.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#include <asm/time.h>

int ext_timer_state(void)
{
	return 0;
}

int ext_timer_set_base_clock(unsigned int hz)
{
	return 0;
}

static int ext_timer_set_next_event(unsigned long delta,
				 struct clock_event_device *evt)
{
	return -EINVAL;
}

static void ext_timer_set_mode(enum clock_event_mode mode,
			    struct clock_event_device *evt)
{
	return;
}

static void ext_timer_event_handler(struct clock_event_device *dev)
{
}

static struct clock_event_device ext_clockevent = {
	.name		= "EXT",
	.features	= CLOCK_EVT_FEAT_PERIODIC,
	.set_next_event	= ext_timer_set_next_event,
	.set_mode	= ext_timer_set_mode,
	.event_handler	= ext_timer_event_handler,
};

static irqreturn_t ext_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *cd = &ext_clockevent;
	extern void bsp_timer_ack(void);

	/* Ack the RTC interrupt. */
	bsp_timer_ack();

	cd->event_handler(cd);
	return IRQ_HANDLED;
}

static struct irqaction ext_irqaction = {
	.handler	= ext_timer_interrupt,
	.flags		= IRQF_DISABLED | IRQF_PERCPU | IRQF_TIMER,
	.name		= "EXT",
};

int __cpuinit ext_clockevent_init(int irq)
{
	struct clock_event_device *cd;

	cd = &ext_clockevent;
	cd->rating = 100;
	cd->irq = irq;
	clockevent_set_clock(cd, 32768);
	cd->max_delta_ns = clockevent_delta2ns(0x7fffffff, cd);
	cd->min_delta_ns = clockevent_delta2ns(0x300, cd);
	cd->cpumask = cpumask_of(0);

	clockevents_register_device(&ext_clockevent);

	return setup_irq(irq, &ext_irqaction);
}
