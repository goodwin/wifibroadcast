#!/bin/bash

#howto use: add a button between SHUTDOWN_PIN and +3.3V and a 10k resistor between SHUTDOWNPIN and GND. If everything is right then a button press will shut down the system

SHUTDOWN_PIN=25


echo $SHUTDOWN_PIN > /sys/class/gpio/export

while :
do
	PINV=`cat /sys/class/gpio/gpio$SHUTDOWN_PIN/value`
	if [ $PINV -eq "1" ]; then
		echo "Shutdown"
		sudo halt
	fi

	sleep 1
done

