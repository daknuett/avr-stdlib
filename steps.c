/* make the floppy stepper drive */
#define __DEV_M168_
#include<pins.h>
#define F_CPU 1000000ul
#include<util/delay.h>

#define stepper_step_pin 27
#define stepper_dir_pin 26
volatile int pos = 0;

#define max_pos 158
// maximal pos

void to_pos(int new_pos)
{
	char dir = new_pos < pos;
	write_pin(stepper_dir_pin,dir);
	if(new_pos >max_pos)
	{
		new_pos = max_pos;
	}
	while(pos != new_pos)
	{
		// trigger one step
		write_pin(stepper_step_pin,1);
		_delay_ms(30);
		write_pin(stepper_step_pin,0);
		if(dir)
		{
			pos--;
		}
		else
		{
			pos++;
		}
	}
	
}
int main(void)
{
	while(1)
	{
		to_pos(50);
		to_pos(60);
		to_pos(0);
	}
	return 0;
}

