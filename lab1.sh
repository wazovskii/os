#!/bin/bash
ip=$(ifconfig en0 | awk '/inet 1/{print $2}')
mask=$(sudo ifconfig en0 | awk '/netmask/{print$4}')
gate=$(route -n get default | awk '/gateway/{print$2}')

echo
while [ -n "$1" ]
do
case "$1" in
-h)
    echo "Copyright reserved by : Nizamova Veronika"
    echo "Availible arguments are:"
    echo " -h to read help;"
    echo " -l to list all network connections;"
    echo " -k to kill network connection;"
    echo " -r to revive network connection;"
    echo " -sip to set ip"
    echo " -sm to set mask"
    echo " -sg to set gateway"
;;
-l)
    echo " Network interfaces:"
    echo "    Wi-Fi"
    echo "    MAC address: $(ifconfig en0 | awk '/ether/{print $2}')"
    echo "    IP: $(ifconfig en0 | awk '/inet 1/{print $2}')"
    echo "    Connection speed: $(ifconfig en0 | awk '/media/{print $2}')"
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
    $(sudo ifconfig en0 $2)
    echo "IP changed to $2"
;;
-sm)
        $(sudo ifconfig en0 $ip netmask $2)
        echo "Mask changed to $2"
        echo "Current Mask $(sudo ifconfig en0 | awk '/netmask/{print$4}')"
;;
-sg)
        $(sudo route delete default)
        $(sudo route add default $2)
        echo "Gateway changed to $2"
;;
esac
shift
done
