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


static unsigned int rtl819x_gpio_mux(u32 pin, u32 *value, u32 *address );

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

	#if 0
	printk("%s(%d)xxx 0x%08x\n",__FUNCTION__,__LINE__,
		__raw_readl((void __iomem*)PINMUX_SEL_REG(_ata_rtl8972d_v1xx_leds_gpio[i].gpio)));
	printk("%s(%d)xxx 0x%08x\n",__FUNCTION__,__LINE__,
		__raw_readl((void __iomem*)BSP_GPIO_CNR_REG(_ata_rtl8972d_v1xx_leds_gpio[i].gpio)));
	printk("%s(%d)xxx 0x%08x\n",__FUNCTION__,__LINE__,
		__raw_readl((void __iomem*)BSP_GPIO_DIR_REG(_ata_rtl8972d_v1xx_leds_gpio[i].gpio)));

	printk("%s(%d)xxx pin=%d, val=%d\n",__FUNCTION__,__LINE__,pin,value);
	printk("%s(%d)xxx 0x%08x\n",__FUNCTION__,__LINE__,REG32(BSP_GPIO_DAT_REG(pin)));
	#endif

	if (value == 0)
		data &= ~(1 << BSP_GPIO_BIT(pin));
	else
		data |= (1 << BSP_GPIO_BIT(pin));

	//printk("%s(%d)yyy 0x%08x\n",__FUNCTION__,__LINE__,data);

	__raw_writel(data, (void __iomem*)BSP_GPIO_DAT_REG(pin));

	//printk("%s(%d)xxx 0x%08x\n",__FUNCTION__,__LINE__,
	//	__raw_readl((void __iomem*)BSP_GPIO_DAT_REG(pin)));

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
	unsigned int mask  = 0;
	unsigned int mux =0;
	unsigned int mux_reg;
	unsigned int val;
	


	if (pin >= BSP_GPIO_PIN_MAX)
		return;

	spin_lock_irqsave(&rtl819x_gpio_lock, flags);

	/* pin MUX1 */
	mask = rtl819x_gpio_mux(pin,&val,&mux_reg);

	//mux  = __raw_readl((void __iomem*) BSP_PINMUX_SEL_REG(pin));
	mux  = __raw_readl((void __iomem*)mux_reg);

	//if (mask != 0 && (mux & mask) == 0)
	if (mask != 0)
	    __raw_writel( ((mux&(~mask)) | (val)), (void __iomem*)mux_reg);

	/* 0 as BSP_GPIO pin */
	__raw_writel(__raw_readl((void __iomem*)BSP_GPIO_CNR_REG(pin)) & ~(1<<BSP_GPIO_BIT(pin)), 
					(void __iomem*)BSP_GPIO_CNR_REG(pin));

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

