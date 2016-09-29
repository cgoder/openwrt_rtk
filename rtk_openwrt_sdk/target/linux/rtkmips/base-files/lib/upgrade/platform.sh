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
	local bootmode_cmd=`cat /proc/flash/bootmode`
	local bootbank_cmd=`cat /proc/flash/bootbank`
	local bootmode=0
	local cur_bootbank=0
	local next_bootbank=$cur_bootbank
	PART_NAME=linux

	[ -f /proc/flash/bootmode ] && [ -f /proc/flash/bootbank ] && {
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
	}
	
	default_do_upgrade "$ARGV"
	echo $next_bootbank > /proc/flash/bootbank
	sleep 1
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

rtk_pre_upgrade() {
	echo "- rtk_pre_upgrade -"
	if [ -n "$RAMDISK_SWITCH" ]; then
		if [ -n "$NO_LDD_SUPPORT" ]; then
        		install_ram_libs
		fi
	fi
	disable_watchdog
}

append sysupgrade_pre_upgrade rtk_pre_upgrade
