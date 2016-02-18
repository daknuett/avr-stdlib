#ifndef __MOTOR_H_
#define __MOTOR_H_
#define MAX_MOTORS 4

typedef struct Motor;

typedef struct MotorHolder;

extern static volatile MotorHolder * motors = NULL;

typedef char MotorFD;

MotorFD _add_motor(char current,char pin1, char pin2);
MotorFD motor_begin(char current,char pin1,char pin2);
void set_motor(MotorFD motor, int value);
void motor_calib_drive(MotorFD motor,char pin);
void motor_stop(MotorFD motor,int current_speed);
void motor_vdrive(MotorFD motor,float speed, float calib);
void motor_vdrive_cm_s(MotorFD motor,float speed, float calib);
void motor_bsdrive_mm(MotorFD motor, float speed, float calib, float mm);
#endif
