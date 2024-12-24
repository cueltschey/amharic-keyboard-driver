obj-m += amharic_keyboard_driver.o

all:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	cp -fv amharic_keyboard_driver.ko /lib/modules/$(shell uname -r)/kernel/drivers/hid/
	depmod -a
	modprobe amharic_keyboard_driver
