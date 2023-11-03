obj-m += modxom.o


all:
	mkdir -p $(PWD)/build
	ln -fs $(PWD)/modxom.c $(PWD)/build/modxom.c
	ln -fs $(PWD)/modxom.h $(PWD)/build/modxom.h
	ln -fs $(PWD)/Makefile $(PWD)/build/Makefile
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/build modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/build clean
	rm -r $(PWD)/build