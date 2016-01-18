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

/* one_wire.c: provide a soft onewire library */

#include<avr/io.h>
#include<util/atomic.h>
#define __DEV_M168_
#include<pins.h>
#ifndef F_CPU
#define F_CPU 1000000
#endif
#include<util/delay.h>

#define ONE_WIRE_NO_INT
#define ONE_WIRE_SINGLE_SLAVE

#if defined( ONE_WIRE_NO_INT)
char one_wire_pin;
void one_wire_begin(char pin)
{
	pin_mode(pin,PIN_OUT);
	write_pin(pin,HIGH);
	one_wire_pin = pin;
#if defined( ONE_WIRE_SINGLE_SLAVE)
#elif defined ( ONE_WIRE_MULTI_SLAVE)
#else
#error " no valid ONE_WIRE configuration defined"
#endif
}

char one_wire_reset(void)
{
	// every bit has to be atomic
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		// start with reset signal
		write_pin(one_wire_pin,LOW);
		_delay_us(481);
		write_pin(one_wire_pin,HIGH);
		// reset done
		// wait for presence signal
		unsigned char timeout = 0;
		while(read_pin(one_wire_pin) != 0)
		{
			timeout ++;
			_delay_us(1);
			if(timeout >= 60)
			{
				return -1;
			}
		}
		timeout = 0;
		while(read_pin(one_wire_pin) == 0)
		{
			timeout++;
			_delay_us(1);
		}
		if(timeout < 40)
		{
			return -1;
		}
		return 0;
	}
}

void write_bit(char bit)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		write_pin(one_wire_pin,LOW);
		if(bit == 0)
		{
			_delay_us(60);
			write_pin(one_wire_pin,HIGH);
			_delay_us(10);
		}
		else
		{
			_delay_us(6);
			write_pin(one_wire_pin,HIGH);
			_delay_us(64);
		}

	}
}

char read_bit(void)
{
	char res;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		write_pin(one_wire_pin,LOW);
		_delay_us(6);
		write_pin(one_wire_pin,HIGH);
		_delay_us(10);
		res = read_pin(one_wire_pin);
		_delay_us(55);
	}
	return res != 0;

}

char read_byte(void)
{
	char i;
	char res = 0;
	for(i=0;i<8;i++)
	{
		res |= read_bit() << i;
	}
	return res;
}
void write_byte(char __b)
{
	char i;
	for(i = 0; i < 8; i++)
	{
		write_bit( __b & ( 1<< i));
	}
}

#elif defined(ONE_WIRE_INT)
#error "not yet implemented"
#else
#error "no valid ONE_WIRE_MODE defined"



#endif

