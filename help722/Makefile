ifneq ($(KERNELRELEASE),)
# kbuild part of makefile

# -O0 can actually cause error in include/linux/rcupdate.h:917 size of array blah blah negative
#ccflags-y := -munaligned-access

# we specify obj-m, the m meaning "build as a module" and list the name of resulting object
# (which gets changed from .o -> .ko)
obj-m  := help722.o 
# now we name <module>-objs to list the modules involved to make <module>
help722-objs := main.o omnihook.o
else
 # Normal Makefile

all: module

module:
	KBUILD_VERBOSE=1 ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) $(MAKE) -C $(KERNEL_DIR) M=`pwd`

clean:
	$(MAKE) -C $(KERNEL_DIR) M=`pwd` clean

endif

