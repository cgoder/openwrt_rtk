# 
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

BlockSize=128k
ifeq ($(CONFIG_MTD_NAND_RTK_BLOCK_SIZE),0x80000)
BlockSize=512k
endif
ifeq ($(CONFIG_MTD_NAND_RTK_BLOCK_SIZE),0x20000)
BlockSize=128k
endif

define mkcmdline
board=$(1) console=$(2),$(3) linuxpart=0x$(4)
endef

SINGLE_PROFILES :=

define SingleProfile

  define Image/Build/Profile/$(1)/initramfs
	$(call Image/BuildLoader,loader-$(SUBTARGET)-$(1),bin,$(call mkcmdline,$(1),$(2),$(3)) $(4),$(5))
	cvimg-$(SUBTARGET) linux $(KDIR)/loader-$(SUBTARGET)-$(1).bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-ramfs.bin $(5) $(6)
  endef

ifeq ($(CONFIG_MTD_NAND_RTK),y)
  define Image/Build/Profile/$(1)/squashfs
	$(call Image/BuildLoader,loader-$(SUBTARGET)-$(1),bin,$(call mkcmdline,$(1),$(2),$(3),$(6)),$(5))

	cvimg-$(SUBTARGET) linux $(KDIR)/loader-$(SUBTARGET)-$(1).bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux.bin $(5) $(6)
	dd if=$(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux.bin of=$(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux_4k.bin bs=$(BlockSize) conv=sync
	cat $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux_4k.bin $(KDIR)/root.squashfs-4k > $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw_4k_cat.bin
	cvimg-$(SUBTARGET) fix_chksum  $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw_4k_cat.bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw.bin
	rm -rf $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux_4k.bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw_4k_cat.bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux.bin
  endef
else

  define Image/Build/Profile/$(1)/squashfs
	$(call Image/BuildLoader,loader-$(SUBTARGET)-$(1),bin,$(call mkcmdline,$(1),$(2),$(3),$(6)),$(5))

	cvimg-$(SUBTARGET) linux $(KDIR)/loader-$(SUBTARGET)-$(1).bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux.bin $(5) $(6)
	dd if=$(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux.bin of=$(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux_4k.bin bs=4k conv=sync
	cat $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux_4k.bin $(KDIR)/root.squashfs-4k > $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw_4k_cat.bin
	cvimg-$(SUBTARGET) fix_chksum  $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw_4k_cat.bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw.bin
	rm -rf $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux_4k.bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-fw_4k_cat.bin $(BIN_DIR)/$(IMG_PREFIX)-$(1)-linux.bin
  endef


endif

  SINGLE_PROFILES += $(1)

endef

define MultiProfile

  define Image/Build/Profile/$(1)/initramfs
	$(foreach p,$(2),
		$$(call Image/Build/Profile/$p/initramfs)
	)
  endef

  define Image/Build/Profile/$(1)/squashfs
	$(foreach p,$(2),
		$$(call Image/Build/Profile/$p/squashfs)
	)
  endef

endef

define Image/Prepare
	lzma e $(KDIR)/vmlinux -lc1 -lp2 -pb2 $(KDIR)/vmlinux.bin.lzma
endef

LOADER_MAKE := $(NO_TRACE_MAKE) -C lzma-loader KDIR=$(KDIR) LINUX_DIR=$(LINUX_DIR)

define Build/Clean
	$(LOADER_MAKE) clean
endef

define Image/BuildLoader
	-rm -rf $(KDIR)/lzma-loader
	$(LOADER_MAKE) LOADER=$(1).$(2) KERNEL_CMDLINE="$(3)" \
		LZMA_TEXT_START=$(4) LOADADDR=0x80000000 \
		LOADER_DATA="$(KDIR)/vmlinux.bin.lzma" BOARD="$(1)" \
		compile loader.$(2)
endef

#
# rtl8196c profiles
#
#
ifeq ($(CONFIG_TARGET_realtek_rtl8196c),y)

$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))

endif # CONFIG_TARGET_realtek_rtl8196c

#
# rtl8196e profiles
#
ifeq ($(CONFIG_TARGET_realtek_rtl8196e),y)

$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))
$(eval $(call SingleProfile,AP,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))

endif # CONFIG_TARGET_realtek_rtl8196e

#
# rtl819xd profiles
#
ifeq ($(CONFIG_TARGET_realtek_rtl819xd),y)
ifeq ($(CONFIG_MTD_NAND_RTK),y)
$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,800000))
$(eval $(call SingleProfile,AP,ttyS0,38400,root=/dev/mtdblock2,0x80500000,800000))
else
$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))
$(eval $(call SingleProfile,AP,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))
endif

endif # CONFIG_TARGET_realtek_rtl819xd

#
# rtl819xdt profiles
#
ifeq ($(CONFIG_TARGET_realtek_rtl819xdt),y)

$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,30000))

endif # CONFIG_TARGET_realtek_rtl819xdt

#
# rtl89xxd profiles
#
ifeq ($(CONFIG_TARGET_realtek_rtl89xxd),y)

$(eval $(call SingleProfile,V100_GATEWAY,ttyS0,38400,root=/dev/mtdblock2,0x80500000,30000))
$(eval $(call SingleProfile,V100_AP_ROUTER,ttyS0,38400,root=/dev/mtdblock2,0x80500000,30000))
$(eval $(call SingleProfile,V100_ATA,ttyS0,38400,root=/dev/mtdblock2,0x80500000,30000))
$(eval $(call MultiProfile,Default,$(SINGLE_PROFILES)))

endif # CONFIG_TARGET_realtek_rtl89xxd

#
# rtl8881a profiles
#
ifeq ($(CONFIG_TARGET_realtek_rtl8881a),y)
ifeq ($(CONFIG_MTD_NAND_RTK),y)
$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,800000))
$(eval $(call SingleProfile,AP,ttyS0,38400,root=/dev/mtdblock2,0x80500000,800000))
else
$(eval $(call SingleProfile,None,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))
$(eval $(call SingleProfile,AP,ttyS0,38400,root=/dev/mtdblock2,0x80500000,10000))
endif
endif # CONFIG_TARGET_realtek_rtl8881a

# RAMFS
define Image/Build/Initramfs
	$(call Image/Build/Profile/$(PROFILE)/initramfs)
endef

# SQUASHFS
ifeq ($(CONFIG_MTD_NAND_RTK),y)
define Image/Build
	dd if=$(KDIR)/root.squashfs of=$(KDIR)/root.squashfs-4k bs=$(BlockSize) conv=sync
	$(call add_jffs2_mark,$(KDIR)/root.squashfs-4k)
	$(call Image/Build/Profile/$(PROFILE)/squashfs)
endef
else
define Image/Build	
	dd if=$(KDIR)/root.squashfs of=$(KDIR)/root.squashfs-4k bs=4k conv=sync
	$(call add_jffs2_mark,$(KDIR)/root.squashfs-4k)
	$(call Image/Build/Profile/$(PROFILE)/squashfs)
endef
endif

$(eval $(call BuildImage))
