tinkering with befinitiv's wifibroadcast project

(send video thru 802.11 STA via packet injection, for RC FPV)

https://bitbucket.org/befi/wifibroadcast
https://befinitiv.wordpress.com/

##How?
* raspbian comes with a utility that reads video: raspivid
* raspivid's output gets piped into the tx portion of this project

##Steps
* install libpcap (eg Ubuntu: `sudo apt-get install libpcap-dev`)
* compile `make`
* run it `./tx` or `./rx` (see ./scripts/tx.sh for example)
** ifconfig wlan0 down
** iw dev wlan0 set monitor otherbss fcsfail
** ifconfig wlan0 up
** iwconfig wlan0 channel 11
* setup auto start (see ./scripts/systemd)

##Other Notes
###mounting partitions within raspi images
* fdisk -l TX_2015-09-24-raspbian-jessie.img (should show FAT boot and Linux/ext4 system)
* example:
```
                                              Device Boot      Start         End      Blocks   Id  System
/home/a/Downloads/TX_2015-09-24-raspbian-jessie.img1            8192      122879       57344    c  W95 FAT32 (LBA)
/home/a/Downloads/TX_2015-09-24-raspbian-jessie.img2          122880     8447999     4162560   83  Linux
```
* Start/End/Blocks are in 512-byte units, so multiply to get file offset (8192*512 and 122880*512)
* mount -v -o offset=4194304 -t vfat whatever.img /mnt/raspi_boot
* mount -v -o offset=62914560 -t ext4 whatever.img /mnt/raspi_system
