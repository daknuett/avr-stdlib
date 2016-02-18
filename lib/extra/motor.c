#define __DEV_M168_
#include<pins.h>
#define F_CPU 1000000ul
#define BAUD 1200
#include<util/delay.h>
#include<stdio.h>
#include<usart.h>
#include<usart_io.h>
#include<stdlib.h>

#define MAX_MOTORS 4

typedef struct
{
	char current, // PWM current select
	     pin1, // logical direction select1
	     pin2; // logical direction select2
}Motor;

typedef struct
{
	char num_motors;
	Motor ** motors;
}
MotorHolder;

static volatile MotorHolder * motors = NULL;

typedef char MotorFD;

MotorFD _add_motor(char current,char pin1, char pin2)
{
	Motor * new_motor = malloc(sizeof(Motor));
	new_motor->current = current;
	new_motor->pin1 = pin1;
	new_motor->pin2 = pin2;
	motors->motors[motors->num_motors] = new_motor;
	motors->num_motors++;
	return motors->num_motors - 1;
}

MotorFD motor_begin(char current,char pin1,char pin2)
{
	if(motors == NULL)
	{
		motors = malloc(sizeof(MotorHolder));
		motors->num_motors = 0;
		motors->motors = malloc(sizeof(Motor *) * MAX_MOTORS);

	}
	/* prepare for usage & prevent unexpected stuff */
	analog_write(current, 0);
	write_pin(pin1, 0);
	write_pin(pin2, 0);
	return _add_motor(current, pin1, pin2);
}

void set_motor(MotorFD motor, int value)
{
	if(motor > motors->num_motors)
	{
		return;
	}
	Motor mymotor = *(motors->motors[motor]);
	if(value > 0)
	{
		write_pin(mymotor.pin1, 1);
		write_pin(mymotor.pin2, 0);
	}
	if(value < 0)
	{
		write_pin(mymotor.pin2, 1);
		write_pin(mymotor.pin1, 0);
		value *= -1;
	}
	if(value == 0)
	{
		write_pin(mymotor.pin2, 0);
		write_pin(mymotor.pin1, 0);
	}
	analog_write(mymotor.current, value );
}

void motor_calib_drive(MotorFD motor,char pin)
{
	set_motor(motor,-200);
	while(!read_pin(pin));
	set_motor(motor,0);
}

void motor_stop(MotorFD motor,int current_speed)
{
	set_motor(motor, current_speed * -1);
	_delay_ms(4);
	set_motor(motor,0);
}

/* motor calibration:
 speed = 127 => 1 cm/s */
void motor_vdrive(MotorFD motor,float speed, float calib)
{
	// calibrate the speed
	speed *= calib;
	// my  hbridge is using an inverted signal
	speed = 255 - speed;
	set_motor(motor,(int) speed);
}
/* drive ``speed'' cm/s */
void motor_vdrive_cm_s(MotorFD motor,float speed, float calib)
{
	motor_vdrive(motor,speed * 127,calib);
}

/* XXX blocking
 	speed : in mm / s
 */
void motor_bsdrive_mm(MotorFD motor, float speed, float calib, float mm)
{
	/*||   s = v * t  =>  t = s / v  ||
	  ||   time in s                 ||*/
	float abs_speed = speed;
	if(mm < 0)
	{
		speed *= -1;
		mm *= -1;
	}
	float time = (1000 * mm) / abs_speed; // prevent division value problems
	motor_vdrive(motor, speed * 12.7, calib);
	wait_ms((int) time);
	motor_stop(motor, (int) speed * 12.7);


}

