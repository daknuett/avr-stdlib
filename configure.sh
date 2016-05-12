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

printf 'm168_CFLAG = -std=gnu99 -I $(INCDIR) -mmcu=atmega168 -O -o  \nm8_CFLAG = -std=gnu99 -I $(INCDIR) -mmcu=atmega8 -O -o  \n \n \nm168_LIBDIR= $(std_LIBDIR)/m168\n \nm8_LIBDIR= $(std_LIBDIR)/m8\n \nm168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o $(m168_LIBDIR)/pins.o\n \nm8_LIBS= $(m8_LIBDIR)/digital.o $(m8_LIBDIR)/analog.o $(m8_LIBDIR)/pins.o\n \nm168_USART= $(m168_LIBDIR)/usart.o \nm8_USART= $(m8_LIBDIR)/usart.o\n \nm8_USART_IO= $(m8_LIBDIR)/usart_io.o \nm168_USART_IO= $(m168_LIBDIR)/usart_io.o\nextra_LIBDIR = $(std_LIBDIR)/extra\n ' > config/Makefile.inc

printf 'extra_ONEWIRE = $(extra_LIBDIR)/one_wire.o\nm168_LCD = $(m168_LIBDIR)/lcd.o\nm8_LCD = $(m8_LIBDIR)/lcd.o\nm168_LCD_IO = $(m168_LIBDIR)/lcd_io.o\nm8_LCD_IO = $(m8_LIBDIR)/lcd_io.o\n' >> config/Makefile.inc

printf 'extra_WAIT = $(extra_LIBDIR)/wait.o \nextra_BL3_MOTOR = $(extra_LIBDIR)/brushless3.o\n' >> config/Makefile.inc

function use_m168()
{
	echo "using m168"
	printf 'LIBDIR = $(m168_LIBDIR)\nCFLAG = $(m168_CFLAG)\nLIBS = $(m168_LIBS)\nUSART = $(m168_USART)\nUSART_IO = $(m168_USART_IO)\nONEWIRE = $(extra_ONEWIRE)\nLCD = $(m168_LCD)\nLCD_IO = $(m168_LCD_IO)\n' >> config/Makefile.inc
	printf "DEVICE = m168\n" >> config/Makefile.inc
	printf "MMCU = atmega168\n" >> config/device
	printf "#define __DEV_M168_\n" >> config/config.h
}
function use_m8()
{
	echo "using m8"
	printf 'LIBDIR = $(m8_LIBDIR)\nCFLAG = $(m8_CFLAG)\nLIBS = $(m8_LIBS)\nUSART = $(m8_USART)\nUSART_IO = $(m8_USART_IO)\nONEWIRE = $(extra_ONEWIRE)\nLCD = $(m8_LCD)\nLCD_IO = $(m18_LCD_IO)\n' >> config/Makefile.inc
	printf "DEVICE = m8\n" >> config/Makefile.inc
	printf "MMCU = atmega8\n" >> config/device
	printf "#define __DEV_M8_\n" >> config/config.h
}

printf "use select device:\nm8 \tatmega8\nm168\tatmega168\ndevice:  "
read dev
case $dev in
	"m8") use_m8 ;;
	"m168") use_m168 ;;

esac


printf "always link to usart and usart_io? "
read link_usart
if [[ "$link_usart" == "y" ]]
then
	printf 'LIBS += $(USART) $(USART_IO)\n' >> config/Makefile.inc
fi
printf "always link to onewire? "
read link_onewire
# we need this anyways...
one_wire_port="PORTB"
one_wire_pin="PINB"
one_wire_ddr="DDRB"
one_wire_pinno="PB0"

if [[ "$link_onewire" == "y" ]]
then
	printf 'LIBS += $(ONEWIRE)\n' >> config/Makefile.inc
	printf "Enter ONE_WIRE_PORT (PORTB|PORTC|PORTD)"
	read one_wire_port
	printf "Enter ONE_WIRE_PIN (PINB|PINC|PIND)"
	read one_wire_pin
	printf "Enter ONE_WIRE_DDR (DDRB|DDRC|DDRD)"
	read one_wire_ddr
	printf "Enter ONE_WIRE_PINNO (PC0|PC1|PB0|...)"
	read one_wire_pinno


fi

printf "#ifndef __ONE_WIRE_CONFIG_H_\n#define __ONE_WIRE_CONFIG_H_\n#define ONE_WIRE_PORT $one_wire_port\n #define ONE_WIRE_PIN $one_wire_pin \n#define ONE_WIRE_DDR $one_wire_ddr\n#define ONE_WIRE_PINNO $one_wire_pinno\n#endif\n" >> config/config.h


printf "always link to lcd and lcd_io? "
read link_lcd
if [[ "$link_lcd" == "y" ]]
then
	printf 'LIBS += $(LCD) $(LCD_IO)\n' >> config/Makefile.inc
fi

printf "link to wait? "
read link_wait
if [[ "$link_wait" == "y" ]]
then
	printf 'LIBS += $(extra_WAIT)\n' >> config/Makefile.inc
fi

printf "link to bl3_motor? "
read link_bl3_motor
if [[ "$link_bl3_motor" == "y" ]]
then
	printf 'LIBS += $(extra_BL3_MOTOR)\n' >> config/Makefile.inc
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

printf "F_CPU? "
read fcpu
printf "#define F_CPU $fcpu\n" >> config/config.h
printf "\n\n\n\n"
echo "finishing config/config.h and config/usart_config.h"
printf "#endif\n" >> config/config.h
printf "#endif\n" >> config/usart_config.h
echo "configure done"
