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

/* usart.c provide usart for atmegas */

// for interrupt driven usart
#include<avr/interrupt.h>
#include<avr/io.h>

// for test: POLL MODE
#define USART_POLL_MODE


/* POLL MODE */
#if defined( USART_POLL_MODE)


/* use precalculated ubrr value
 start usart in poll-mode (no interrupts)
 */
void usart_begin(unsigned int ubrr)
{
	/* only needed in interrupt mode
	// turn off interrupts, see manual

	cli();
	*/

	// set baud
	UBRRH = (unsigned char) ( ubrr >> 8 ); // high bits
	UBRRL = (unsigned char) ( ubrr & 0xff );

	// enable RX and TX
	UCSRB = ( 1 << RXEN )|( 1 << TXEN );

	// frame format
	// 1 byte data, 2 stop bits
	UCSRC = (1 << URSEL) | (1 << USBS ) | ( 1 << UCSZ0);
}
#elif defined( USART_INT_MODE)
// TODO implement this

#endif

/* all the same */
void usart_putc(char chr)
{
	// still transmitting
	while(UCSRA & (1 << UDRE ));
	UDR = chr;
}

char usart_getc(void)
{
	// still receiving
	while(UCSRA & ( 1 << RXC ));

	return UDR;
}


