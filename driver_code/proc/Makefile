obj-m=proc_rw.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
