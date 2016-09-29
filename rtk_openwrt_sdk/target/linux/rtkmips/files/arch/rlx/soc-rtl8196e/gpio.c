/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2007 Aurelien Jarno <aurelien@aurel32.net>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include "bspchip.h"

static int rtl819x_gpio_mux(u32 pin, u32 *reg, u32 *mask, u32 *val);

static DEFINE_SPINLOCK(rtl819x_gpio_lock);

static int __rtl819x_gpio_get_value(unsigned gpio)
{
	unsigned int data;

	data = (__raw_readl((void __iomem*)BSP_GPIO_DAT_REG(gpio)) >> BSP_GPIO_BIT(gpio) ) & 1;

	return data;
}

static int rtl819x_gpio_get_value(struct gpio_chip *chip, unsigned pin)
{
	if (pin >= BSP_GPIO_PIN_MAX)
		return -1;

	return __rtl819x_gpio_get_value(pin);
}

static int __rtl819x_gpio_set_value(unsigned pin, int value)
{
	unsigned int data;

	data = __raw_readl((void __iomem*)BSP_GPIO_DAT_REG(pin));

	if (value == 0)
		data &= ~(1 << BSP_GPIO_BIT(pin));
	else
		data |= (1 << BSP_GPIO_BIT(pin));

	__raw_writel(data, (void __iomem*)BSP_GPIO_DAT_REG(pin));

	return 0;
}

static void rtl819x_gpio_set_value(struct gpio_chip *chip,
				  unsigned pin, int value)
{
	if (pin >= BSP_GPIO_PIN_MAX)
		return;

	__rtl819x_gpio_set_value(pin, value);
}

static int rtl819x_gpio_direction_input(struct gpio_chip *chip,
				       unsigned pin)
{
	unsigned long flags;

	if (pin >= BSP_GPIO_PIN_MAX)
		return -1;

	spin_lock_irqsave(&rtl819x_gpio_lock, flags);

	/* 0 : input */
	__raw_writel(__raw_readl((void __iomem*)BSP_GPIO_DIR_REG(pin)) & ~(1 << BSP_GPIO_BIT(pin)), 
					(void __iomem*)BSP_GPIO_DIR_REG(pin));

	spin_unlock_irqrestore(&rtl819x_gpio_lock, flags);

	return 0;
}

static int rtl819x_gpio_direction_output(struct gpio_chip *chip,
					unsigned pin, int value)
{
	unsigned long flags;

	if (pin >= BSP_GPIO_PIN_MAX)
		return -1;

	spin_lock_irqsave(&rtl819x_gpio_lock, flags);

	__raw_writel(__raw_readl((void __iomem*)BSP_GPIO_DIR_REG(pin)) | (1 << BSP_GPIO_BIT(pin)), 
					(void __iomem*)BSP_GPIO_DIR_REG(pin) );

	spin_unlock_irqrestore(&rtl819x_gpio_lock, flags);

	return 0;
}


static struct gpio_chip rtl819x_gpio_peripheral = {

	.label				= "rtl819x_gpio",
	.get				= rtl819x_gpio_get_value,
	.set				= rtl819x_gpio_set_value,
	.direction_input	= rtl819x_gpio_direction_input,
	.direction_output	= rtl819x_gpio_direction_output,
	.base				= 0,
};

