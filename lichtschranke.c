#define __DEV_M168_
#include<pins.h>

void setup(void)
{
	pin_mode(28,PIN_OUT);
	pin_mode(27,PIN_IN);
}


void loop(void)
{
	while(1)
	{
		while(read_pin(27));
		while(!read_pin(27))
		{
			write_pin(28,HIGH);
		}
		write_pin(28,LOW);
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
