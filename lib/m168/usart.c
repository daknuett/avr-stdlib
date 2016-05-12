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
#include<util/atomic.h>


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
	UBRR0H = (unsigned char) ( ubrr >> 8 ); // high bits
	UBRR0L = (unsigned char) ( ubrr );

	// enable RX and TX
	UCSR0B = ( 1 << RXEN0 )|( 1 << TXEN0 );

	// frame format
	// 1 byte data, 1 stop bit
	UCSR0C = ( 1 << UCSZ00) | ( 1 << UCSZ01);
}

void usart_putc(char chr)
{
	// still transmitting
	while(!(UCSR0A & (1 << UDRE0 )));
	UDR0 = chr;
}

char usart_getc(void)
{
	// still receiving
	while(!(UCSR0A & ( 1 << RXC0 )));

	return UDR0;
}

// we will block the system, but there could be data
unsigned char usart_available(void)
{
	return 1;
}
#elif defined( USART_INT_MODE)
// XXX test this

#include<avr/interrupt.h>

void usart_begin(unsigned int ubrr)
{
	// refer to manual: interrupts should be turned of
	cli();
	// set baud
	UBRR0H = (unsigned char) ( ubrr >> 8 ); // high bits
	UBRR0L = (unsigned char) ( ubrr );

	// enable RX and TX
	UCSR0B = ( 1 << RXEN0 )|( 1 << TXEN0 );

	// frame format
	// 1 byte data, 1 stop bit
	UCSR0C = ( 1 << UCSZ00) | ( 1 << UCSZ01);

	// enable interrupt channels
	UCSR0B |= ( 1 << RXCIE0 ) | ( 1 << UDRIE0 );
	sei();
}


struct _FIFO_buffer
{
	char buffer[IO_BUF_S];
	int head , tail ;
};

typedef struct _FIFO_buffer FIFO_buffer;

volatile FIFO_buffer RX_buf;
volatile FIFO_buffer TX_buf;
volatile int RX_bytes = 0;
volatile int TX_bytes = 0;

void FIFO_buffer_putc(volatile FIFO_buffer *  buffer,char chr)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		int pos = buffer->head % IO_BUF_S;
		if(pos == buffer->tail - 1)
		{
			return;
		}
		buffer->buffer[pos] = chr;
		buffer->head = ( buffer->head + 1) % IO_BUF_S;
	}
}
char FIFO_buffer_getc(volatile FIFO_buffer * buffer)
{
	char res;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		int pos = buffer->tail % IO_BUF_S;
		buffer->tail = (pos + 1) % IO_BUF_S;
		res = buffer->buffer[pos];
	}
	return res;
}

ISR(USART_RX_vect)
{
	FIFO_buffer_putc(&RX_buf,UDR0);
	RX_bytes++;
}
ISR(USART_UDRE_vect)
{
	if(!(TX_bytes <= 0))
	{
		UDR0 = FIFO_buffer_getc(&TX_buf);
		TX_bytes--;
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);
	}
}

void usart_putc(char chr)
{
	FIFO_buffer_putc(&TX_buf,chr);
	UCSR0B |= (1<<UDRIE0);
	TX_bytes++;
}

char usart_getc(void)
{
	if(!(RX_bytes<=0))
	{
		char chr = FIFO_buffer_getc(&RX_buf);
		RX_bytes--;
		return chr;
	}
	return -1;
}

unsigned char usart_available(void)
{
	return RX_bytes;
}
#else
#error "no valid USART mode defined!"
#endif



