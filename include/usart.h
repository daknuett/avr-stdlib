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


#ifndef __USART_H_
#define __USART_H_

#ifndef BAUD
#warning "warning: no BAUD defined: using 9600"
#define BAUD 9600
#endif

#ifndef F_CPU
#warning "warning: no F_CPU defined: using 1000000"
#define F_CPU 1000000ul
#endif

#define UBRR_VAL (F_CPU/8/BAUD-1)/2

#if defined(USART_POLL_MODE)
extern void usart_begin(unsigned int ubrr);
#elif defined(USART_INT_MODE)

#else
#error "no valid usart mode defined"
#endif

extern void usart_putc(char chr);
extern char usart_getc(void);

#endif
