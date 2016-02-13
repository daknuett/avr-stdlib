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

/* provide blocking wait functions */

#include<util/delay.h>

void wait_ms(unsigned int ms)
{
	unsigned int i;
	for (i = 1; i < ms; i++)
	{
		_delay_ms(1);
	}
	// function + loop head might be like this
	_delay_us(900);
}

void wait_us(unsigned int us)
{
	unsigned int i;
	// assuming 3 us function overhead
	// assuming 4 cycles loop overhead
	us = us - (4 *  (us / F_CPU));
	for ( i = 3; i <  us; i++)
	{
		_delay_us(1);
	}
}

void wait_s(unsigned int s)
{
	unsigned int i;
	for(i = 0; i < s; i++)
	{
		_delay_ms(1000);
	}
}


