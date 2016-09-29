# Realtek Semiconductor Corp.
#
# bsp/Makefile
#     bsp Makefile
#
#

#
# Sheipa
#
#obj-y := prom.o setup.o irq.o timer.o serial.o
obj-y := prom.o setup.o timer.o serial.o dev-gpio-buttons.o
obj-y += flushall.o
obj-$(CONFIG_PCI) += pci-fixup.o pci-ops.o
obj-$(CONFIG_PCI) += pci.o
obj-$(CONFIG_RTK_XHCI_USB) += xhci-usb.o
obj-$(CONFIG_SATA_AHCI_PLATFORM) += sata.o
obj-$(CONFIG_I2C) += i2c.o
obj-$(CONFIG_SMP) += smp-amon.o
obj-$(CONFIG_MIPS_MT_SMTC) += smtc.o

obj-$(CONFIG_SOC_RTL8198C) += rtl8198c.o
obj-$(CONFIG_IRQ_GIC) += irq-gic.o
obj-$(CONFIG_GPIOLIB) += gpio.o
#obj-$(CONFIG_KEYBOARD_GPIO_POLLED) += dev-gpio-buttons.o
obj-$(CONFIG_LEDS_GPIO) += dev_leds_gpio.o
obj-$(CONFIG_SOC_RTL8198C) += mach_rtl8198c.o
obj-$(CONFIG_MIPS_CMP) += gcmp.o
#obj-$(CONFIG_MIPS_CMP) += amon.o
