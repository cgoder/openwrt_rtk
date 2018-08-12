# openwrt_rtk
# RTK OpenWrt SDK 
   -->  rtk_openwrt_sdk.tar.gz : sdk source
   -->  rtk_openwrt_image.tar.gz : sdk pre-build image
   -->  bootcode : bootcode source and pre-build bootcode image 
   -->  document : sdk document

# Build RTK OpenWrt SDK #

1. When you build the SDK for the first time,some internet download operations will be needed,hence the internet service must be avalible on your build code environment.

2. Below are the commands when you build the SDK at the first time

   --> get into the dir "rtk_openwrt_sdk"         (it's our root dir in this SDK)

   --> execute "./scripts/feeds update -a" and "./scripts/feeds install -a"

   --> Copy rtk default config for openwrt 
   For 8198C :
   	--> execute "cp rtk_deconfig/defconfig_rtl8198c .config"    
   For 8954E :
        --> execute "cp rtk_deconfig/defconfig_rtl8954e .config"
   For 8197D :
        --> execute "cp rtk_deconfig/defconfig_rtl8196xd .config"
   For 8196E :
   	--> execute "cp rtk_deconfig/defconfig_rtl8196e .config"    
   For 8881A :
   	--> execute "cp rtk_deconfig/defconfig_rtl8881a .config"       	

   --> execute "make menuconfig" , just leave&save it if no configurations need to be changed.

   --> execute "make" (build image) or "make V=99" (build image with compiling log)

   NOTE1 : Sometimes the make process will be stopped due to the in-consistent kerenl config option,
   you can do "make kernel_menuconfig" to select some new kernel options or just save&exit to sync 
   the kernel options to consistent. 

   NOTE2 : If you do not execute "./scripts/feeds install -a" then you need to execute "./rtk_scripts/rtk_init.sh patch" 
   to patch some realtek's special patches to OpenWRT SDK. 

# Change some kernel options for your HW platform
   Some kernel options may need to be selected for your HW platform(for
   example, select the correct wifi chip and switch type on yuor board)
   
   --> execute "make kernel_menuconfig" and select the options you need.   
   
   NOTE: Check the ApplicationNote to check some important kerenl options for your
         HW platform.

# Image Location
   For 8197D/8196E/8881A :
   --> the image( linux & rootfs )will be put in the dir "bin/realtek/",
      the image is "openwrt-realtek-rtl8196e-AP-fw.bin" for 8196E
      the image is "openwrt-realtek-rtl819xd-AP-fw.bin" for 8197D
      the image is "openwrt-realtek-rtl8881a-AP-fw.bin" for 8881A

   For 8198C/8954E :	
   --> the image( linux & rootfs ) will be put in the dir "bin/rtkmips/",
     the image is "openwrt-rtkmips-rtl8198c-AP-fw.bin" for 8198C
     the image is "openwrt-rtkmips-rtl8954e-AP-fw.bin" for 8954E

   For 8197F :	
   --> the image( linux & rootfs ) will be put in the dir "bin/rtkmipsel/",
     the image is "openwrt-rtkmipsel-rtl8197f-AP-fw.bin" for 8197F (flash 4k erase size)
     the image is "openwrt-rtkmipsel-rtl8197f-AP-64k-fw.bin" for 8197F (flash 64k erase size)
# Upload your firmware image at bootcode stage 
   --> press <ESC> to enter the Tftp server mode at booting stage.
   --> The tftp server default IP is "192.168.1.6" 
   --> use Tftp client tools to upload your image. The firmware will be running
       automatically after flashing.
   
   NOTE: You can also use the same way to update your bootcode image,the latest bootcode
   images that support bring up rtk OpenWRT firmware is under dir : "bootcode/image/"

#  Bootloader source code
   You can find all model's bootloader source under dir "bootcode/src/" , but these are only stable version but not the 
   latest one , for the latest bootcode , please contact to our FAE .

#  Login webserver 
   --> The Router's default IP address is "192.168.1.1" , you can use this ip to login Web server and there is no 
   password for login, just use root and ignore the password field.

 
