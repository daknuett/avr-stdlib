#define __DEV_M168_
#include<pins.h>
#define F_CPU 1000000ul
#include<util/delay.h>

// for usart
#define USART_INT_MODE
#define BAUD 9600

#include<usart.h>
#include<usart_io.h>
#include<stdio.h>

char pins[] = {27,28};
// {out1, in1, out2, in2}
#define NUM_PINS	2
unsigned int pins_block_in = 0,
	     pins_block_out = 0;
unsigned int signal_recognized = 0;
unsigned int had_no_signal = 0;
#define PIN_L_MAX 15


void setup(void)
{
	usart_begin(UBRR_VAL);
	pin_mode(28,PIN_IN);
	pin_mode(14,PIN_OUT);
	DDRB = 0xff;
}

int main(void)
{
	setup();
	int cnt = 0;
	unsigned int last_cnt = 0;
	while(1)
	{
		int i = 0;
		write_pin(26,HIGH);
		_delay_ms(8);
		for ( i = 0; i < NUM_PINS; i++)
		{
			if( (i % 2) == 0 ) // outer pin
			{
				char pin = read_pin(pins[i]);
				if(!pin )
				{
					if(!( had_no_signal & ( 1 << (i + 1))))
					{
						if( pins_block_out & (1 << i))
						{
							// bin blockiert => kann nichts tun
							write_pin(13,HIGH);
						}
						else
						{
							
							if(pins_block_in & ( 1 << (i + 1)))
							{
								// jemand ist gerade raus
								cnt --;
								// blockier mich, damit der andere arbeiten  kann
								signal_recognized |= (1 << i);
							}
							else
							{
								// jemand kommt rein blockier mich selbst
								pins_block_out |= (1 << i);
							}

						}
					}
				}
				else
				{
					if( pins_block_out & (1 << i))
					{
						write_pin(13,HIGH);
					}
					if(signal_recognized & (1 << (i + 1)) )
					{
						// kann blockierung loesen
						pins_block_out &= ~ (1 << i);
						signal_recognized &= ~(1 << (i + 1));
						had_no_signal |= (1 << i);
					}
					had_no_signal &= ~(1 << (i + 1));
				}
				write_pin(13,LOW);
			}
			else
			{
				char pin = read_pin(pins[i]);
				if(!pin ) 
				{
					if(!(had_no_signal & (1 << (i - 1))))
					{
						if(pins_block_in & (1 << i))
						{
							write_pin(12,HIGH);
							// bin gerade blockiert
						}
						else
						{
							if(pins_block_out & ( 1 << (i - 1)))
							{
								// jemand ist grad rein
								cnt ++;
								signal_recognized |=  (1 << i);
							}
							else
							{
								// jemand will raus: blockier mich
								pins_block_in |= (1 << i);
							}
						}
					}
				}
				else
				{
					if(pins_block_in & (1 << i))
					{
						write_pin(12,HIGH);
					}
					if((signal_recognized & (1 << (i - 1)) ) )
					{
						// kann blockierung loesen
						pins_block_in &= ~ (1 << i);
						signal_recognized &= ~(1 << (i - 1));
						had_no_signal |= (1 << i);
					}
					had_no_signal &= ~(1 << (i - 1));

				}
				write_pin(12,LOW);
			
			}
		}
		write_pin(26,LOW);
		PORTB = cnt;
		if(cnt != last_cnt)
		{
			printf("%u\n",cnt);
			last_cnt = cnt;

		}
		_delay_ms(16);
	}
	return 0;
}


