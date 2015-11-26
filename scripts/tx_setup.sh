#!/bin/bash
# tx script

#adapt these to your needs
NIC="wlan1"
CHANNEL="6"

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

echo "updating wifi ($NIC, $CHANNEL)"
ifconfig $NIC down
iw dev $NIC set monitor otherbss fcsfail
ifconfig $NIC up
iwconfig $NIC channel $CHANNEL

echo "Hypothetically, I would start: tx for $NIC"
echo "raspivid -ih -t 0 -w $WIDTH -h $HEIGHT -fps $FPS -b $BITRATE -n -g $KEYFRAMERATE -pf high -o - | $WBC_PATH/tx -p $PORT -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH $NIC"

