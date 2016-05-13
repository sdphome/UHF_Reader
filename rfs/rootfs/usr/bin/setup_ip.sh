#!/bin/sh

TYPE=$1
IP=$2
MASK=$3
GATE=$4
DNS=$5
NET_CFG=/etc/network/interfaces

if [ $1 == "auto" ]; then
	echo
	echo "setup dhcp"
	echo
	echo "auto eth0" > ${NET_CFG}
	echo "iface eth0 inet dhcp" >> ${NET_CFG}
	exit 0
elif [ $1 == "static" ]; then
	echo
	echo "setup static ip."
	echo
else
	echo "wrong cmd!!!"
	exit 1
fi

echo
echo "Setup ip address"
echo "ip:${IP} mask:${MASK} gate:${GATE} dns:${DNS}"
echo

#ifconfig eth0 ${IP}
#ifconfig eth0 ${IP} netmask ${MASK}
#route add default gw ${GATE}

echo "auto lo" > ${NET_CFG}
echo "iface lo inet loopback" >> ${NET_CFG}
echo "" >> ${NET_CFG}

echo "iface atml0 inet dhcp" >> ${NET_CFG}
echo "" >> ${NET_CFG}

echo "auto eth0" >> ${NET_CFG}
echo "iface eth0 inet static" >> ${NET_CFG}
echo "	address ${IP}" >> ${NET_CFG}
echo "	netmask ${MASK}" >> ${NET_CFG}
echo "	gateway ${GATE}" >> ${NET_CFG}

echo "nameserver 127.0.0.1" > /etc/resolv.conf
echo "nameserver ${DNS}" >> /etc/resolv.conf

#/etc/init.d/networking restart
