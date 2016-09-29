#
# Copyright (C) 2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rtl_fs
PKG_VERSION:=0.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

include $(TOPDIR)/.config

KERNEL_SOURCE_PATH:=$(KERNEL_BUILD_DIR)/linux-3.10.49
KERNEL_BUILD_PATH:=$(KERNEL_BUILD_DIR)/linux-3.10.49
EXT_MODULE_FLAGS:=

ifdef CONFIG_TARGET_rtkmips_rtl8198c
  MODULE_TARGET:=r274734
endif

define KernelPackage/rtl_fs
  SUBMENU:=Filesystems
  TITLE:=Realtek High Performance NTFS/exFAT/HFS+ filesystem
  FILES:=$(PKG_BUILD_DIR)/$(MODULE_TARGET)/jnl.ko
  FILES+=$(PKG_BUILD_DIR)/$(MODULE_TARGET)/ufsd.ko
  AUTOLOAD:=$(call AutoLoad,,ufsd)
endef

define KernelPackage/rtl_fs/description
  Realtek kernel module for supporting NTFS/exFAT/HFS+ filesystem formats with high performance.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/$(MODULE_TARGET)
	$(INSTALL_BIN) ./release/$(MODULE_TARGET)/*.ko $(PKG_BUILD_DIR)/$(MODULE_TARGET)/
	$(INSTALL_BIN) ./release/$(MODULE_TARGET)/mk* $(PKG_BUILD_DIR)/$(MODULE_TARGET)/
	$(INSTALL_BIN) ./release/$(MODULE_TARGET)/chk* $(PKG_BUILD_DIR)/$(MODULE_TARGET)/
#	$(INSTALL_BIN) ./release/$(MODULE_TARGET)/sysdump_home_nas $(PKG_BUILD_DIR)/$(MODULE_TARGET)/
endef

define Build/Configure
	
endef

define Build/Compile
	
endef

define KernelPackage/rtl_fs/install
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(MODULE_TARGET)/*.ko $(1)/lib/modules/3.10.49
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(MODULE_TARGET)/mk* $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(MODULE_TARGET)/chk* $(1)/usr/sbin/
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(MODULE_TARGET)/sysdump_home_nas $(1)/usr/sbin/
endef

$(eval $(call KernelPackage,rtl_fs))
