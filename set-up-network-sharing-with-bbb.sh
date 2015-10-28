# run this in beagle bone black

### sudo su
### ifconfig usb0 192.168.7.2
### route add default gw 192.168.7.1
### echo "nameserver 8.8.8.8" >> /etc/resolv.conf

# run this in your ubuntu machine, which connected to internet

sudo su
ifconfig eth1 192.168.7.1
iptables --table nat --append POSTROUTING --out-interface eth0 -j MASQUERADE
iptables --append FORWARD --in-interface eth1 -j ACCEPT && echo 1 > /proc/sys/net/ipv4/ip_forward
