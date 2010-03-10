#!/bin/bash
#http://www.yolinux.com/TUTORIALS/LinuxTutorialIptablesNetworkGateway.html
#use any wlan connection and set your computer as gw

#ifconfig eth0 10.0.0.3 #set an internal ip (gw for other computers)


#config 
WLANIF=eth2
LANIF=eth0
#eth2 external connection (www)
iptables --table nat --append POSTROUTING --out-interface $WLANIF -j MASQUERADE 
#eth0 internal connection (lan)
iptables --append FORWARD --in-interface $LANIF -j ACCEPT
#enables forwarding for ipv4 conections 
echo 1 > /proc/sys/net/ipv4/ip_forward

#route add  -net 10.0.0.0  netmask 255.0.0.0 gw 192.168.1.37  dev eth0
