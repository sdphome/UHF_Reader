#!/bin/sh

IP=$1
MASK=$2
GATE=$3
DNS=$4
ETH0_CFG=/etc/sysconfig/network-scripts/ifcfg-eth0

echo
echo "Setup ip address"
echo "ip:${IP} mask:${MASK} gate:${GATE} dns:${DNS}"
echo

ifconfig eth0 ${IP}
ifconfig eth0 ${IP} netmask ${MASK}
route add default gw ${GATE}

echo "DEVICE=eth0" > ${ETH0_CFG}
echo "ONBOOT=yes" >> ${ETH0_CFG}
echo "BOOTPROTO=static" >> ${ETH0_CFG}
echo "IPADDR=${IP}" >> ${ETH0_CFG}
echo "NETMASK=${MASK}" >> ${ETH0_CFG}
echo "GATEWAY=${GATE}" >> ${ETH0_CFG}

echo "nameserver 127.0.0.1" > /etc/resolv.conf
echo "nameserver ${DNS}" >> /etc/resolv.conf

#/etc/init.d/network restart
