#define __DEV_M168_
#define F_CPU 1000000ul
#include<pins.h>
#include<util/delay.h>

#include<lcd.h>
#include<lcd_io.h>
#include<stdio.h>
#define BAUD 1200
#include<usart.h>

#include<calculations.h>

void setup(void)
{
	lcd_begin();
	usart_begin(UBRR_VAL);
	stdout = &lcd_stdout;
}

int main(void)
{
	setup();
	printf("reading data from\nusart\n");
	while(1)
	{
		char chr = usart_getc();
		if(chr != -1)
		{
			usart_putc(chr);
			lcd_putc(chr);
		}
	}
}
