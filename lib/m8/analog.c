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


#include<avr/io.h>

#include"pin_defs.h"

/* Routinen fuer analoges Schreiben und Lesen */

/* pins nach bedeutung */
#define OC2	17
#define OC1A	15
#define OC1B	16

/* analog in pins  */
#define ADC0	23
#define ADC1	24
#define ADC2	25
#define ADC3	26
#define ADC4	27
#define ADC5	28


void analog_write(unsigned char pin,unsigned char value)
{
	/* if pins do not support PWM, they are used in digial mode */
	pin_mode(pin,PIN_OUT);

	if(pin == OC1A)
	{
		if(value == 0)
		{
			TCCR1A &= ~(1<<COM1A1);
			write_pin(pin,value);
			return;
		}
		TCCR1A |= (1<<COM1A1)|(1<<WGM10)|(1<<WGM11)|(1<<WGM12);
		TCCR1B |= (1<<CS11);
		OCR1A=value;
		return;
	}
	if(pin == OC1B)
	{
		if(value == 0)
		{
			TCCR1A &= ~(1<<COM1B1);
			write_pin(pin,value);
			return;
		}
		TCCR1A |= (1<<COM1B1)|(1<<WGM10)|(1<<WGM11)|(1<<WGM12);
		TCCR1B |= (1<<CS11);
		OCR1B = value;
		return;
	}
	if(pin == OC2)
	{
		if(value == 0)
		{
			TCCR2 &= ~(1<<COM21);
			write_pin(pin,value);
			return;
		}
		TCCR2 |= (1<<CS21);
		TCCR2 |= (1<<COM21)|(1<<WGM20)|(1<<WGM21);
		OCR2 = value;
		return;
	}
	if(value>127)
	{
		write_pin(pin,HIGH);
	}
	else
	{
		write_pin(pin,LOW);
	}

}

unsigned int analog_read(unsigned char pin)
{
	/* use read_pin, if adc not supported */
	// interne 1.1 volt referenzspannung
	unsigned int res=0;
	pin_mode(pin,PIN_IN);
	if(pin == ADC0)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		// I am sorry, but this will save a LOT of space!
		goto adc_read;
	}
	if(pin == ADC1)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX0);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
	if(pin == ADC2)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX1);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
	if(pin == ADC3)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX0)|(1<<MUX1);
		ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
	if(pin == ADC4)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX2);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
	if(pin == ADC5)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX0)|(1<<MUX2);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
#ifdef ADC6
	if(pin == ADC6)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX2)|(1<<MUX1);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
#ifdef ADC7
	if(pin == ADC7)
	{
		ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX0)|(1<<MUX2)|(1<<MUX1);
		ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADPS2);
		goto adc_read;
	}
#endif
#endif
	return read_pin(pin);
adc_read:
	while(ADCSRA & (1<<ADSC));
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	res = ADCL;
	res |= (ADCH << 8);
	return res;
}
