#ifndef __brushless_3_h_
#define __brushless_3_h_

typedef struct 
{
	char current, // PWM current select
	     pin_1_H, // winding 1 HIGH
	     pin_1_L, // winding 2 LOW
	     pin_2_H, // ...
	     pin_2_L,
	     pin_3_H,
	     pin_3_L;
	char status; // the current status of the rotor
}BL3Motor;

typedef struct 
{
	char num_motors;
	BL3Motor ** motors;
}
BL3MotorHolder;
typedef char 
BL3MotorFD;

extern volatile BL3MotorHolder * bl3_motors;

BL3MotorFD _bl3_add_motor(char current,
		char pin_1_H, char pin_1_L,
		char pin_2_H, char pin_2_L,
		char pin_3_H, char pin_3_L);

void bl3_motor_turn_off(BL3MotorFD motor);

BL3MotorFD bl3_motor_begin(char current,
		char pin_1_H, char pin_1_L,
		char pin_2_H, char pin_2_L,
		char pin_3_H, char pin_3_L);

void bl3_motor_step(BL3MotorFD motor);
#endif
