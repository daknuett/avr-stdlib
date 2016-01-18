#define __DEV_M168_
#define F_CPU 1000000ul
#include<pins.h>
#include<util/delay.h>

#include<lcd.h>
#include<lcd_io.h>
#include<stdio.h>

#include<calculations.h>

void setup(void)
{
	lcd_begin();
	stdout = &lcd_stdout;
}

void loop(void)
{
	unsigned int val = analog_get(26,NORMAL_MODE);
	printf("pin 25: %d.%d\n",pseudo_float(no_float(voltage(val,5),100),100));
	_delay_ms(1000);
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


