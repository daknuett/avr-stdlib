#define __DEV_M168_

#include<pins.h>
#define F_CPU 1000000ul
#define BAUD 1200
#include<usart.h>
#include<usart_io.h>
#include<util/delay.h>
#include<stdio.h>

void setup(void)
{
	usart_begin(UBRR_VAL);	
	stdout = &usart_stdout;
}

void servo(unsigned char pin,unsigned char degree)
{
	unsigned char val = ((degree + 45) % 180) / 3;
	analog_write(pin,val);
}

void loop(void)
{

	unsigned char i = 0;
	for(;i < 180;i++)
	{
		servo(15,i);
		printf("%u\n",i);
		_delay_ms(100);
	}
	for(;i > 0;i--)
	{
		servo(15,i);
		printf("%u\n",i);
		_delay_ms(100);
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


