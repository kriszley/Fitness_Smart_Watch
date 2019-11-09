export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
obj-m += fpga_dev_driver.o

all:
	make -C ../../linux/source M=$(PWD) modules

clean:
	make -C ../../linux/source M=$(PWD) clean

