#!/bin/bash

sudo service network-manager stop
sudo killall wvdial
sudo iptables -F
sudo iptables -X
sudo iptables -t nat -F
sudo echo 1 > /proc/sys/net/ipv4/ip_forward
sudo iptables -A FORWARD -i ppp0 -o eth0 -j ACCEPT
sudo iptables -A FORWARD -o ppp0 -i eth0 -j ACCEPT
sudo iptables -t nat -A POSTROUTING -o ppp0 -j MASQUERADE
sudo ifconfig eth0 192.168.3.1 netmask 255.255.255.0 up
sudo wvdial &
sleep 10
sudo ifconfig eth0 192.168.3.1 netmask 255.255.255.0 up
