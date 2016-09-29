#
# Makefile for the Tulip ethernet driver
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).
#
# Note 2! The CFLAGS definitions are now in the main makefile...
#Add mips16 Support

DIR_RTLASIC = $(DIR_LINUX)/drivers/net/rtl819x/

ifdef CONFIG_RTL_8370_SUPPORT
obj-y := \
	rtk_api.o \
	rtl8370_asicdrv_acl.o \
	rtl8370_asicdrv.o \
	rtl8370_asicdrv_cputag.o \
	rtl8370_asicdrv_dot1x.o \
	rtl8370_asicdrv_eee.o \
	rtl8370_asicdrv_eeelldp.o \
	rtl8370_asicdrv_fc.o \
	rtl8370_asicdrv_green.o \
	rtl8370_asicdrv_igmp.o \
	rtl8370_asicdrv_inbwctrl.o \
	rtl8370_asicdrv_interrupt.o \
	rtl8370_asicdrv_led.o \
	rtl8370_asicdrv_lut.o \
	rtl8370_asicdrv_meter.o \
	rtl8370_asicdrv_mib.o \
	rtl8370_asicdrv_mirror.o \
	rtl8370_asicdrv_misc.o \
	rtl8370_asicdrv_oam.o \
	rtl8370_asicdrv_phy.o \
	rtl8370_asicdrv_port.o \
	rtl8370_asicdrv_portIsolation.o \
	rtl8370_asicdrv_qos.o \
	rtl8370_asicdrv_rldp.o \
	rtl8370_asicdrv_rma.o \
	rtl8370_asicdrv_rrcp.o \
	rtl8370_asicdrv_scheduling.o \
	rtl8370_asicdrv_specialCongest.o \
	rtl8370_asicdrv_storm.o \
	rtl8370_asicdrv_svlan.o \
	rtl8370_asicdrv_trunking.o \
	rtl8370_asicdrv_unknownMulticast.o \
	rtl8370_asicdrv_vlan.o 
else

obj-y := \
	rtk_api.o \
	rtl8370_asicdrv_acl.o \
	rtl8370_asicdrv.o \
	rtl8370_asicdrv_cputag.o \
	rtl8370_asicdrv_dot1x.o \
	rtl8370_asicdrv_eee.o \
	rtl8370_asicdrv_eeelldp.o \
	rtl8370_asicdrv_fc.o \
	rtl8370_asicdrv_green.o \
	rtl8370_asicdrv_igmp.o \
	rtl8370_asicdrv_inbwctrl.o \
	rtl8370_asicdrv_interrupt.o \
	rtl8370_asicdrv_led.o \
	rtl8370_asicdrv_lut.o \
	rtl8370_asicdrv_meter.o \
	rtl8370_asicdrv_mib.o \
	rtl8370_asicdrv_mirror.o \
	rtl8370_asicdrv_misc.o \
	rtl8370_asicdrv_oam.o \
	rtl8370_asicdrv_phy.o \
	rtl8370_asicdrv_port.o \
	rtl8370_asicdrv_portIsolation.o \
	rtl8370_asicdrv_qos.o \
	rtl8370_asicdrv_rldp.o \
	rtl8370_asicdrv_rma.o \
	rtl8370_asicdrv_rrcp.o \
	rtl8370_asicdrv_scheduling.o \
	rtl8370_asicdrv_specialCongest.o \
	rtl8370_asicdrv_storm.o \
	rtl8370_asicdrv_svlan.o \
	rtl8370_asicdrv_trunking.o \
	rtl8370_asicdrv_unknownMulticast.o \
	rtl8370_asicdrv_vlan.o \
	smi.o \
	gpio.o
endif

#EXTRA_CFLAGS += -O1 -DRTL_TBLDRV -D__linux__  -mno-memcpy -DRTL865X_OVER_KERNEL -DRTL865X_OVER_LINUX -Werror
EXTRA_CFLAGS += -O1 -DRTL_TBLDRV -D__linux__  -mno-memcpy -DRTL865X_OVER_KERNEL -DRTL865X_OVER_LINUX -Wno-implicit
EXTRA_CFLAGS += -I$(DIR_RTLASIC)/RTL8370_RTL8367_API

EXTRA_AFLAGS += $(EXTRA_CFLAGS)