void rtl819x_gpio_pin_enable(u32 pin)
{
	unsigned long flags;
	u32 mask = 0;
	u32 mux = 0;
	u32 reg = 0;
	u32 val = 0;

	switch(pin) {
		/*
		 * PIN SEL 1
		 */
		case BSP_GPIO_PIN_A2:
		case BSP_GPIO_PIN_A4:
		case BSP_GPIO_PIN_A5:
		case BSP_GPIO_PIN_A6:
		/* 0xB800-0040 bit 2:0 */
		mask = 0x00000007;
		val  = 0x00000006;	//3'b110
		reg  = BSP_PIN_MUX_SEL1;
		break;

		/* 0xB800-0040 bit 4:3 reserved*/

		case BSP_GPIO_PIN_A7:
		case BSP_GPIO_PIN_B0:
		/* 0xB800-0040 bit 5 */
		mask = 0x00000020;
		val  = 0x00000020; //1'b1
		reg  = BSP_PIN_MUX_SEL1;
		break;

		case BSP_GPIO_PIN_B1:
		/* 0xB800-0040 bit 6 */
		mask = 0x00000040;
		val  = 0x00000040; //1'b1
		reg  = BSP_PIN_MUX_SEL1;
		break;

		/* 0xB800-0040 bit 19:7 reserved */

		case BSP_GPIO_PIN_C1:
		/* 0xB800-0040 bit 21:20 */
		mask = 0x00300000;
		val  = 0x00300000;
		reg  = BSP_PIN_MUX_SEL1;
		break;

		case BSP_GPIO_PIN_C2:
		/* 0xB800-0040 bit 23:22 */
		mask = 0x00C00000;
		val  = 0x00C00000;
		reg  = BSP_PIN_MUX_SEL1;
		break;

		case BSP_GPIO_PIN_C3:
		/* 0xB800-0040 bit 25:24 */
		mask = 0x00C00000;
		val  = 0x00C00000;
		reg  = BSP_PIN_MUX_SEL1;
		break;
		
		/* 0xB800-0040 bit 31:26 reserved */

		/*
		 * PIN SEL 2
		 */
		case BSP_GPIO_PIN_B2:
		/* 0xB800-0040 bit 1:0 */
		mask = 0x00000003;
		val  = 0x00000003;
		reg  = BSP_PIN_MUX_SEL2;
		break;

		/* 0xB800-0044 bit 2 reserved */

		case BSP_GPIO_PIN_B3:
		/* 0xB800-0044 bit 4:3 */
		mask = 0x0000000C;
		val  = 0x0000000C;
		reg  = BSP_PIN_MUX_SEL2;
		break;

		/* 0xB800-0044 bit 5 reserved */

		case BSP_GPIO_PIN_B4:
		/* 0xB800-0044 bit 7:6 */
		mask = 0x000000C0;
		val  = 0x000000C0;
		reg  = BSP_PIN_MUX_SEL2;
		break;

		/* 0xB800-0044 bit 8 reserved */

		case BSP_GPIO_PIN_B5:
		/* 0xB800-0044 bit 10:9 */
		mask = 0x00000600;
		val  = 0x00000600;
		reg  = BSP_PIN_MUX_SEL2;
		break;

		/* 0xB800-0044 bit 11 reserved */

		case BSP_GPIO_PIN_B6:
		/* 0xB800-0044 bit 13:12 */
		mask = 0x00003000;
		val  = 0x00003000;
		reg  = BSP_PIN_MUX_SEL2;
		break;

		/* 0xB800-0044 bit 14:12 reserved */

		case BSP_GPIO_PIN_B7:
		/* 0xB800-0044 bit 17:15 */
		mask = 0x00038000;
		val  = 0x00020000; //3'b100
		reg  = BSP_PIN_MUX_SEL2;
		break;

		/* 0xB800-0044 bit 31:18 reserved */

		default:
		/* other gpio pin are not supported */
		printk("%s doesn't support pin %d\n",__FUNCTION__,pin);
		return;
	}

	spin_lock_irqsave(&rtl819x_gpio_lock, flags);

	mux  = __raw_readl((void __iomem*) reg);
	/* set masked bit to zero */
	mux &= ~mask;

	/* set value to masked bit */
	mux |= val;

	//if ((mux & mask) == 0) {
		__raw_writel( mux, (void __iomem*) reg);

		/* 0 as BSP_GPIO pin */
		__raw_writel(__raw_readl((void __iomem*)BSP_GPIO_CNR_REG(pin))& ~(1<<BSP_GPIO_BIT(pin)), 
						(void __iomem*)BSP_GPIO_CNR_REG(pin));
	//} //mark_fix

	spin_unlock_irqrestore(&rtl819x_gpio_lock, flags);
}

void rtl819x_gpio_pin_disable(u32 pin)
{
	unsigned long flags;

	spin_lock_irqsave(&rtl819x_gpio_lock, flags);

	/* 1 as peripheral pin */
	__raw_writel(__raw_readl((void __iomem*)BSP_GPIO_CNR_REG(pin)) | (1<<BSP_GPIO_BIT(pin)), 
					(void __iomem*)BSP_GPIO_CNR_REG(pin));

	spin_unlock_irqrestore(&rtl819x_gpio_lock, flags);
}

void rtl819x_gpio_pin_set_val(u32 pin, int val)
{
	__rtl819x_gpio_set_value(pin, val);
}

int rtl819x_gpio_pin_get_val(u32 pin)
{
	return __rtl819x_gpio_get_value(pin);
}

static int __init rtl819x_gpio_peripheral_init(void)
{
	int err;

	rtl819x_gpio_peripheral.ngpio = BSP_GPIO_PIN_MAX;
	err = gpiochip_add(&rtl819x_gpio_peripheral);

	if (err)
		panic("cannot add rtl89x BSP_GPIO chip, error=%d", err);

	return err;
}
device_initcall(rtl819x_gpio_peripheral_init);

int gpio_to_irq(unsigned gpio)
{
    /* FIXME */
    return -EINVAL;
}
EXPORT_SYMBOL(gpio_to_irq);

int irq_to_gpio(unsigned irq)
{
    /* FIXME */
    return -EINVAL;
}
EXPORT_SYMBOL(irq_to_gpio);  

