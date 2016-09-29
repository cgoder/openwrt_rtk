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
#include <linux/autoconf.h>
#include "bspchip.h"
#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"

#define RTL819X_BUTTONS_POLL_INTERVAL   20
#define RTL819X_BUTTONS_DEBOUNCE_INTERVAL   3*RTL819X_BUTTONS_POLL_INTERVAL
extern void rtl819x_add_device_usb(void);
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);

static struct gpio_led rtl8972d_v100_ata_leds_gpio[] __initdata = {
	{
		.name		= "rtl819x:green:sys",
		.gpio		= BSP_GPIO_PIN_G3,
		.active_low	= 1,
	},
	{
		.name		= "rtl819x:green:wps",
		.gpio		= BSP_GPIO_PIN_G4,
		.active_low	= 1,
	},
	{
		.name		= "rtl819x:green:voip0",
		.gpio		= BSP_GPIO_PIN_G5,
		.active_low	= 1,
	},
	{
		.name		= "rtl819x:green:voip1",
		.gpio		= BSP_GPIO_PIN_G6,
		.active_low	= 1,
	}
};

static struct gpio_button rtl8972d_v100_ata_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = RTL819X_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_GPIO_PIN_G2,
		.active_low	= 1,
	}, {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= BTN_1,
		.debounce_interval = RTL819X_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_GPIO_PIN_G1,
		.active_low	= 1,
	} 
};

static void __init mach_RTL8972D_V100_ATA_setup(void)
{
	int i;

#ifdef CONFIG_ARCH_BUS_USB
	rtl819x_add_device_usb();
#endif

#ifdef CONFIG_LEDS_GPIO
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(rtl8972d_v100_ata_leds_gpio),
		rtl8972d_v100_ata_leds_gpio);

	for (i=0; i<ARRAY_SIZE(rtl8972d_v100_ata_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(rtl8972d_v100_ata_leds_gpio[i].gpio);
	}
#endif
	for (i=0; i<ARRAY_SIZE(rtl8972d_v100_ata_gpio_buttons); i++) {
		rtl819x_gpio_pin_enable(rtl8972d_v100_ata_gpio_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, RTL819X_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(rtl8972d_v100_ata_gpio_buttons),
				       rtl8972d_v100_ata_gpio_buttons);
}

pure_initcall(mach_RTL8972D_V100_ATA_setup);

void mach_RTL8972D_V100_ATA_export_gpio_pin(void)
{
	int i;

	for (i=0; i<ARRAY_SIZE(rtl8972d_v100_ata_leds_gpio); i++) {
		gpio_export(rtl8972d_v100_ata_leds_gpio[i].gpio, 1);
		rtl819x_gpio_pin_set_val(rtl8972d_v100_ata_leds_gpio[i].gpio, 1);
	}

	/* Button gpio */
	for (i=0; i<ARRAY_SIZE(rtl8972d_v100_ata_gpio_buttons); i++) {
		gpio_export(rtl8972d_v100_ata_gpio_buttons[i].gpio,1);
	}
}

late_initcall(mach_RTL8972D_V100_ATA_export_gpio_pin);

