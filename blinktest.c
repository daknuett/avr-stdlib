
#include<avr/io.h>
#include<avr/interrupt.h>
#define F_CPU	1000000ul
#include<util/delay.h>

#define __DEV_M168_
#include"include/pins.h"


void setup(void)
{
	pin_mode(OC0A,PIN_OUT);
	pin_mode(OC0B,PIN_OUT);
	pin_mode(BY_P_PB1,PIN_IN);
}

void loop(void)
{
	static unsigned char led1_val=0;
	static unsigned char led2_val=0xff;
	analog_write(OC0A,led1_val);
	analog_write(OC0B,LOW);
	while(!get_pin(BY_P_PB1,DOUBLE_POLL))
	{
	}
	analog_write(OC0A,LOW);
	analog_write(OC0B,led2_val);
	while(!get_pin(BY_P_PB1,DOUBLE_POLL))
	{
	}

	led1_val = analog_read(ADC0)>>1;
	led2_val = analog_read(ADC1)>>1;
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