static unsigned int rtl819x_gpio_mux(u32 pin, u32 *value, u32 *address )
{
	unsigned int mask = 0;

	switch(pin) {

		// GPIOA , re-define 
		case BSP_GPIO_PIN_A0:
		/* 0xB800-0040 bit 17:16 */
		mask = 0x3<<16;
		*value = 0x3<<16;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_A1:
		/* 0xB800-0040 bit 13:12 */
		mask = 0x3<<12;
		*value = 0x3<<12;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_A2:
		case BSP_GPIO_PIN_A3:
		case BSP_GPIO_PIN_A4:
		case BSP_GPIO_PIN_A5:
		case BSP_GPIO_PIN_A6:
		/* 0xB800-0040 bit 2:0 , need to be 110 to GPIO mode */
		mask = 0x7<<0;
		*value = 0x6<<0;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_A7:
		case BSP_GPIO_PIN_B0:
		/* 0xB800-0040 bit 2:0 */
		mask = 0x1<<5;
		*value = 0x1<<5;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_B1:
		/* 0xB800-0040 bit 6 */
		mask = 0x1<<6;
		*value = 0x1<<6;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_B2:
		/* 0xB800-0044 bit 1:0 */
		mask = 0x3<<0;
		*value =  0x3<<0;
		*address=0xb8000044;
		break;

		case BSP_GPIO_PIN_B3:
		/* 0xB800-0044 bit 4:3 */
		mask = 0x3<<3;
		*value =  0x3<<3;
		*address=0xb8000044;
		break;

   case BSP_GPIO_PIN_B4:
		/* 0xB800-0044 bit 7:6 */
		mask = 0x3<<6;
		*value =  0x3<<6;
		*address=0xb8000044;
		break;
		
		case BSP_GPIO_PIN_B5:
		/* 0xB800-0044 bit 11:9 */
		mask = 0x3<<9;
		*value =  0x3<<9;
		*address=0xb8000044;
		break;

		case BSP_GPIO_PIN_B6:
		/* 0xB800-0044 bit 13:12 */
		mask = 0x3<<12;
		*value =  0x3<<12;
		*address=0xb8000044;
		break;

		case BSP_GPIO_PIN_B7:
		/* 0xB800-0044 bit 17:15 */
		mask = 0x7<<15;
		*value =  0x4<<15;
		*address=0xb8000044;
		break;

		///////////////////////////////
		case BSP_GPIO_PIN_C0:
		/* 0xB800-0044 bit 20:18 */
		mask = 0x7<<18;
		*value =  0x4<<18;
		*address=0xb8000044;
		break;

		case BSP_GPIO_PIN_C1:
		/* 0xB800-0040 bit 21:20 */
		mask = 0x3<<20;
		*value =  0x3<<20;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_C2:
		/* 0xB800-0040 bit 23:22 */
		mask = 0x3<<22;
		*value =  0x3<<22;
		*address=0xb8000040;
		break;

		case BSP_GPIO_PIN_C3:
		/* 0xB800-0040 bit 25:24 */
		mask = 0x3<<24;
		*value =  0x3<<24;
		*address=0xb8000040;
		break;


		case BSP_GPIO_PIN_C4:
		/* 0xB800-0040 bit 27:26 */
		mask = 0x3<<26;
		*value =  0x3<<26;
		*address=0xb8000040;
		break;
		
		case BSP_GPIO_PIN_C5:
		/* 0xB800-0040 bit 29:28 */
		mask = 0x3<<28;
		*value =  0x3<<28;
		*address=0xb8000040;
		break;
		
		case BSP_GPIO_PIN_C6:
		/* 0xB800-0040 bit 19:18 */
		mask = 0x3<<18;
		*value =  0x3<<18;
		*address=0xb8000040;
		break;
         
		case BSP_GPIO_PIN_E0:
		case BSP_GPIO_PIN_E1:
		case BSP_GPIO_PIN_E2:
		case BSP_GPIO_PIN_E3:
		case BSP_GPIO_PIN_E4:
		case BSP_GPIO_PIN_E5:
		case BSP_GPIO_PIN_E6:
		case BSP_GPIO_PIN_E7:
		case BSP_GPIO_PIN_F0:
		case BSP_GPIO_PIN_F1:
		case BSP_GPIO_PIN_F2:
		case BSP_GPIO_PIN_F3:
		case BSP_GPIO_PIN_F4:
		/* 0xB800-0040 bit 9:8 */
		mask = 0x3<<8;
		*value =  0x3<<8;
		*address=0xb8000040;
		break;

		//case BSP_GPIO_PIN_D0: 	//?
		//case BSP_GPIO_PIN_D1: 	//?
    case BSP_GPIO_PIN_F5:
		case BSP_GPIO_PIN_F6:
		/* 0xB800-0040 bit 4:3 */
		mask = 0x3<<3;
		*value =  0x3<<3;
		*address=0xb8000040;
		break;


		
	

		case BSP_GPIO_PIN_G0:
		case BSP_GPIO_PIN_G1:
		case BSP_GPIO_PIN_G2:
		case BSP_GPIO_PIN_G3:	//?
		case BSP_GPIO_PIN_G4:	//?
		case BSP_GPIO_PIN_G5:	//?
		case BSP_GPIO_PIN_G6:	//?
		case BSP_GPIO_PIN_G7:	//?
		/* 0xB800-0040 bit 11:10 */
		mask = 0x3<<10;
		*value =  0x3<<10;
		*address=0xb8000040;
		break;
			

		default:
		break;
	}

	return mask;
}

