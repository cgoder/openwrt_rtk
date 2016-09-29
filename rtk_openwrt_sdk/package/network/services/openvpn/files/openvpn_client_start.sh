#!/bin/sh

VPN_SERVER_PUBLIC_IP_FILE="/etc/openvpn/vpn_server_ip"
VPN_CLIENT_CONFIG_FILE="/etc/openvpn/vpn_client.conf"
MAX_TRY_NUM=3

VPN_SERVER_PRIVATE_IP=${1:-172.89.29.100}
VPN_CLIENT_PRIVATE_IP=${2:-172.89.29.101}

create_vpn_config_file()
{
	echo dev tun > $VPN_CLIENT_CONFIG_FILE
	echo proto udp >> $VPN_CLIENT_CONFIG_FILE
	echo lport 1194 >> $VPN_CLIENT_CONFIG_FILE
	echo remote $1 1194 >> $VPN_CLIENT_CONFIG_FILE
	echo ifconfig $VPN_CLIENT_PRIVATE_IP $VPN_SERVER_PRIVATE_IP >> $VPN_CLIENT_CONFIG_FILE
	echo keepalive 10 60 >> $VPN_CLIENT_CONFIG_FILE
	echo ping-timer-rem >> $VPN_CLIENT_CONFIG_FILE
	echo persist-key >> $VPN_CLIENT_CONFIG_FILE
	echo persist-tun >> $VPN_CLIENT_CONFIG_FILE
	echo secret /etc/openvpn/secret.key >> $VPN_CLIENT_CONFIG_FILE
	echo comp-lzo >> $VPN_CLIENT_CONFIG_FILE
	echo verb 3 >> $VPN_CLIENT_CONFIG_FILE 	
}

get_vpn_server_public_ip()
{
	cloud_user id_00005 00005
	sleep 3
	num=1
	while [ $num -lt $MAX_TRY_NUM ] && [ ! -e $VPN_SERVER_PUBLIC_IP_FILE ]
	do
		killall cloud_user
		cloud_user id_00005 00005
		$((num++))
		sleep 4
	done
}

check_whether_vpn_connected()
{
	ping $VPN_SERVER_PRIVATE_IP -c 3
        while [ $? != 0 ]
        do
                sleep 1
                ping $VPN_SERVER_PRIVATE_IP -c 1
        done
}

set_default_gateway()
{
	vpn_server_ip_prefix=`cat $VPN_SERVER_PUBLIC_IP_FILE | cut -d : -f 2 | cut -d . -f 1-3`
	vpn_server_netip=${vpn_server_ip_prefix}.0
	gw_ip=`route -n | grep "UG" | grep "0.0.0.0" | sed 's/  */:/g' | cut -d : -f 2`
	if [ ! -z $gw_ip ]
	then
		route add -net $vpn_server_netip netmask 255.255.255.0 gw $gw_ip
		route del default gw $gw_ip
		route add default gw $VPN_SERVER_PRIVATE_IP
	
		iptables -t nat -I POSTROUTING 1 -o tun0 -j MASQUERADE
	fi
}

start_vpn_client()
{	
	if [ -e $VPN_SERVER_PUBLIC_IP_FILE ]
	then
		vpn_server_ip=`cat $VPN_SERVER_PUBLIC_IP_FILE | cut -d : -f 2`
		if [ ! -z $vpn_server_ip ]
		then
			killall openvpn > /dev/null 2>&1
			create_vpn_config_file $vpn_server_ip
			openvpn --script-security 3 --dev tun --config $VPN_CLIENT_CONFIG_FILE &
			sleep 3
			check_whether_vpn_connected
			ping $VPN_SERVER_PRIVATE_IP -c 1
			if [ $? == 0 ]
			then
				set_default_gateway
				rm $VPN_SERVER_PUBLIC_IP_FILE > /dev/null 2>&1	
			fi
		fi
	else
		echo "Get VPN Server's Public IP Fails!"
		exit 1 
	fi
}

start_vpn_client
