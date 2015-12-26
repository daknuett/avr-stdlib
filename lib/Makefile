CC=avr-gcc
CFLAG=  -mmcu=atmega168 -O -o
CLFLAG= -c $(CFLAG)

HFLAG= -mmcu=atmega168

all: pins

pins:devices
	$(CC) $(CLFLAG) pins.o pins.c

	
devices:lib_m168 lib_m8

lib_m168:                             
	cd m168 && make && cd ..
lib_m8:
	cd m8 && make && cd ..
