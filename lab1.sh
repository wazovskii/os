#!/bin/bash
mask=$(sudo ifconfig en0 | awk '/netmask/{print$4}')
ip=$(ifconfig en0 | awk '/inet 1/{print $2}')
gate=$(route -n get default | awk '/gateway/{print$2}')
speed=$(ifconfig en0 | awk '/media/{print $2}')
mac=$(ifconfig en0 | awk '/ether/{print $2}')
echo
while [ -n "$1" ]
do
case "$1" in
-h)
    echo "Copyright reserved by : Nizamova Veronika"
    echo "Availible arguments are:"
    echo " -h to read help; (example ./lab1 -h)"
    echo " -l to list all network connections; (example ./lab1 -l)"
    echo " -k to kill network connection; (example ./lab1 -k)"
    echo " -r to revive network connection; (example ./lab1 -r)"
    echo " -sip to set ip (example ./lab1 -sip 192.168.1.43)"
    echo " -sm to set mask (example ./lab1 -sm 255.255.255)"
    echo " -sg to set gateway (example ./lab1 -sg 192.168.1.1)"
;;
-l)
    echo " Network interfaces:"
    echo "    Wi-Fi"
    echo "    MAC address: $mac"
    echo "    IP: $ip"
    echo "    Connection speed: $speed"
    echo "    Mask: $mask"
    echo "    Gateway: $gate"
;;
-k)
    sudo ifconfig en0 down
    echo "Wi-Fi is disabled"
;;
-r)
    sudo ifconfig en0 up
    echo "Wi-Fi is enabled"
;;
-sip)
    sudo ifconfig en0 $2
    echo "IP changed to $2"
;;
-sm)
        sudo ifconfig en0 $ip netmask $2
        echo "Mask changed to $2"
;;
-sg)
        sudo route delete default
        sudo route add default $2
        echo "Gateway changed to $2"
;;
esac
shift
done
