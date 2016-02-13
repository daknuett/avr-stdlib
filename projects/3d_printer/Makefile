CC=avr-gcc
STD_DIR = ../..
INCDIR= $(STD_DIR)/include
std_LIBDIR = $(STD_DIR)/lib

include $(STD_DIR)/config/Makefile.inc

%.elf: %.c libs
	$(CC) $(CFLAG) $@ $(LIBS) $<
i%.elf: %.elf
	avrdude -p '$(DEVICE)' -c avrispmkii  -U flash:w:$<:a

clean:
	cd $(STD_DIR)/lib/ && make clean && cd ..

libs:
	cd $(STD_DIR)/lib && make -s || make


