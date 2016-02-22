#define __DEV_M168_

#define R_PIN 16
#define G_PIN 17
#define B_PIN 15

#include<pins.h>

#define F_CPU	1000000ul
#include<util/delay.h>

void setup(void)
{
	pin_mode(R_PIN,PIN_OUT);
	pin_mode(G_PIN,PIN_OUT);
	pin_mode(B_PIN,PIN_OUT);
}

void loop(void)
{
	analog_write(R_PIN,255);
	analog_write(G_PIN,255);
	analog_write(B_PIN,255);
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

