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
	printf("pin 26: %d.%d   \r",pseudo_float(no_float(voltage(val,5),100),100));
	_delay_ms(10);
}

void print_hello(void)
{
	printf("Hallo Oma!\n");
	printf("Leider kann ich\nnicht da sein,weil\nich krank bin");
	_delay_ms(5000);
	lcd_clear();
	printf("und ich will\ndich nicht\ninfizieren");
	_delay_ms(5000);
	lcd_clear();
	printf("aber ich will dir\netwas zeigen, was\nich gemacht habe\n");
	_delay_ms(4000);
	lcd_clear();
	printf("alles gute\nDaniel <3");
	_delay_ms(3000);
	lcd_clear();
}

int main(void)
{
	setup();
	print_hello();
	printf("am roten rad drehen\n");
	printf("lese spannung\n");
	while(1)
	{
		loop();
	}
	return 0;
}


