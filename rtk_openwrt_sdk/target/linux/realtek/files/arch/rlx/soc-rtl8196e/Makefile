# Realtek Semiconductor Corp.
#
# bsp/Makefile
#     bsp Makefile
#
# Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
#

extra-y  += vmlinux.lds

obj-y := prom.o setup.o irq.o timer.o serial.o gpio.o dev_leds_gpio.o dev-gpio-buttons.o
obj-$(CONFIG_RTL_8196E_GW) += mach_rtl8196e_v110_11n.o
#obj-$(CONFIG_PCI) += pci-fixup.o pci-ops.o
obj-$(CONFIG_PCI) += pci.o
obj-$(CONFIG_ARCH_BUS_USB) += dev_usb.o

CPPFLAGS_vmlinux.lds := $(KBUILD_CFLAGS)
