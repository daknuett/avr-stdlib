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
#include<stdlib.h>
#include<avr/io.h>
#include<one_wire.h>
#include<util/delay.h>

/*
   provide an interface for the ds18b20 in single slave mode.
   ( FIXME: add multislave)
 */

/* clear the unused bits */
int themp_appl_cfg(int raw, char cfg)
{
	cfg = cfg & 0x60;
	switch (cfg)
	{
		case 0x00:
			{
				raw = raw & ~7;
				return raw;
			}
		case 0x20:
			{
				raw = raw & ~3;
				return raw;
			}
		case 0x40:
			{
				raw = raw & ~1;
				return raw;
			}
		default:
			{
				return raw;
			}
	}
}

void request_themp(void)
{
		one_wire_reset();
		one_wire_putb(0xcc);
		one_wire_putb(0x44); // start conversion

		ONE_WIRE_DDR &= ~(1 << PB0);
		ONE_WIRE_PORT |= 1 << PB0;
		_delay_ms(1000);

}

int read_raw_themp(void)
{
	char * res = malloc(9);
	char i;
	one_wire_reset();
	one_wire_putb(0xcc);
	one_wire_putb(0xbe);
	for(i = 0;i < 9; i++)
	{
		res[i] = one_wire_getb();
	}

	int raw = (res[0] & 0xff) | (res[1] << 8);
	raw = themp_appl_cfg(raw,res[4]);
	free(res);
	return raw;
}

float celsius(int raw)
{
	return raw / 16.0;
}
