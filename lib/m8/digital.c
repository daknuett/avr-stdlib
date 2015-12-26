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

#include<avr/io.h>
#include"pin_defs.h"
/* operate on the pins of an atmega8
 	just like atmega168
 */


void pin_mode(unsigned char pin, unsigned char mode)
{
	/*
	   raw mode: the pin is just the number from pin1
	 */

	if(pin < 2)
	{
		// PORTC, pin1
		// PC6

		// set to 0 first
		DDRC &= ~0b00100000;
		// set mode
		DDRC |= (mode << 5);
		return;
	}
	if(pin < 7)
	{
		// PD0 => PD4
		// set to 0
		DDRD &= ~( 1 <<  (pin - 2));
		DDRD |= ( mode <<  (pin - 2));
		return;
	}
	if( pin >= 7 && pin < 9 )
	{
		// Vcc and GND
		return;
	}
	if( pin < 10 )
	{
		// PB6 and PB7
		DDRB &= ~(1 << ((pin - 9) + 6));
		DDRB |= (mode << ((pin - 9) + 6));
		return;
	}
	if( pin < 14 )
	{
		// PD5 => PD7
		DDRD &= ~(1 << ((pin - 11) + 5));
		DDRD |= (mode << ((pin - 11) + 5));
		return ;
	}
	if( pin < 20 )
	{
		// PB0 => PB5
		DDRB &= ~(1 << (( pin - 14)));
		DDRB |= (mode << (( pin - 14)));
		return;
	}
	if( pin >= 20 && pin < 23)
	{
		// Aref, GND, AVcc
		return;
	}
	if( pin < 29)
	{
		// PC0 => PC5
		DDRC &= ~(1 << (( pin - 23)));
		DDRC |= (mode << (( pin - 23)));
	}
	return;
}


void write_pin(unsigned char pin, unsigned char value)
{
	pin_mode(pin,PIN_OUT);
	if(pin < 2)
	{
		// PORTC, pin1
		// PC6

		// set to 0 first
		PORTC &= ~0b00100000;
		// set value
		PORTC |= (value << 5);
		return;
	}
	if(pin < 7)
	{
		// PD0 => PD4
		// set to 0
		PORTD &= ~( 1 <<  (pin - 2));
		PORTD |= ( value <<  (pin - 2));
		return;
	}
	if( pin >= 7 && pin < 9 )
	{
		// Vcc and GND
		return;
	}
	if( pin < 11 )
	{
		// PB6 and PB7
		PORTB &= ~(1 << ((pin - 9) + 6));
		PORTB |= (value << ((pin - 9) + 6));
		return;
	}
	if( pin < 14 )
	{
		// PD5 => PD7
		PORTD &= ~(1 << ((pin - 11) + 5));
		PORTD |= (value << ((pin - 11) + 5));
		return ;
	}
	if( pin < 20 )
	{
		// PB0 => PB5
		PORTB &= ~(1 << (( pin - 14)));
		PORTB |= (value << (( pin - 14)));
		return;
	}
	if( pin >= 20 && pin < 23)
	{
		// Aref, GND, AVcc
		return;
	}
	if( pin < 29)
	{
		// PC0 => PC5
		PORTC &= ~(1 << (( pin - 23)));
		PORTC |= (value << (( pin - 23)));
	}
	return;

}

unsigned char read_pin(unsigned char pin)
{
	pin_mode(pin,PIN_IN);
	if(pin < 2)
	{
		// PORTC, pin1
		// PC6

		return PINC & (1 << 5);
	}
	if(pin < 7)
	{
		// PD0 => PD4
		return PIND & ( 1 <<  (pin - 2));
	}
	if( pin >= 7 && pin < 9 )
	{
		// Vcc and GND
		return 0;
	}
	if( pin < 11 )
	{
		// PB6 and PB7
		return PINB & (1 << ((pin - 9) + 6));
	}
	if( pin < 14 )
	{
		// PD5 => PD7
		return PIND & (1 << ((pin - 11) + 5));
	}
	if( pin < 20 )
	{
		// PB0 => PB5
		return PINB & (1 << (( pin - 14)));
	}
	if( pin >= 20 && pin < 23)
	{
		// Aref, GND, AVcc
		return 0;
	}
	if( pin < 29)
	{
		// PC0 => PC5
		return PINC & (1 << (( pin - 23)));
	}
	return 0;

}

