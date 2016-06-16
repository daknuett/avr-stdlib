#define F_CPU 1000000ul
#include<extra/brushless3.h>
#include<util/delay.h>
#define __DEV_M168_
#include<pins.h>

int main(void)
{
	BL3MotorFD my_motor = bl3_motor_begin(11, 12,13, 14,15,  16,17);
	bl3_motor_current_select(my_motor, 100);

	while(1)
	{
		bl3_motor_step(my_motor);
		_delay_ms(40);
	}
}
