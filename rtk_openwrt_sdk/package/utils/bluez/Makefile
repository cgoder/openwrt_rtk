#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=bluez
PKG_VERSION:=5.24
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.kernel.org/pub/linux/bluetooth
PKG_MD5SUM:=42d0db236cb25c97697b37ecde0af648

PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/bluez
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libpthread +libreadline +libncurses +libusb-compat +glib2 +dbus +udev +python-bluez +dbus-python +python-gobject $(INTL_DEPENDS) $(ICONV_DEPENDS)
  TITLE:=Realtek Bluetooth utility
  URL:=http://www.bluez.org/
  MENU:=1
endef

define Package/bluez/config
        source "$(SOURCE)/Config.in"
endef

define Package/bluez/conffiles
/etc/config/bluetooth
endef
CONFIGURE_ARGS += \
	--enable-library \
	--disable-systemd \
	--disable-monitor \
	--disable-cups \
	--enable-client \
	--disable-obex \
	--enable-usb \
	--enable-experimental \
	--disable-audio \
	--with-usb=yes \
	--with-udevdir="$(STAGING_DIR)/lib/udev"

define Build/Compile
	$(CP) ./files/hciattach_rtk.c $(PKG_BUILD_DIR)/tools
	$(MAKE) -C $(PKG_BUILD_DIR) \
		LDFLAGS="$(TARGET_LDFLAGS) \
			-L$(ICONV_PREFIX)/lib \
			-L$(INTL_PREFIX)/lib -lm -lncurses" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		all install
endef


#$(INSTALL_BIN) ./files/bluez-utils.init $(1)/etc/init.d/bluez-utils
define Package/bluez/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/include/bluetooth
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/etc/bluetooth/
	$(CP) $(PKG_INSTALL_DIR)/usr/include/bluetooth/ $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/bluetooth $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DATA) ./files/bluetooth.config $(1)/etc/config/bluetooth
	$(INSTALL_DATA) ./files/main.conf $(1)/etc/bluetooth/main.conf
	$(INSTALL_DIR) $(1)/etc/dbus-1/system.d/
	$(INSTALL_DATA) ./files/bluetooth.dbus $(1)/etc/dbus-1/system.d/bluetooth.conf
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/bluez.init $(1)/etc/init.d/bluez
	$(CP) ./files/bluez_test/ $(1)/usr/ -rf
        ifeq ($(CONFIG_SERIAL_RTL_8761A),y)
	$(INSTALL_DIR) $(1)/lib/firmware/rtlbt
	$(CP) ./files/rtk_bluetooth_firmware/serial/rtl8761a/rtl8761a_config $(1)/lib/firmware/rtlbt/rtlbt_config
	$(CP) ./files/rtk_bluetooth_firmware/serial/rtl8761a/rtl8761a_fw $(1)/lib/firmware/rtlbt/rtlbt_fw
        endif
        ifeq ($(CONFIG_USB_RTL_8761A),y)
	$(INSTALL_DIR) $(1)/lib/firmware/
	$(CP) ./files/rtk_bluetooth_firmware/usb/8761A/rtl8761au8192ee_fw $(1)/lib/firmware/rtl8761au8192ee_fw
	$(CP) ./files/rtk_bluetooth_firmware/usb/8761A/rtl8761au8812ae_fw $(1)/lib/firmware/rtl8761au8812ae_fw
	$(CP) ./files/rtk_bluetooth_firmware/usb/8761A/rtl8761au_fw $(1)/lib/firmware/rtl8761au_fw
	$(CP) ./files/rtk_bluetooth_firmware/usb/8761A/rtl8761aw8192eu_fw $(1)/lib/firmware/rtl8761aw8192eu_fw
        endif
endef

$(eval $(call BuildPackage,bluez))
