#
# Makefile for the fastpath modules on top of IPv4.
#

#include $(DIR_ROOT)/.config
export DIR_LINUX := $(srctree)

#EXTRA_CFLAGS += -I $(DIR_LINUX)/drivers/net/rtl819x
EXTRA_CFLAGS += -I $(DIR_LINUX)/net
EXTRA_CFLAGS += -D__KERNEL__
#EXTRA_CFLAGS += -Wno-implicit -Werror

ifeq "$(CONFIG_MODEL_RTL89xxC_SDK)" "y"
EXTRA_CFLAGS += --save-temps
endif

ifeq ($(CONFIG_FAST_PATH_MODULE),y)
#ifeq ($(CONFIG_RTL_IPTABLES_FAST_PATH),y) #for module
EXTRA_CFLAGS += -DCONFIG_RTK_IPTABLES_FAST_PATH
EXTRA_CFLAGS += -DCONFIG_FAST_PATH_MODULE
#EXTRA_CFLAGS += -DEXPORT_SYMTAB

#FASTPATH_OBJ=fastpath_core.o fastpath_common.o filter.o fast_pptp_core.o fast_l2tp_core.o
FASTPATH_OBJ=fastpath_core.o fastpath_common.o filter.o fast_pptp_core.o fast_l2tp_core.o fast_pppoe_core.o fast_filter.o
FASTPATH_MODULE=fastpath.o
#obj-$(CONFIG_RTL_IPTABLES_FAST_PATH) += $(FASTPATH_MODULE)
obj-m += $(FASTPATH_MODULE)
fastpath-objs := $(FASTPATH_OBJ)

else #for module
obj-$(CONFIG_RTL_IPTABLES_FAST_PATH) += fastpath_core.o fastpath_common.o filter.o fast_pptp_core.o fast_l2tp_core.o

ifeq ($(CONFIG_RTL_FAST_FILTER), y)
obj-$(CONFIG_RTL_IPTABLES_FAST_PATH) += fast_filter.o
else
obj-$(CONFIG_RTL_IPTABLES_FAST_PATH) += filter_v2.o
endif

ifeq ($(CONFIG_RTL_FAST_PPPOE), y)
obj-$(CONFIG_RTL_IPTABLES_FAST_PATH) += fast_pppoe_core.o
endif

ifeq ($(CONFIG_RTL_FAST_IPV6), y)
obj-$(CONFIG_RTL_IPTABLES_FAST_PATH) += fast_ipv6_core.o
endif
endif #end for module

obj-$(CONFIG_RTL_FAST_BRIDGE) += fast_br.o 

clean:
	rm -rf *.o *.ko *.mod.c

EXTRA_AFLAGS += $(EXTRA_CFLAGS)
