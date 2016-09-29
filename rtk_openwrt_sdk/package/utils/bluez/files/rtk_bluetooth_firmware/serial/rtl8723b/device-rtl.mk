RTK_BT_FIRMWARE_DIR := rtl8723b
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_fw:system/etc/firmware/rtlbt/rtlbt_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_config:system/etc/firmware/rtlbt/rtlbt_config