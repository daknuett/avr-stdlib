/* druckteller fahren lassen: test1 */

#define __DEV_M168_
#include<pins.h>
#define F_CPU 1000000ul
#include<util/delay.h>

#define teller_in1 13
#define teller_in2 14
#define teller_speed 15
#define FORWARD 1
#define BACKWARD 2

void drive(char direction,int speed)
{
	analog_write(teller_speed,speed);
	write_pin(teller_in1, ((direction & 1) != 0));
	write_pin(teller_in2, ((direction & 2) != 0));
}

void find_null(void)
{
	drive(BACKWARD,200);
	while(!read_pin(12));
	drive(0,0);
}


int main(void)
{

	while(1)
	{
		int i;
		find_null();
		drive(FORWARD,300);
		_delay_ms(300);
		for (i = 0; i < 5;i++)
		{
			write_pin(28,HIGH);
			drive(1,100);
			_delay_ms(500);
			write_pin(28,LOW);
			drive(2,100);
			_delay_ms(500);
		}
	}
	return 0;
}
