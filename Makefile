CC=avr-gcc
CFLAG=  -mmcu=atmega168 -O -o  

LIBDIR = ./lib

m168_LIBDIR= $(LIBDIR)/m168

m8_LIBDIR= $(LIBDIR)/m8

m168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o

m8_LIBS= $(m8_LIBDIR)/digital.o $(m8_LIBDIR)/analog.o

LIBS= $(LIBDIR)/pins.o

blink_test: libs
	$(CC) $(CFLAG) blinktest.elf $(LIBS) $(m168_LIBS)  blinktest.c

blink_testi:blink_test
	avrdude -p 'm168' -c avrispmkii  -U flash:w:blinktest.elf:a	

libs:
	cd lib; make
asm_write_port:
	$(CC) $(CFLAG) write_port.elf write_port.S
asm_write_porti:asm_write_port
	avrdude -p 'm168' -c avrispmkii  -U flash:w:write_port.elf:a

blink_test_m8: libs
	$(CC) $(CFLAG) blinktest_m8.elf $(LIBS) $(m8_LIBS)  blinktest_m8.c

blink_test_m8i:blink_test
	avrdude -p 'm8' -c avrispmkii  -U flash:w:blinktest_m8.elf:a	
