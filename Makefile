CC=avr-gcc
CFLAG=  -mmcu=atmega168 -O -o  

LIBDIR = ./lib

m168_LIBDIR= $(LIBDIR)/m168

m168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o

LIBS= $(LIBDIR)/pins.o

blink_test: libs
	$(CC) $(CFLAG) blinktest.elf $(LIBS) $(m168_LIBS)  blinktest.c

blink_testi:blink_test
	avrdude -p 'm168' -c avrispmkii  -U flash:w:blinktest.elf:a	

libs:
	cd lib; make

