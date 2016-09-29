#!/bin/sh

VPN_SERVER_PUBLIC_IP_FILE="/etc/openvpn/vpn_server_ip"
#VPN_SERVER_CONFIG_FILE="/etc/openvpn/vpn_server.conf"
VPN_CLIENT_PUBLIC_IP_FILE="/etc/openvpn/vpn_client_ip"
#VPN_CLIENT_CONFIG_FILE="/etc/openvpn/vpn_client.conf"
VPN_CONFIG_FILE="/etc/config/openvpn"

VPN_ROLE=""
VPN_SET_MODE=""
VPN_SERVER_IP=""
VPN_CLIENT_IP=""

MAX_TRY_NUM=3

VPN_SERVER_PRIVATE_IP=${1:-172.89.29.100}
VPN_CLIENT_PRIVATE_IP=${2:-172.89.29.101}

parse_vpn_config_file()
{
	if [ ! -e $VPN_CONFIG_FILE ]
	then
		killall openvpn > /dev/null 2>&1	
		echo "VPN Config File does not exist!"
		exit 1
	fi
	if ! grep "enable_vpn" $VPN_CONFIG_FILE	
	then
		killall openvpn > /dev/null 2>&1
		echo "VPN is Disabled"
		exit 1
	fi
	if grep "vpn_role 'server'" $VPN_CONFIG_FILE
	then
		VPN_ROLE="server"		
	else
		VPN_ROLE="client"
	fi	
	
	if grep "setting_mode 'auto'" $VPN_CONFIG_FILE
	then
		VPN_SET_MODE="auto"		
	else
		VPN_SET_MODE="manual"
		if grep "server_ip" $VPN_CONFIG_FILE
		then
			VPN_SERVER_IP=`grep "server_ip" $VPN_CONFIG_FILE | cut -d ' ' -f 3 | tr -cs 0-9. ' '`	
		else
			echo "VPN is Set Manual Mode, But Server IP is not set"
			exit 1	
		fi
		if grep "client_ip" $VPN_CONFIG_FILE
		then
			VPN_CLIENT_IP=`grep "client_ip" $VPN_CONFIG_FILE | cut -d ' ' -f 3 | tr -cs 0-9. ' '`	
		else
			echo "VPN is Set Manual Mode, But Client IP is Not Set"
			exit 1	
		fi
		
		if grep "server_tunnel_ip" $VPN_CONFIG_FILE
		then
			VPN_SERVER_PRIVATE_IP=`grep "server_tunnel_ip" $VPN_CONFIG_FILE | cut -d ' ' -f 3 | tr -cs 0-9. ' '`	
		fi
		if grep "client_tunnel_ip" $VPN_CONFIG_FILE
		then
			VPN_CLIENT_PRIVATE_IP=`grep "client_tunnel_ip" $VPN_CONFIG_FILE | cut -d ' ' -f 3 | tr -cs 0-9. ' '`	
		fi
	fi	
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

start_vpn_client()
{
	if [ $VPN_SET_MODE = "auto" ]
	then
		killall cloud_user > /dev/null 2>&1	
		get_vpn_server_public_ip
	else
		echo "VpnServerIp:$VPN_SERVER_IP" > $VPN_SERVER_PUBLIC_IP_FILE
		/usr/sbin/openvpn_client_start.sh $VPN_SERVER_PRIVATE_IP $VPN_CLIENT_PRIVATE_IP
	fi
}

start_vpn_server()
{
	if [ $VPN_SET_MODE = "auto" ]
	then
		killall cloud_device > /dev/null 2>&1
		cloud_device id_00005 00005
	else
		echo "VpnClientIp:$VPN_CLIENT_IP" > $VPN_CLIENT_PUBLIC_IP_FILE 
		/usr/sbin/openvpn_server_start.sh $VPN_SERVER_PRIVATE_IP $VPN_CLIENT_PRIVATE_IP
	fi
}

parse_vpn_config_file

if [ $VPN_ROLE = "server" ]
then 
	start_vpn_server
else
	start_vpn_client
fi
