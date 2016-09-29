#
# Copyright (C) 2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rtl_nf
PKG_VERSION:=0.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

include $(TOPDIR)/.config

ifdef CONFIG_TARGET_realtek_rtl8196e
TARGET_DIR:=4181
endif

ifdef CONFIG_TARGET_realtek_rtl8881a
TARGET_DIR:=5281
endif

ifdef CONFIG_TARGET_realtek_rtl819xd
TARGET_DIR:=5281
endif

ifdef CONFIG_TARGET_rtkmips_rtl8198c
TARGET_DIR:=msdk
endif

ifdef CONFIG_TARGET_rtkmips_rtl8954e
TARGET_DIR:=msdk
endif

ifdef CONFIG_TARGET_rtkmipsel
TARGET_DIR:= msdkl
endif

define KernelPackage/rtl_nf
  SUBMENU:=Network Support
  TITLE:=rtl_nf driver
  FILES:=$(PKG_BUILD_DIR)/rtl_nf.ko
  KCONFIG:=CONFIG_RTL_USB_IP_HOST_SPEEDUP=y
  AUTOLOAD:=$(call AutoLoad,50,rtl_nf)
endef

define KernelPackage/rtl_nf/description
Kernel module to rtl_nf
endef

include $(INCLUDE_DIR)/kernel-defaults.mk

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/release
	$(INSTALL_BIN) release/rtl_nf-$(TARGET_DIR).ko $(PKG_BUILD_DIR)/release/rtl_nf.ko
	echo "obj-m   := rtl_nf.o" > $(PKG_BUILD_DIR)/Makefile
	echo "" > $(PKG_BUILD_DIR)/rtl_nf.c
endef

define Build/Compile
	$(MAKE) $(KERNEL_MAKEOPTS) SUBDIRS="$(PKG_BUILD_DIR)" modules
endef

define KernelPackage/rtl_nf/install
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/release/rtl_nf.ko $(1)/lib/modules/3.10.49
endef

$(eval $(call KernelPackage,rtl_nf))
