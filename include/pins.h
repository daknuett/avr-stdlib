/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.
 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.
 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/


#ifndef __pins_h_
#define __pins_h_

#include<avr/io.h>

/* routines to set pins */

#define PIN_OUT 1
#define PIN_IN	0

extern void pin_mode(unsigned char pin, unsigned char mode);

#define HIGH	1
#define LOW	0

extern void write_pin(unsigned char pin, unsigned char value);

#define STD	1
#define	POLL	2
#define DOUBLE_POLL	3

extern unsigned char read_pin(unsigned char pin);

extern unsigned char get_pin(unsigned char pin, unsigned char mode);

extern void analog_write(unsigned char pin, unsigned char value);

extern int analog_read(unsigned char pin);

#ifdef __DEV_M168_
#include"pins_m168.h"
#else
#error "no valid device ( like __DEV_M168_ ) defined!"
#endif



#endif


