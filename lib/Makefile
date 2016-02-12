CC=avr-gcc
INCDIR=`pwd`/../include
CFLAG= -I $(INCDIR) -O -o
CLFLAG= -c $(CFLAG)


all: pins  usart_m168 usart_m8 lcd_m168 lcd_m8 lib_extra

pins:devices pins_m8 pins_m168
	echo "compiled">/dev/null


pins_m168:
	$(CC) -mmcu=atmega168  $(CLFLAG) pins.o pins.c &&\
	mv pins.o m168/pins.o
pins_m8:
	$(CC) -mmcu=atmega8  $(CLFLAG) pins.o pins.c && \
	mv pins.o m8/pins.o

usart_m168:
	$(CC) -mmcu=atmega168 $(CLFLAG) usart_io.o usart_io.c &&\
	mv usart_io.o m168/usart_io.o
usart_m8:
	$(CC) -mmcu=atmega8 $(CLFLAG) usart_io.o usart_io.c &&\
	mv usart_io.o m8/usart_io.o
lcd_m168:
	$(CC) -mmcu=atmega168 $(CLFLAG) lcd_io.o lcd_io.c &&\
	mv lcd_io.o m168/lcd_io.o
lcd_m8:
	$(CC) -mmcu=atmega8 $(CLFLAG) lcd_io.o lcd_io.c &&\
	mv lcd_io.o m8/lcd_io.o

	
devices:lib_m168 lib_m8

lib_m168:                             
	cd m168 && make && cd ..
lib_m8:
	cd m8 && make && cd ..

clean: 
	cd m8 && make clean && cd .. &&\
	cd m168 && make clean && cd .. &&\
	cd extra && make clean && cd ..
lib_extra:
	cd extra && make && cd ..

disclaimer:
	printf "/*\n This program is free software: you can redistribute it and/or modify\n it under the terms of the GNU General Public License as published by\n the Free Software Foundation, either version 3 of the License, or\n (at your option) any later version.\n\n This program is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY; without even the implied warranty of\n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n GNU General Public License for more details.\n\n You should have received a copy of the GNU General Public License\n along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\n Dieses Programm ist Freie Software: Sie können es unter den Bedingungen\n der GNU General Public License, wie von der Free Software Foundation,\n Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren\n veröffentlichten Version, weiterverbreiten und/oder modifizieren.\n Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber\n OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite\n Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.\n Siehe die GNU General Public License für weitere Details.\n Sie sollten eine Kopie der GNU General Public License zusammen mit diesem\n Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.\n*/"
