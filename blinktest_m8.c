
#include<avr/io.h>
#include<avr/interrupt.h>
#define F_CPU	1000000ul
#include<util/delay.h>

#define __DEV_M8_
#include"include/pins.h"


void setup(void)
{
	pin_mode(OC2,PIN_OUT);
	pin_mode(OC1B,PIN_OUT);
	pin_mode(BY_P_PB1,PIN_IN);
}

void loop(void)
{
	static unsigned char led1_val=0;
	static unsigned char led2_val=0xff;
	analog_write(OC2,led1_val);
	analog_write(OC1B,LOW);
	while(!get_pin(BY_P_PB1,DOUBLE_POLL))
	{
		_delay_ms(2);
	}
	analog_write(OC2,LOW);
	analog_write(OC1B,led2_val);
	while(!get_pin(BY_P_PB1,DOUBLE_POLL))
	{
	}

	led1_val = analog_get(ADC0,SLOW_MODE)>>1;
	led2_val = analog_get(ADC1,0)>>1;
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
