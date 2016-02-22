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

/* provide a (hopefully) fast library to use my km41c464 DRAM module */


/* XXX WARNING!!!: XXX there have to be 8bit left in this collumn! */

#define RAS 	PB5
#define CAS 	PB4
#define D	PB6
#define Q	PB7
#define RW	PB3

#include<util/atomic.h>
#include<avr/io.h>
#include"config/config_ram_km41c565.h"

void ram_putb(unsigned int row, unsigned int col, unsigned char __c)
{
	asm("#include<avr/io.h>\n#include\"config/config_ram_km41c565.h\"");
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		register int i;
		unsigned int now_col ;
		for (i = 0; i < 8; i++)
		{
			// set row
			RAM_ADDR_LOW = row;
			RAM_ADDR_HIGH = (row >> 7) & 0b111;
			asm("cbi RAM_ADDR_HIGH,RAS"); 
			asm("nop");
			asm("sbi RAM_ADDR_HIGH,RAS");
			now_col = col + i;
			RAM_ADDR_LOW = now_col;
			RAM_ADDR_HIGH = (now_col >> 7) & 0b111;
			asm("cbi RAM_ADDR_HIGH,CAS"); 
			asm("nop");
			asm("sbi RAM_ADDR_HIGH,CAS");

			// rightshift data
			asm("push r17 \n\tpush r18 \n\tmov r17,%0 \n\tmov r18,%1 \n\tlsr r17,r18"::"r"(i),"r"(__c));
			asm("andi r17, 0b1 \n\tldi r18, D \n\tlsl r17,r18 \n\tout RAM_ADDR_HIGH,r17");
		}
	}
}
