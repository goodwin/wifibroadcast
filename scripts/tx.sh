#!/bin/bash
# tx script


#adapt these to your needs
NIC="wlan0"
CHANNEL="1"

WIDTH=1280
HEIGHT=720
FPS=48
BITRATE=4000000
KEYFRAMERATE=48

##################################

#change these only if you know what you are doing (and remember to change them on both sides)
BLOCK_SIZE=8
FECS=4
PACKET_LENGTH=1024
PORT=0

##################################

WBC_PATH="/home/pi/repos/lwerdna/wifibroadcast"


# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

# kill shit
pkill dhcpcd
pkill ntpd

#wait a bit. this help automatic starting
sleep 2

echo "updating wifi ($NIC, $CHANNEL)"
ifconfig $NIC down
iw dev $NIC set monitor otherbss fcsfail
ifconfig $NIC up
iwconfig $NIC channel $CHANNEL

echo "Starting tx for $NIC"
raspivid -ih -t 0 -w $WIDTH -h $HEIGHT -fps $FPS -b $BITRATE -n -g $KEYFRAMERATE -pf high -o - | $WBC_PATH/tx -p $PORT -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH $NIC

#killall raspivid
#killall tx
