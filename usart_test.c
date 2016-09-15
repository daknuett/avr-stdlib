
#define F_CPU 1000000ul
#define BAUD 1200

#define __DEV_M168_

#include"include/usart.h"
//#define __USE_USART_ONLY
#include"include/usart_io.h"
#include"include/pins.h"

#include<util/delay.h>
#include<stdio.h>


void setup(void)
{
	usart_begin(UBRR_VAL);
	/*
	pin_mode(4,PIN_OUT);
	pin_mode(15,PIN_OUT);
	write_pin(4,HIGH);
	_delay_ms(1000);
	write_pin(4,LOW);
	*/
}

void loop(void)
{
	/*
	char string[5]={'h','e','l','o','\n'};
	unsigned char i;

	for(i=0;i<5;i++)
	{
		write_pin(15,HIGH);
		usart_putc(string[i]);
		write_pin(15,LOW);
	}
	char chr;
	*/
	
	while(1)
	{
		printf("Hello, world\n");
		_delay_ms(1000);
	}
	
}

int main(void)
{
	setup();
	stdout = &usart_stdout;
	while(1)
	{
		loop();
	}
	return 0;
}

