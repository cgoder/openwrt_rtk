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
//#include "bspchip.h"
#include <asm/mach-realtek/bspchip.h>


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
	


    if (pin >= TOTAL_PIN_MAX)
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
    if(pin < BSP_GPIO_PIN_MAX)
    {
        __raw_writel(__raw_readl((void __iomem*)BSP_GPIO_CNR_REG(pin)) & ~(1<<BSP_GPIO_BIT(pin)), 
					(void __iomem*)BSP_GPIO_CNR_REG(pin));
    }

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
        case BSP_UART1_PIN:   
		mask = ((0xf<<3)|(7<<7)|(7<<10)|(0xf<<13));
		*value =  (0x7<<3)|(7<<7)|(7<<10)|(0x8<<13);
		*address=0xB800010C; /*SYS_PIN_MUX_SEL4*/
		break;

        case BSP_UART2_PIN:   
		mask = (0x1<<22)|(3<<23)|(3<<25);
		*value =  (0x0<<22)|(0<<23)|(0<<25);
		*address=0xB8000104;  /*SYS_PIN_MUX_SEL2*/
		break;

		case BSP_GPIO_PIN_E7:
		mask = 0x7<<27;
		*value =  0x3<<27;
		*address=0xB8000108;
		break;
		case BSP_GPIO_PIN_H7: //LED 
		mask = 0x3<<14;
		*value =  0x3<<14;
		*address=0xB8000110;
		break;
		case BSP_GPIO_PIN_H5:	//RESET BTN
		mask = 0x3<<23;
		*value =  0x3<<23;
		*address=0xB800010C;
		break;
		case BSP_GPIO_PIN_H6:	//WPS BTN
		mask = 0x3<<0;
		*value =  0x3<<0;
		*address=0xB8000110;
		break;
		default:
		break;
	}

	return mask;
}


