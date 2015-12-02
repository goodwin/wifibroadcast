# help722 - wifi broadcast helper
designed to be a one-stop util to tune your TL-WN722N (or other AR9271 based cards)
* patch regulatory settings (always max transmit)
* choose highest rate 30db
* disable/enabled patched firmware

# build
* I prefer to cross compile on my Ubuntu machine and scp the driver over
* clone my omnihook lib
* create symbolic links to omnihook_linux_arm.{c,h}
```
$ ln -s ~/repos/lwerdna/omnihook/omni_linux_arm.c omnihook.c
$ ln -s ~/repos/lwerdna/omnihook/omni_linux_arm.h omnihook.h
```
* set your cross compiler, kernel dir, and compile
```
$ echo $CCOMPILER
/home/a/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
$ ARCH=arm CROSS_COMPILE=$CCOMPILER KERNEL_DIR=~/Downloads/linux/ make
...
```

# notes
## driver hierarchy
```
ath9k_htc
  cf80211
  mac80211
  ath9k_common
    ath
    ath9k_hw
```
## firmware registers
* in 16-byte offsets, 9271 specific start at 0x8000
* see reg.h for full list
* call into ath9k_regread()/ath9k_regwrite() from htc_drv_init.c
## carrier sense disable notes from ath9k-devel mailing list
* see ath9k/reg.h for definitions, call 
* reg AR_DIAG_SW: Set AR_DIAG_IGNORE_VIRT_CS / AR_DIAG_FORCE_CH_IDLE_HIGH to disable virtual carrier sensing
* reg AR_DIAG_FORCE_RX_CLEAR to disable physical carrier sensing.
- reg AR_D_GBL_IFS_SIFS: SIFS timeout.
- reg AR_D_GBL_IFS_SLOT: SLOT timeout.
- reg AR_DLCL_IFS: inter-frame spacing, minimum and maximum contention window, and AIFSN values
- Set force_agc_clear (bit 28 of reg 0xa360).
