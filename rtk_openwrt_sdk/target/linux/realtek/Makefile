#
# Copyright (C) 2006-2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=rlx
BOARD:=realtek
BOARDNAME:=Realtek
SUBTARGETS:=rtl819xd rtl8196e rtl8881a
FEATURES:=squashfs
LINUX_VERSION:=3.10.49

include $(INCLUDE_DIR)/target.mk

#DEFAULT_PACKAGES += kmod-gpio-button-hotplug

define Target/Description
	Build firmware images for Realtek based boards
endef

$(eval $(call BuildTarget))
