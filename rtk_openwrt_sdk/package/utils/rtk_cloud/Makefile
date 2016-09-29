#
## Copyright (C) 2006-2009 OpenWrt.org
#
## This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# 

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rtk_cloud
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
STAMP_PREPARED := $(STAMP_PREPARED)_$(call confvar,CONFIG_MTD_REDBOOT_PARTS)

include $(INCLUDE_DIR)/package.mk

define Package/rtk_cloud
  SECTION:=Tool
  CATEGORY:=Utilities
  TITLE:=For communication with rtk cloud server.
endef

define Package/rtk_cloud/description
 This Package is for communication with rtk cloud server.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

target=$(firstword $(subst -, ,$(BOARD)))

MAKE_FLAGS += TARGET="$(target)"
TARGET_CFLAGS += -Dtarget_$(target)=1 -Wall

ifdef CONFIG_MTD_REDBOOT_PARTS
  MAKE_FLAGS += FIS_SUPPORT=1
  TARGET_CFLAGS += -DFIS_SUPPORT=1
endif

define Package/rtk_cloud/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cloud_device $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cloud_user $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,rtk_cloud))
