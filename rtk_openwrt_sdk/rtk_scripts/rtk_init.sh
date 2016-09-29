#!/bin/sh

error() {
	echo "$0: $*"
	exit 1
}

usage() {
	echo "Usage: $0 <command> [arguments]"
	echo "Commands:"
	echo "help                             This help text"
	echo "prepare                          prepare realtek must files"
	echo "patch                            patch realtek's stuff to openwrt SDK"
	echo "release <sdk_dir>                release sdk,input the sdk_dir that pre-build modules(xx.ko) are avalible"
	echo "uclibc <dir_rsdk>                config and rebuild uclibc"
	echo "wrapper <dir_rsdk> <dir_linux>   update kernel header and rebuild wrapper"
}

prepare_package() {
	cd  package/kernel/rtl_nf
	rm -fr Makefile
	ln -sf Makefile.build Makefile
	cd -

	cd  package/kernel/rtl_fs
	rm -fr Makefile
	ln -sf Makefile.build Makefile
	cd -
	
#	Prepare Makefile for building rtl_sendfile	
	cd  package/kernel/rtl_sendfile
	rm -fr Makefile
	ln -sf Makefile.build Makefile
	cd -

	cd  package/kernel/fastpath
	rm -fr Makefile
	ln -sf Makefile.build Makefile
	cd -

	cd  package/kernel/rtl_dev_stats
	rm -fr Makefile
	ln -sf Makefile.build Makefile
	cd -
}

release_package() {
#	$1 is the openwrt SDK main path that can get the pre-build .ko or .o proprietary object
#	Remove rtl_nf source code
	cd  package/kernel/rtl_nf
	find ./ -type d -name '.svn' -exec rm -rf {} \;
	rm -fr src
	rm -fr Makefile
	ln -sf Makefile.release Makefile
	cp -fr $1/package/kernel/rtl_nf/release ./
	cd -
	
#	Remove source code of rtl_fs
	cd package/kernel/rtl_fs
	find ./ -type d -name '.svn' -exec rm -rf {} \;
	rm -fr src
	rm -fr Makefile
	ln -sf Makefile.release Makefile
	cp -fr $1/package/kernel/rtl_fs/release ./
	cd -

#	Remove rtl_sendfile source code
	cd  package/kernel/rtl_sendfile
	find ./ -type d -name '.svn' -exec rm -rf {} \;
	rm -fr src/reverse_sendfile.c
	rm -fr Makefile
	ln -sf Makefile.release Makefile
	cp -fr $1/package/kernel/rtl_sendfile/release ./
	cd -

#	remove wapi code
	cd target/linux/realtek/files/drivers/net/wireless/rtl8192cd
	rm wapi*
	cd -

	cd  package/kernel/fastpath
	find ./ -type d -name '.svn' -exec rm -rf {} \;
	rm -fr src/fast_l2tp_core.c
	rm -fr src/fastpath_core.c
	rm -fr src/fast_pppoe_core.c
	rm -fr src/fast_pptp_core.c
	rm -fr src/filter.c
	rm -fr src/filter_v2.c
	rm -fr src/fast_br.c
	rm -fr src/fast_l2tp_core.h
	rm -fr Makefile
	ln -sf Makefile.release Makefile
	cp -fr $1/package/kernel/fastpath/release ./
	cd -

	cd  package/kernel/rtl_dev_stats
	find ./ -type d -name '.svn' -exec rm -rf {} \;
	rm -fr src
	rm -fr Makefile
	#ln -sf Makefile.release Makefile
	#cp -fr $1/package/kernel/rtl_dev_stats/release ./
	cd -
}

release_sdk() {
#	Remove some proprietary	stuff
	# remove document
	rm -rf rtk_document/ 
	# remove download rsdk tar toolchain in dl/
	rm dl/rsdk-4.6.4-5281-EB-3.10-0.9.33-m32ub-20141001.tar.bz2
	rm dl/rsdk-4.6.4-4181-EB-3.10-0.9.33-m32u-20141001.tar.bz2
}

