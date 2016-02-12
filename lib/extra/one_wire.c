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

/* provide a polled onewire library */

#define pin_low() ONE_WIRE_PORT &= ~( 1 << ONE_WIRE_PINNO)
#define pin_high() ONE_WIRE_PORT |= ( 1 << ONE_WIRE_PINNO)
#define pin_output() ONE_WIRE_DDR |= ( 1 << ONE_WIRE_PINNO)
#define pin_input() ONE_WIRE_DDR &= ~( 1 << ONE_WIRE_PINNO)

#define pin_read() ONE_WIRE_PIN & ( 1 << ONE_WIRE_PINNO)


#include<util/atomic.h>
#include<util/delay.h>

char one_wire_reset(void)
{
	pin_input();	
	char retrys = 0xff, res;
	// wait for BUS to be unused
	while(retrys-- && !pin_read());
	// BUS cannot be used
	if(!pin_read())
	{
		return -1;
	}

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		pin_output();
		pin_low();
		_delay_us(480);
		pin_input();
		_delay_us(70);
		res = !pin_read();
	}
	_delay_us(410);
	return res;	
}

void one_wire_write_bit(char bit)
{
	pin_output();
	if(bit & 1)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			pin_low();
			_delay_us(10);
			pin_high();
		}
		_delay_us(55);
	}
	else
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			pin_low();
			_delay_us(60);
			pin_high();
		}
		_delay_us(5);
	}
}

char one_wire_read_bit(void)
{
	char res;
	pin_output();
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		pin_low();
		_delay_us(3);
		pin_input();
		_delay_us(10);
		res = pin_read() != 0;
		_delay_us(53);

	}
	return res;
}

void one_wire_putb(char _c)
{
	char i;
	for(i = 0;i < 8; i++)
	{
		one_wire_write_bit(_c >> i);
	}
}

char one_wire_getb(void)
{
	char res = 0;
	char i;
	for (i = 0; i < 8; i++)
	{
		res |= one_wire_read_bit() << i;
	}
	return res;
}

