#define __DEV_M168_
#include<pins.h>
#define F_CPU 1000000
#include<util/delay.h>

void lcd_enable(void)
{
	write_pin(27,HIGH);
	_delay_ms(10);
	write_pin(27,LOW);
}

int main(void)
{
	write_pin(27,LOW);
	write_pin(28,LOW);
	write_pin(13,LOW);
	DDRB = 0xff;
	_delay_ms(30);


	// init: 3 times soft-reset
	PORTB = 0x30;
	lcd_enable();
	_delay_ms(10);
	PORTB = 0x30;
	lcd_enable();
	_delay_ms(10);
	PORTB = 0x30;
	lcd_enable();
	_delay_ms(10);

	PORTB = 0x10;
	lcd_enable();
	_delay_ms(10);

	// blinking cursor moving right
	PORTB = 0b00000111;
	lcd_enable();

	_delay_ms(30);
	// enable display and cursor
	PORTB = 0b00001111;
	lcd_enable();
	_delay_ms(30);
	PORTB = 0b00011100;
	lcd_enable();

	// clear display
	PORTB =  1;
	lcd_enable();
	_delay_ms(30);

	write_pin(28,HIGH);
	PORTB = 'E';
	lcd_enable();
	write_pin(28,LOW);
	
	write_pin(28,HIGH);
	PORTB = 'F';
	lcd_enable();
	write_pin(28,LOW);


	while(1);

}
