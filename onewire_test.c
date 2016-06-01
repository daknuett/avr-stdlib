#define F_CPU 8000000ul
#define BAUD 1200
#define __DEV_M168_

#include<pins.h>
#include<calculations.h>
#include<stdlib.h>
#include<util/delay.h>
#include<avr/io.h>


#include<one_wire.h>

void setup(void)
{
	// 8Mhz
#ifdef __DEF_M168_
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
#elif defined(__DEV_M8_)
	OSCCAL = 0xff;
#endif
}

int appl_cfg(int raw, char cfg)
{
	cfg = cfg & 0x60;
	switch (cfg)
	{
		case 0x00:
			{
				raw = raw & ~7;
				return raw;
			}
		case 0x20:
			{
				raw = raw & ~3;
				return raw;
			}
		case 0x40:
			{
				raw = raw & ~1;
				return raw;
			}
		default:
			{
				return raw;
			}
	}
}

void loop(void)
{
	char  * res = malloc(9);
	char i = 0;
	int want = 27;
	if(!one_wire_reset())
	{
		_delay_ms(200);
		return;
	}

	while(1)
	{
		one_wire_reset();
		one_wire_putb(0xcc);
		one_wire_putb(0x44); // start conversion

		DDRB &= ~(1 << PB0);
		PORTB |= 1 << PB0;
		_delay_ms(1000);


		one_wire_reset();
		one_wire_putb(0xcc);
		one_wire_putb(0xbe);
		for(i = 0;i < 9; i++)
		{
			res[i] = one_wire_getb();
		}

		int raw = (res[0] & 0xff) | (res[1] << 8);
		raw = appl_cfg(raw,res[4]);

		float themp = raw / 16.0;
		if(themp < want)
		{
			write_pin(15,HIGH);
		}
		else
		{
			write_pin(15,LOW);
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
