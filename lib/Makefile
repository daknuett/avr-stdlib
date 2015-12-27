CC=avr-gcc
CFLAG=  -O -o
CLFLAG= -c $(CFLAG)


all: pins 

pins:devices pins_m8 pins_m168
	echo "compiled">/dev/null

pins_m168:
	$(CC) -mmcu=atmega168  $(CLFLAG) pins.o pins.c &&\
	mv pins.o m168/pins.o
pins_m8:
	$(CC) -mmcu=atmega8  $(CLFLAG) pins.o pins.c && \
	mv pins.o m8/pins.o

	
devices:lib_m168 lib_m8

lib_m168:                             
	cd m168 && make && cd ..
lib_m8:
	cd m8 && make && cd ..


