PART_NAME=linux
RAMDISK_SWITCH=1
#NO_LDD_SUPPORT=1

platform_check_image() {
	[ "$ARGC" -gt 1 ] && return 1

	case "$(get_magic_word "$1")" in
		# .cvimg files
		6373) return 0;;
		*)
			echo "Invalid image type. Please use only .trx files"
			return 1
		;;
	esac
}

platform_do_upgrade() {
	
	default_do_upgrade "$ARGV"
}
# use default for platform_do_upgrade()

# without toolchain ldd support(NO_LDD_SUPPORT=1) , you have to below before switch root to ramdisk
#realtek pre upgrade
install_ram_libs() {
	echo "- install_ram_libs -"
	ramlib="$RAM_ROOT/lib"
	mkdir -p "$ramlib"
	cp /lib/*.so.* $ramlib 
	cp /lib/*.so $ramlib 
}

disable_watchdog() {
        killall watchdog
        ( ps | grep -v 'grep' | grep '/dev/watchdog' ) && {
                echo 'Could not disable watchdog'
                return 1
        }
}
rtk_dualimage_check() {
        local bootmode_cmd=`cat /tmp/bootmode`
        local bootbank_cmd=`cat /tmp/bootbank`
	local bootmode=0
        local cur_bootbank=0
        local next_bootbank=$cur_bootbank
        PART_NAME=linux

        [ -f /proc/flash/bootoffset ] && {
        bootmode=$bootmode_cmd
        cur_bootbank=$bootbank_cmd
        if [ $bootmode = '1' ];then
                echo "It's dualimage toggle mode,always burn image to backup and next boot from it"
                PART_NAME=linux_backup
                if [ $cur_bootbank = '0' ];then
                next_bootbank=1
                else
                next_bootbank=0
                fi
        fi
	rtk_bootinfo setbootbank $next_bootbank
	sleep 1
        }
}


rtk_pre_upgrade() {
	echo "- rtk_pre_upgrade -"
	rtk_dualimage_check
	if [ -n "$RAMDISK_SWITCH" ]; then
		if [ -n "$NO_LDD_SUPPORT" ]; then
        		install_ram_libs
		fi
	fi
	disable_watchdog
}

append sysupgrade_pre_upgrade rtk_pre_upgrade
