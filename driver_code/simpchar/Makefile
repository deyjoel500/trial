obj-m=simpchar.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	rm -rf *ko *o
