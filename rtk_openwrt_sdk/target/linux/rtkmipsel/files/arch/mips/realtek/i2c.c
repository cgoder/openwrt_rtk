/*
 * Realtek Semiconductor Corp.
 *
 * bsp/usb.c:
 *     bsp I2C initialization code
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>

#include <asm/mach-realtek/bspchip.h>



/* i2c Host Controller */

static struct resource bsp_i2c_resource[] = {
	[0] = {
		.start = BSP_I2C_MAPBASE,
		.end = BSP_I2C_MAPBASE + BSP_I2C_MAPSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = BSP_PS_I2C_IRQ,
		.end = BSP_PS_I2C_IRQ,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 bsp_i2c_dmamask = 0xFFFFFFFFUL;

struct platform_device bsp_i2c_device = {
	.name = "rtl-i2c",
	.id = -1,
	.num_resources = ARRAY_SIZE(bsp_i2c_resource),
	.resource = bsp_i2c_resource,
	.dev = {
		.dma_mask = &bsp_i2c_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

static struct platform_device *bsp_i2c_devs[] __initdata = {	&bsp_i2c_device,  };

static int __init bsp_i2c_init(void)
{
	int ret;

	printk("INFO: initializing i2c devices ...\n");

	ret = platform_add_devices(bsp_i2c_devs, ARRAY_SIZE(bsp_i2c_devs));
	if (ret < 0) {
		printk("ERROR: unable to add devices\n");
		return ret;
	}

	return 0;
}
arch_initcall(bsp_i2c_init);
