#!/bin/bash
# rx script

#wait a bit until the wifi cards are ready
sleep 2

#adapt these to your needs
CHANNEL="1"
NICS=`ls /sys/class/net | grep wlan`
SAVE_PATH="/media/usb0/video"

WBC_PATH="/home/a/repos/lwerdna/wifibroadcast"
DISPLAY_PROGRAM="/opt/vc/src/hello_pi/hello_video/hello_video.bin" 


##################################
#change these only if you know what you are doing (and remember to change them on both sides)
BLOCK_SIZE=8
FECS=4
PACKET_LENGTH=1024
PORT=0
##################################

function prepare_nic {
	echo "updating wifi ($1, $2)"
	ifconfig $1 down
	iw dev $1 set monitor otherbss fcsfail
	ifconfig $1 up
	iwconfig $1 channel $2
}

################################# SCRIPT START #######################


# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi


#prepare NICS
for NIC in $NICS
do
	prepare_nic $NIC $CHANNEL
done

echo "Starting with recording"
echo $WBC_PATH/rx -p $PORT -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH $NICS
$WBC_PATH/rx -p $PORT -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH $NICS > ./save.rawvid
	
#if [ -d "$SAVE_PATH" ]; then
#	echo "Starting with recording"
#	FILE_NAME=$SAVE_PATH/`ls $SAVE_PATH | wc -l`.rawvid
#	$WBC_PATH/rx -p $PORT -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH $NICS | tee $FILE_NAME | $DISPLAY_PROGRAM
#else
#	echo "Starting without recording"
#	$WBC_PATH/rx -p $PORT -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH $NICS | $DISPLAY_PROGRAM
#fi

