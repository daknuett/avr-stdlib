CC=avr-gcc
CFLAG=  -mmcu=atmega168 -O -o  

LIBDIR = ./lib

m168_LIBDIR= $(LIBDIR)/m168

m8_LIBDIR= $(LIBDIR)/m8

m168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o $(m168_LIBDIR)/pins.o

m8_LIBS= $(m8_LIBDIR)/digital.o $(m8_LIBDIR)/analog.o $(m8_LIBDIR)/pins.o

m168_USART= $(m168_LIBDIR)/usart.o
m8_USART= $(m8_LIBDIR)/usart.o


blink_test: libs
	$(CC) $(CFLAG) blinktest.elf  $(m168_LIBS)  blinktest.c

blink_testi:blink_test
	avrdude -p 'm168' -c avrispmkii  -U flash:w:blinktest.elf:a	

libs:
	cd lib; make -s || make

blink_test_m8: libs
	$(CC) $(CFLAG) blinktest_m8.elf  $(m8_LIBS)  blinktest_m8.c

blink_test_m8i:blink_test
	avrdude -p 'm8' -c avrispmkii  -U flash:w:blinktest_m8.elf:a	

usart_test: libs
	$(CC) $(CFLAG) usart_test.elf $(m168_USART)  $(m168_LIBS) usart_test.c
usart_testi:usart_test
	avrdude -p 'm168' -c avrispmkii  -U flash:w:usart_test.elf:a
