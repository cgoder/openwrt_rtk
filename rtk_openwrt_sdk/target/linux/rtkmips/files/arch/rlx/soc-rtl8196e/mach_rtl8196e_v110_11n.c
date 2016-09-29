/*
 *  Buffalo WZR-HP-AG300H board support
 *
 *  Copyright (C) 2011 Felix Fietkau <nbd@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/leds.h>
#ifndef CONFIG_WRT_BARRIER_BREAKER
#include <linux/autoconf.h>
#else
#include <generated/autoconf.h>
#endif
#include "bspchip.h"
#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"

#define RTL819X_BUTTONS_POLL_INTERVAL   100 // orignal is 20 , fine-tune to 100
#define RTL819X_BUTTONS_DEBOUNCE_INTERVAL   3*RTL819X_BUTTONS_POLL_INTERVAL
extern void rtl819x_add_device_usb(void);
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);

static struct gpio_led rtl8196e_v110_11n_leds_gpio[] __initdata = {
	{
		.name		= "rtl819x:green:sys",
		.gpio		= BSP_GPIO_PIN_A6,
		.active_low	= 1,
	},
};

static struct gpio_keys_button rtl8196e_v110_11n_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = RTL819X_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_GPIO_PIN_A5,
		.active_low	= 1,
	}, {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = RTL819X_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_GPIO_PIN_A2,
		.active_low	= 1,
	} 
};

static void __init mach_RTL8196E_V110_11N_setup(void)
{
	int i;

#ifdef CONFIG_ARCH_BUS_USB
	rtl819x_add_device_usb();
#endif

#ifdef CONFIG_LEDS_GPIO
	for (i=0; i<ARRAY_SIZE(rtl8196e_v110_11n_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(rtl8196e_v110_11n_leds_gpio[i].gpio);
	}
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(rtl8196e_v110_11n_leds_gpio),
		rtl8196e_v110_11n_leds_gpio);
#endif
	for (i=0; i<ARRAY_SIZE(rtl8196e_v110_11n_gpio_buttons); i++) {
		rtl819x_gpio_pin_enable(rtl8196e_v110_11n_gpio_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, RTL819X_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(rtl8196e_v110_11n_gpio_buttons),
				       rtl8196e_v110_11n_gpio_buttons);
        //###customized gpio###
        //enable your customized gpio here
        //for example ,
        //rtl819x_gpio_pin_enable(BSP_GPIO_PIN_A6);

}

pure_initcall(mach_RTL8196E_V110_11N_setup);

void mach_RTL196E_V110_11N_export_gpio_pin(void)
{
	int i;

	/* LED gpio */
	for (i=0; i<ARRAY_SIZE(rtl8196e_v110_11n_leds_gpio); i++) {
		gpio_export(rtl8196e_v110_11n_leds_gpio[i].gpio,1);
		rtl819x_gpio_pin_set_val(rtl8196e_v110_11n_leds_gpio[i].gpio, 1);
	}

	/* Button gpio */
	for (i=0; i<ARRAY_SIZE(rtl8196e_v110_11n_gpio_buttons); i++) {
		gpio_export(rtl8196e_v110_11n_gpio_buttons[i].gpio,1);
	}
        //###customized gpio###
        //export your customized gpio here
        //for example ,
        //gpio_export(BSP_GPIO_PIN_A6,1);

}

late_initcall(mach_RTL196E_V110_11N_export_gpio_pin);

