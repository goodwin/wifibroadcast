#!/bin/bash


#adapt these to your needs
NIC="wlan0"
PORT=1
SAVE_PATH="/media/usb0/telemetry"

BLOCK_SIZE=8
FECS=4
PACKET_LENGTH=1024

WBC_PATH="/home/pi/wifibroadcast"
FRSKY_OMX_OSD_PATH="/home/pi/frsky_omx_osd"

sleep 10

# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi


if [ -d "$SAVE_PATH" ]; then
	echo "Starting osd with recording"
	$WBC_PATH/rx -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH -p $PORT $NIC | tee $SAVE_PATH/`ls $SAVE_PATH | wc -l`.frsky | $FRSKY_OMX_OSD_PATH/frsky_omx_osd /opt/vc/src/hello_pi/hello_font/
else
	echo "Starting osd without recording"
	$WBC_PATH/rx -b $BLOCK_SIZE -r $FECS -f $PACKET_LENGTH -p $PORT $NIC | $FRSKY_OMX_OSD_PATH/frsky_omx_osd $FRSKY_OMX_OSD_PATH
fi


