--[[
LuCI - Lua Configuration Interface

Copyright 2008 Steven Barth <steven@midlink.org>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

$Id: dhcp.lua 9623 2013-01-18 14:08:37Z jow $
]]--

local sys = require "luci.sys"

m = Map("openvpn", translate("OpenVPN"),
	translate("OpenVPN is used to setting up a virtual private network, and it can pass through NAT device." ))

m.on_after_commit = function(self)
luci.sys.call("/usr/sbin/openvpn_start.sh > /dev/null 2>&1")
end

s = m:section(TypedSection, "openvpn", translate("VPN Settings"))
s.anonymous = true
s.addremove = false

s:tab("general", translate("General Settings"))
s:tab("advanced", translate("Advanced Settings"))

s:taboption("general", Flag, "enable_vpn",
	translate("Enable"),
	translate("Enable/Disable VPN")).optional = true

vm = s:taboption("general", ListValue, "vpn_role", translate("VPN Role"))
vm:value("client", translate("vpn client"))
vm:value("server", translate("vpn server"))
vm:depends("enable_vpn", "1")

sm = s:taboption("general", ListValue, "setting_mode", translate("Setting Mode"))
sm:value("auto", translate("auto"))
sm:value("manual", translate("manual"))
sm:depends("enable_vpn", "1")

si = s:taboption("general", Value, "server_ip", translate("VPN Server IP"))
si.datatype = "ip4addr"
si.optional = true
si:depends("setting_mode", "manual")

ci = s:taboption("general", Value, "client_ip", translate("VPN Client IP"))
ci.datatype = "ip4addr"
ci.optional = true
ci:depends("setting_mode", "manual")

sti = s:taboption("general", Value, "server_tunnel_ip", translate("VPN Server Tunnel IP"))
sti.datatype = "ip4addr"
sti.optional = true
sti:depends("setting_mode", "manual")

cti = s:taboption("general", Value, "client_tunnel_ip", translate("VPN Client Tunnel IP"))
cti.datatype = "ip4addr"
cti.optional = true
cti:depends("setting_mode", "manual")

pt = s:taboption("general", Value, "port", translate("VPN Port"))
pt.optional = true
pt.datatype = "port"
pt.placeholder = 1194
pt:depends("enable_vpn", "1")

return m
