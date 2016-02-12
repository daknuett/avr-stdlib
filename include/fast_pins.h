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

/* to provide a faster pin access use these macros to convert the pin by number to a pin by port.  */
#include<avr/io.h>

#if defined(__DEV_M168_)

#define PORTOF_1 PORTC
#define PORTOF_2 PORTD
#define PORTOF_3 PORTD
#define PORTOF_4 PORTD
#define PORTOF_5 PORTD
#define PORTOF_6 PORTD
#define PORTOF_9 PORTB
#define PORTOF_10 PORTB
#define PORTOF_11 PORTD 
#define PORTOF_12 PORTD
#define PORTOF_13 PORTD
#define PORTOF_14 PORTB
#define PORTOF_15 PORTB
#define PORTOF_16 PORTB
#define PORTOF_17 PORTB
#define PORTOF_18 PORTB
#define PORTOF_19 PORTB
#define PORTOF_23 PORTC
#define PORTOF_24 PORTC
#define PORTOF_25 PORTC
#define PORTOF_26 PORTC
#define PORTOF_27 PORTC
#define PORTOF_28 PORTC

#define DDROF_1 DDRC
#define DDROF_2 DDRD
#define DDROF_3 DDRD
#define DDROF_4 DDRD
#define DDROF_5 DDRD
#define DDROF_6 DDRD
#define DDROF_9 DDRB
#define DDROF_10 DDRB
#define DDROF_11 DDRD 
#define DDROF_12 DDRD
#define DDROF_13 DDRD
#define DDROF_14 DDRB
#define DDROF_15 DDRB
#define DDROF_16 DDRB
#define DDROF_17 DDRB
#define DDROF_18 DDRB
#define DDROF_19 DDRB
#define DDROF_23 DDRC
#define DDROF_24 DDRC
#define DDROF_25 DDRC
#define DDROF_26 DDRC
#define DDROF_27 DDRC
#define DDROF_28 DDRC



#define PINOF_1 PC6
#define PINOF_2 PD0
#define PINOF_3 PD1
#define PINOF_4 PD2
#define PINOF_5 PD3
#define PINOF_6 PD4
#define PINOF_9 PB6
#define PINOF_10 PB7
#define PINOF_11 PD5
#define PINOF_12 PD6
#define PINOF_13 PD7
#define PINOF_14 PB0
#define PINOF_15 PB1
#define PINOF_16 PB2
#define PINOF_17 PB3
#define PINOF_18 PB4
#define PINOF_19 PB5
#define PINOF_23 PC0
#define PINOF_24 PC1
#define PINOF_25 PC2
#define PINOF_26 PC3
#define PINOF_27 PC4
#define PINOF_28 PC5


#elif defined(__DEV_M8_)
#define PORTOF_1 PORTC
#define PORTOF_2 PORTD
#define PORTOF_3 PORTD
#define PORTOF_4 PORTD
#define PORTOF_5 PORTD
#define PORTOF_6 PORTD
#define PORTOF_9 PORTB
#define PORTOF_10 PORTB
#define PORTOF_11 PORTD 
#define PORTOF_12 PORTD
#define PORTOF_13 PORTD
#define PORTOF_14 PORTB
#define PORTOF_15 PORTB
#define PORTOF_16 PORTB
#define PORTOF_17 PORTB
#define PORTOF_18 PORTB
#define PORTOF_19 PORTB
#define PORTOF_23 PORTC
#define PORTOF_24 PORTC
#define PORTOF_25 PORTC
#define PORTOF_26 PORTC
#define PORTOF_27 PORTC
#define PORTOF_28 PORTC

#define DDROF_1 DDRC
#define DDROF_2 DDRD
#define DDROF_3 DDRD
#define DDROF_4 DDRD
#define DDROF_5 DDRD
#define DDROF_6 DDRD
#define DDROF_9 DDRB
#define DDROF_10 DDRB
#define DDROF_11 DDRD 
#define DDROF_12 DDRD
#define DDROF_13 DDRD
#define DDROF_14 DDRB
#define DDROF_15 DDRB
#define DDROF_16 DDRB
#define DDROF_17 DDRB
#define DDROF_18 DDRB
#define DDROF_19 DDRB
#define DDROF_23 DDRC
#define DDROF_24 DDRC
#define DDROF_25 DDRC
#define DDROF_26 DDRC
#define DDROF_27 DDRC
#define DDROF_28 DDRC



#define PINOF_1 PC6
#define PINOF_2 PD0
#define PINOF_3 PD1
#define PINOF_4 PD2
#define PINOF_5 PD3
#define PINOF_6 PD4
#define PINOF_9 PB6
#define PINOF_10 PB7
#define PINOF_11 PD5
#define PINOF_12 PD6
#define PINOF_13 PD7
#define PINOF_14 PB0
#define PINOF_15 PB1
#define PINOF_16 PB2
#define PINOF_17 PB3
#define PINOF_18 PB4
#define PINOF_19 PB5
#define PINOF_23 PC0
#define PINOF_24 PC1
#define PINOF_25 PC2
#define PINOF_26 PC3
#define PINOF_27 PC4
#define PINOF_28 PC5


#else
#error "no DEVICE defined"
#endif
