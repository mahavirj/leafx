#!/bin/bash

# Forward traffic to-and-from ppp0 to ethernet
sudo iptables -A FORWARD -i enp0s25 -o ppp0 -j ACCEPT
sudo iptables -A FORWARD -i ppp0 -o enp0s25 -j ACCEPT

# Enable SNAT in POSTROUTING
sudo iptables -t nat -A POSTROUTING -o ppp0 -j MASQUERADE

# Enable forwarding at IP layer
echo 1 > /proc/sys/net/ipv4/ip_forward

# Start DHCP server with DNS received for ppp0 interface

# OR use dnsmasq with in-built dhcp server on ethernet interface

# sample dhcp config
# # cat /etc/dhcpd.conf
# # Using the google's dns in the example.
# # Change it to 139.96.30.100 if you have a dns server installed
# option domain-name-servers 112.110.249.1, 112.110.249.5;
# option subnet-mask 255.255.255.0;
# option routers 192.168.3.1;
# subnet 192.168.3.0 netmask 255.255.255.0 {
#  range 192.168.3.2 192.168.3.100;
#}

# Happy surfing!
