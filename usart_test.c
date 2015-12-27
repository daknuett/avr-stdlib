#define USART_POLL_MODE

#define F_CPU 1000000
#define BAUD 1200

#define __DEV_M168_

#include"include/usart.h"
#include"include/pins.h"

#include<util/delay.h>

void setup(void)
{
	usart_begin(UBRR_VAL);
	pin_mode(4,PIN_OUT);
	pin_mode(2,PIN_OUT);
	pin_mode(3,PIN_OUT);
	write_pin(4,HIGH);
	_delay_ms(1000);
	write_pin(4,LOW);
}

void loop(void)
{
	char string[5] = {'h','e','l','l','o'};
	unsigned char i;
	for(i=0;i<5;i++)
	{
		usart_putc(string[i]);
		if(i%2 == 0)
		{
			write_pin(4,HIGH);
		}
		else
		{
			write_pin(4,LOW);
		}
	}
}

int main(void)
{
	setup();
	while(1)
	{
		loop();
	}
	return 0;
}

