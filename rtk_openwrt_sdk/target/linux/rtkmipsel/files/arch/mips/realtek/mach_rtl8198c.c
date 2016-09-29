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
#include <asm/mach-realtek/bspchip.h>

#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"

#define RTL819X_BUTTONS_POLL_INTERVAL   100 // orignal is 20 , fine-tune to 100
#define RTL819X_BUTTONS_DEBOUNCE_INTERVAL   3*RTL819X_BUTTONS_POLL_INTERVAL
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);


static struct gpio_led rtl8198c_leds_gpio[] __initdata = {

#ifndef CONFIG_RTL_8198C_8367RB
	{
		.name		= "rtl819x:green:wps",
		.gpio		= BSP_GPIO_PIN_H7,
		.active_low	= 1,
	},
#endif	
#if 0
	{
		.name		= "rtl819x:green:sys",
		.gpio		= BSP_GPIO_PIN_A6,
		.active_low	= 1,
	}
#endif
};

#ifdef CONFIG_RTL_8198C_8367RB
#define BSP_GPIO_RESET_BUTTON BSP_GPIO_PIN_E7
#else
#define BSP_GPIO_RESET_BUTTON BSP_GPIO_PIN_H5
#endif

static struct gpio_keys_button rtl8198c_buttons[] __initdata = { 
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = RTL819X_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_GPIO_RESET_BUTTON,
		.active_low	= 1,
	}
	,
 	{
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = RTL819X_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_GPIO_PIN_H6,
		.active_low	= 1,
	}

};

static void __init mach_RTL8198c_setup(void)
{
	int i;


#ifdef CONFIG_LEDS_GPIO
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(rtl8198c_leds_gpio),
		rtl8198c_leds_gpio);

	for (i=0; i<ARRAY_SIZE(rtl8198c_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(rtl8198c_leds_gpio[i].gpio);
	}
#endif
	for (i=0; i<ARRAY_SIZE(rtl8198c_buttons); i++) {
		rtl819x_gpio_pin_enable(rtl8198c_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, RTL819X_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(rtl8198c_buttons),
				       rtl8198c_buttons);

	//###customized gpio###
	//enable your customized gpio here
	//for example ,
	//rtl819x_gpio_pin_enable(BSP_GPIO_PIN_A6);
#ifdef CONFIG_SERIAL_RTL_UART1
	rtl819x_gpio_pin_enable(BSP_UART1_PIN);
#endif
#ifdef CONFIG_SERIAL_RTL_UART2
	rtl819x_gpio_pin_enable(BSP_UART2_PIN);
#endif

}

pure_initcall(mach_RTL8198c_setup);

void mach_rtl8198c_export_gpio_pin(void)
{
	int i;

	for (i=0; i<ARRAY_SIZE(rtl8198c_leds_gpio); i++) {
		gpio_export(rtl8198c_leds_gpio[i].gpio, 1);
		rtl819x_gpio_pin_set_val(rtl8198c_leds_gpio[i].gpio, 1);
	}

	/* Button gpio */
	for (i=0; i<ARRAY_SIZE(rtl8198c_buttons); i++) {
		gpio_export(rtl8198c_buttons[i].gpio,1);
	}

	//###customized gpio###	
	//export your customized gpio here
	//for example ,
	//gpio_export(BSP_GPIO_PIN_A6,1);
}

late_initcall(mach_rtl8198c_export_gpio_pin);



