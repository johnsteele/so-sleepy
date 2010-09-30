
ifneq ($(KERNELRELEASE),)
 	obj-m += sleep-mod.o
	sleep-mod-objs := sleep.o

else
	KERNELDIR= /lib/modules/$(shell uname -r)/build
	PWD= $(shell pwd) 

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules	

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers 

endif
 
