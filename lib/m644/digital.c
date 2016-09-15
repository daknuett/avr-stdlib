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

void pin_mode(unsigned char pin, unsigned char mode)
{
	if(pin < 9)
	{
		pin -= 1;
		DDRB &= (0xff ^ (1 << pin));
		DDRB |=  (1 << pin);
	}
	if(pin > 13 && pin < 22)
	{
		pin -= 14;
		DDRD &= (0xff ^ (1 << pin));
		DDRD |=  (1 << pin);
		
	}
	if(pin > 21 && pin < 30)
	{
		pin -= 22;
		DDRC &= (0xff ^ (1 << pin));
		DDRC |=  (1 << pin);
		
	}
	if(pin > 32 && pin < 41)
	{
		pin -= 33;
		DDRA &= (0xff ^ (1 << pin));
		DDRA |=  (1 << pin);
		
	}
}

void write_pin(unsigned char pin, unsigned char value)
{
	pin_mode(pin,PIN_OUT);

	if(pin < 9)
	{
		pin -= 1;
		PORTB &= (0xff ^ (1 << pin));
		PORTB |=  (1 << pin);
	}
	if(pin > 13 && pin < 22)
	{
		pin -= 14;
		PORTD &= (0xff ^ (1 << pin));
		PORTD |=  (1 << pin);
		
	}
	if(pin > 21 && pin < 30)
	{
		pin -= 22;
		PORTC &= (0xff ^ (1 << pin));
		PORTC |=  (1 << pin);
		
	}
	if(pin > 32 && pin < 41)
	{
		pin -= 33;
		PORTA &= (0xff ^ (1 << pin));
		PORTA |=  (1 << pin);
		
	}
}
unsigned char read_pin(unsigned char pin)
{
	pin_mode(pin,PIN_IN);
	if(pin < 9)
	{
		pin -= 1;
		return PORTB & (1 << pin);
	}
	if(pin > 13 && pin < 22)
	{
		pin -= 14;
		return PORTD & (1 << pin);
		
	}
	if(pin > 21 && pin < 30)
	{
		pin -= 22;
		return PORTC & (1 << pin);
		
	}
	if(pin > 32 && pin < 41)
	{
		pin -= 33;
		return PORTA & (1 << pin);
		
	}
}
