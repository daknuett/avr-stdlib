#!/bin/bash

echo "configure for avr basic libs"
echo "checking for some requirements"

avr-gcc -v || echo "avr-gcc not found. Install avr-gcc!" 

echo "done"
printf "\n\n\n"

echo "configuration:"

echo "building config.h"
printf "#ifndef __CONFIG_H__\n#define __CONFIG_H__\n" > config/config.h 
echo "building usart_config.h"
printf "#ifndef __USART_CONFIG_H__\n#define __USART_CONFIG_H__\n" > config/usart_config.h 

printf "use usart interrupt mode? "
read usart_int_mode
if  [[ "$usart_int_mode" == "y" ]]
then 
	echo "using usart interrupt mode"
	echo "#define USART_INT_MODE" >> config/usart_config.h
	printf "buffersize for ringbuffer ( suggested 50 - 200 )? "
	read bufs
	printf "#define IO_BUF_S " >> config/usart_config.h
	echo $bufs >> config/usart_config.h
else
	echo "using usart poll mode"
	echo "#define USART_POLL_MODE" >> config/usart_config.h
fi

echo "generating config/Makefile.inc"

printf ' m168_CFLAG = -I $(INCDIR) -mmcu=atmega168 -O -o  \n m8_CFLAG =- I $(INCDIR) -mmcu=atmega8 -O -o  \n \n \n m168_LIBDIR= $(std_LIBDIR)/m168\n \n m8_LIBDIR= $(std_LIBDIR)/m8\n \n m168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o $(m168_LIBDIR)/pins.o\n \n m8_LIBS= $(m8_LIBDIR)/digital.o $(m8_LIBDIR)/analog.o $(m8_LIBDIR)/pins.o\n \n m168_USART= $(m168_LIBDIR)/usart.o\n m8_USART= $(m8_LIBDIR)/usart.o\n \n m8_USART_IO= $(m8_LIBDIR)/usart_io.o\n m168_USART_IO= $(m168_LIBDIR)/usart_io.o\n ' > config/Makefile.inc

printf 'm168_ONEWIRE = $(m168_LIBDIR)/one_wire.o\nm8_ONEWIRE = $(m8_LIBDIR)/one_wire.o\nm168_LCD = $(m168_LIBDIR)/lcd.o\nm8_LCD = $(m8_LIBDIR)/lcd.o\nm168_LCD_IO = $(m168_LIBDIR)/lcd_io.o\nm8_LCD_IO = $(m8_LIBDIR)/lcd_io.o\n' >> config/Makefile.inc

printf "use m168? "
read use_m168
if [[ "$use_m168" == "y" ]]
then
	printf 'LIBDIR = $(m168_LIBDIR)\nCFLAG = $(m168_CFLAG)\nLIBS = $(m168_LIBS)\nUSART = $(m168_USART)\nUSART_IO = $(m168_USART_IO)\nONEWIRE = $(m168_ONEWIRE)\nLCD = $(m168_LCD)\nLCD_IO = $(m168_LCD_IO)\n' >> config/Makefile.inc
	printf "DEVICE = m168\n" >> config/Makefile.inc
else 
	echo "using m8"
	printf 'LIBDIR = $(m8_LIBDIR)\nCFLAG = $(m8_CFLAG)\nLIBS = $(m8_LIBS)\nUSART = $(m8_USART)\nUSART_IO = $(m8_USART_IO)\nONEWIRE = $(m8_ONEWIRE)\nLCD = $(m8_LCD)\nLCD_IO = $(m18_LCD_IO)\n' >> config/Makefile.inc
	printf "DEVICE = m8\n" >> config/Makefile.inc
fi

printf "always link to usart and usart_io? "
read link_usart
if [[ "$link_usart" == "y" ]]
then
	printf 'LIBS += $(USART) $(USART_IO)\n' >> config/Makefile.inc
fi
printf "always link to onewire? "
read link_onewire
if [[ "$link_onewire" == "y" ]]
then
	printf 'LIBS += $(ONEWIRE)\n' >> config/Makefile.inc
fi
printf "always link to lcd and lcd_io? "
read link_lcd
if [[ "$link_lcd" == "y" ]]
then
	printf 'LIBS += $(LCD) $(LCD_IO)\n' >> config/Makefile.inc
fi

printf "\n\n\n"
printf "Vref for analog input:\n"
printf "e \t for Aref pin\ni \t for internal 1.1V ref\na \t for Avcc pin\n"
printf "Vref? "
read vref
case $vref in
	e ) echo "Aref"; printf "#define __USE_V_AREF_\n" >> config/config.h ;;
	i ) echo "internal 1.1V"; printf "#define __USE_V_INT_\n" >> config/config.h ;;
	a ) echo "Avcc"; printf "#define __USE_V_AVCC_\n" >> config/config.h ;;
	*) echo "use e|i|a : abort"; exit 1;;
esac
printf "\n\n\n\n"
echo "finishing config/config.h and config/usart_config.h"
printf "#endif\n" >> config/config.h
printf "#endif\n" >> config/usart_config.h
echo "configure done"
