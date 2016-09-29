# Realtek Semiconductor Corp.
#
# bsp/Makefile
#     bsp Makefile
#
# Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
#

extra-y  += vmlinux.lds

obj-y := imem-dmem.o prom.o setup.o irq.o timer.o serial.o gpio.o dev_leds_gpio.o dev-gpio-buttons.o

obj-$(CONFIG_RTL89XXD_BOARD_V100) += mach_rtl8972d_v100_ata.o
obj-$(CONFIG_SOC_RTL819XD) += mach_rtl819xd.o
obj-$(CONFIG_PCI) += pci.o
obj-$(CONFIG_ARCH_BUS_USB) += dev_usb.o
CPPFLAGS_vmlinux.lds := $(KBUILD_CFLAGS)