prepare_rsdk_toolchain() {
	mkdir -p dl
	mkdir -p staging_dir

	if [ ! -e dl/rsdk-4.6.4-5281-EB-3.10-0.9.33-m32ub-20141001.tar.bz2 ]; then
		svn export http://cadinfo.realtek.com.tw/svn/CN/jungle/trunk/toolchain/rsdk/uclibc/rsdk-4.6.4-5281-EB-3.10-0.9.33-m32ub-20141001.tar.bz2 dl/rsdk-4.6.4-5281-EB-3.10-0.9.33-m32ub-20141001.tar.bz2
		tar xvfj dl/rsdk-4.6.4-5281-EB-3.10-0.9.33-m32ub-20141001.tar.bz2 -C staging_dir/
	fi
        if [ ! -e dl/rsdk-4.6.4-4181-EB-3.10-0.9.33-m32u-20141001.tar.bz2 ]; then
		svn export http://cadinfo.realtek.com.tw/svn/CN/jungle/trunk/toolchain/rsdk/uclibc/rsdk-4.6.4-4181-EB-3.10-0.9.33-m32u-20141001.tar.bz2 dl/rsdk-4.6.4-4181-EB-3.10-0.9.33-m32u-20141001.tar.bz2
		tar xvfj dl/rsdk-4.6.4-4181-EB-3.10-0.9.33-m32u-20141001.tar.bz2 -C staging_dir/
	fi
	cp include/site/mips-openwrt-linux-uclibc include/site/mips-rlx5281-linux
	cp include/site/mips-openwrt-linux-uclibc include/site/mips-rlx4181-linux
}

release() {
	prepare_rsdk_toolchain
	release_package	$1
	release_sdk
}

prepare() {
	prepare_rsdk_toolchain
	prepare_package
}

rtk_patch() {
#       patch 80M support in LUCI
	mkdir -p feeds/luci/contrib/package/luci/patches
	cp rtk_scripts/patches/luci/*.patch feeds/luci/contrib/package/luci/patches

#	patch for auto mounting rtl_fs
	mkdir -p package/system/mountd/patches
	cp rtk_scripts/patches/mountd/*.patch package/system/mountd/patches

#	patch for rtk nand support in jffs2 case
	mkdir -p package/system/fstools/patches
	cp rtk_scripts/patches/fstools/*.patch package/system/fstools/patches
	
#	patch for samba using reverse sendfile fastpath and enabling fsync configuration
	mkdir -p package/network/services/samba36/patches
	cp rtk_scripts/patches/samba36/920-rtl_sendfile-samba.patch package/network/services/samba36/patches
	patch < rtk_scripts/patches/samba36/rtl_sendfile-samba-makefile.patch package/network/services/samba36/Makefile
	patch < rtk_scripts/patches/samba36/smb1-and-fsync-smbconf.patch package/network/services/samba36/files/smb.conf.template
}

uclibc() {
	WRAPPER=$1/bin/rsdk-linux-wrapper
	UCLIBC=$1/config/uclibc			
	[ -e $WRAPPER ] || error "WRAPPER not found"
	echo "[WRAPPER] rebuilding uclibc ..."
	rm -f $UCLIBC/extra/config/zconf.tab.o
	$WRAPPER -uclibc || error "[WRAPPER] rebuild uclibc failed"
	echo "[WRAPPER] uclibc update completed"
}

wrapper() {
	WRAPPER=$1/bin/rsdk-linux-wrapper
	DIR_LINUX=$2
	[ -e $WRAPPER ] || error "WRAPPER not found"
	[ -e $DIR_LINUX ] || error "LINUX not found"
	echo "[WRAPPER] rebuilding wrapper ..."
	echo "INFO: updating headers from $DIR_LINUX"
	$WRAPPER -kernel $DIR_LINUX -silent || erraor "[WRAPPER] rebuild wrapper failed"
	echo "[WRAPPER] wrapper update completed"
}

COMMAND="$1"; shift
case "$COMMAND" in
	help) usage;;
	prepare) prepare;;
	uclibc) uclibc "$@";;
	wrapper) wrapper "$@";;
	release) release "$@";;
	patch) rtk_patch;;
	*) usage;;
esac

