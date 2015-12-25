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
#ifndef F_CPU
#define F_CPU 1000000ul
#endif

#include<util/delay.h>


#define POLL	2

#define POLL_TIME_PER_STEP	3
#define POLL_STEPS		40
#define POLL_TIME_AFTER		150

#define STD	1

// doppelte werte
#define DOUBLE_POLL	3


unsigned char get_pin(unsigned char pin, unsigned char mode)
{
	if(mode == POLL)
	{
		unsigned char res = 0;
		unsigned int i;
		for(i=0;i<POLL_STEPS;i++)
		{
			res |= read_pin(pin);
			_delay_ms(POLL_TIME_PER_STEP);
			if(res)
			{
				break;
			}
		}
		if(res)
		{
			_delay_ms(POLL_TIME_AFTER);
		}
		return res;
	}
	if(mode == DOUBLE_POLL)
	{
		unsigned char res = 0;
		unsigned int i;
		for(i=0;i<(POLL_STEPS*2);i++)
		{
			res |= read_pin(pin);
			_delay_ms(POLL_TIME_PER_STEP);
			if(res)
			{
				break;
			}
		}
		if(res)
		{
			_delay_ms(POLL_TIME_AFTER*2);
		}
		return res;

	}

	if(mode == STD)
	{
		return read_pin(pin);
	}
	return read_pin(pin);
}

