# mac80211spy
* hook into mac80211 functions
* print args / stack traces

# build
* clone my omnihook lib
* create symbolic links to omnihook_linux_arm.{c,h}
```
$ ln -s ~/repos/lwerdna/omnihook/omni_linux_arm.c omni_linux_arm.c
$ ln -s ~/repos/lwerdna/omnihook/omni_linux_arm.h omni_linux_arm.h
```
* set your cross compiler, kernel dir, and compile
```
$ echo $CCOMPILER
/home/a/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
$ ARCH=arm CROSS_COMPILE=$CCOMPILER KERNEL_DIR=~/Downloads/linux/ make
...
```

