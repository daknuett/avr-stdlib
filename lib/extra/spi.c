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

#include<pins.h>

#define SPI_TIMEOUT_ERR 2
#define SPI_COLL_ERR 3

int spi_err;


void spi_init(char spi_speed)
{

	// we need sck, ss and mosi to be writeable
	DDRB |= (1 << PB5) | (1<< PB4) | (1 << PB7);
	// speed modi: 0, 1, 2, 3
	spi_speed &= ~3;
	// just enable spi, idk what to do else....
	SPCR |= spi_speed;
	// hey we wonna be master
	SPCR |= (1 << SPE) | (1 << MSTR);
	spi_err = 0;
}


void spi_putc(char __c)
{
	SPDR = __c;
	while(! (SPSR & (1 << SPIF))); // domain collision error protection
}

char spi_getc(void)
{
	return SPDR;
}

char spi_get_resp(char __c)
{
	spi_putc(__c);
	return spi_getc();
}
