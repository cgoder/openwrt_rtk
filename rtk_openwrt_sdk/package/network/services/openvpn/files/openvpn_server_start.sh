#!/bin/sh

VPN_CLIENT_PUBLIC_IP_FILE="/etc/openvpn/vpn_client_ip"
VPN_SERVER_CONFIG_FILE="/etc/openvpn/vpn_server.conf"

VPN_SERVER_PRIVATE_IP=${1:-172.89.29.100}
VPN_CLIENT_PRIVATE_IP=${2:-172.89.29.101}

create_vpn_config_file()
{
	echo dev tun > $VPN_SERVER_CONFIG_FILE
	echo proto udp >> $VPN_SERVER_CONFIG_FILE
	echo lport 1194 >> $VPN_SERVER_CONFIG_FILE
	echo remote $1 1194 >> $VPN_SERVER_CONFIG_FILE
	echo ifconfig $VPN_SERVER_PRIVATE_IP $VPN_CLIENT_PRIVATE_IP >> $VPN_SERVER_CONFIG_FILE
	echo keepalive 10 60 >> $VPN_SERVER_CONFIG_FILE
	echo ping-timer-rem >> $VPN_SERVER_CONFIG_FILE
	echo persist-key >> $VPN_SERVER_CONFIG_FILE
	echo persist-tun >> $VPN_SERVER_CONFIG_FILE
	echo secret /etc/openvpn/secret.key >> $VPN_SERVER_CONFIG_FILE
	echo comp-lzo >> $VPN_SERVER_CONFIG_FILE
	echo verb 3 >> $VPN_SERVER_CONFIG_FILE 	
}

add_iptables_rule()
{
	iptables -S | grep "FORWARD -i tun0 -j ACCEPT"
	if [ $? != 0 ]
	then
		iptables -t filter -I FORWARD 1 -i tun0 -j ACCEPT
	fi
}

start_vpn_server()
{
	while [ ! -e $VPN_CLIENT_PUBLIC_IP_FILE ]
	do
		sleep 1
	done

	if [ -e $VPN_CLIENT_PUBLIC_IP_FILE ]
	then
		vpn_client_ip=`cat $VPN_CLIENT_PUBLIC_IP_FILE | cut -d : -f 2`
		if [ ! -z $vpn_client_ip ]
		then
			killall openvpn > /dev/null 2>&1
			create_vpn_config_file $vpn_client_ip
			openvpn --script-security 3 --dev tun --config $VPN_SERVER_CONFIG_FILE &
			add_iptables_rule
			rm $VPN_CLIENT_PUBLIC_IP_FILE
		fi	
	fi
}

start_vpn_server

