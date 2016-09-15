CC=avr-gcc
INCDIR=`pwd`/../../include
CFLAG= -I $(INCDIR) -std=gnu99 -O -o
CLFLAG= -c $(CFLAG)

include config/project_config

include $(GLOBAL_CONFIG)/device

objects = one_wire.o themp_ds18b20.o wait.o motor.o brushless3.o lcd.o lcd_io.o sd.o spi.o

all: $(objects)
	echo $(objects)
%.o:%.c
	$(CC) -include $(GLOBAL_CONFIG)/config.h -mmcu=$(MMCU) $(CLFLAG) $@ $<
%.s:%.c
	$(CC) -include $(GLOBAL_CONFIG)/config.h -mmcu=$(MMCU) -I $(INCDIR) -std=gnu99 -O -S $<

clean: 
	rm *.o || true


disclaimer:
	printf "/*\n This program is free software: you can redistribute it and/or modify\n it under the terms of the GNU General Public License as published by\n the Free Software Foundation, either version 3 of the License, or\n (at your option) any later version.\n\n This program is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY; without even the implied warranty of\n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n GNU General Public License for more details.\n\n You should have received a copy of the GNU General Public License\n along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\n Dieses Programm ist Freie Software: Sie können es unter den Bedingungen\n der GNU General Public License, wie von der Free Software Foundation,\n Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren\n veröffentlichten Version, weiterverbreiten und/oder modifizieren.\n Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber\n OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite\n Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.\n Siehe die GNU General Public License für weitere Details.\n Sie sollten eine Kopie der GNU General Public License zusammen mit diesem\n Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.\n*/"
