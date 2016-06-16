/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.
 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.
 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#include<pins.h>
#include<util/delay.h>
#include<stdlib.h>

#define MAX_MOTORS 4

typedef struct
{
	char pin_current, // PWM current select
	     pin_1_H, // winding 1 HIGH
	     pin_1_L, // winding 2 LOW
	     pin_2_H, // ...
	     pin_2_L,
	     pin_3_H,
	     pin_3_L;
	char current;
	char status; // the current status of the rotor
}
BL3Motor;

typedef struct
{
	char num_motors;
	BL3Motor ** motors;
}
BL3MotorHolder;

volatile BL3MotorHolder * bl3_motors = NULL;

typedef char BL3MotorFD;

BL3MotorFD _bl3_add_motor(char current,
		char pin_1_H, char pin_1_L,
		char pin_2_H, char pin_2_L,
		char pin_3_H, char pin_3_L)
{
	BL3Motor * new_motor = malloc(sizeof(BL3Motor));
	new_motor->pin_current = current;
	new_motor->current = 255;
	new_motor->pin_1_H = pin_1_H;
	new_motor->pin_1_L = pin_1_L;
	new_motor->pin_2_H = pin_2_H;
	new_motor->pin_2_L = pin_2_L;
	new_motor->pin_3_H = pin_3_H;
	new_motor->pin_3_L = pin_3_L;
	new_motor->status = 1;
	bl3_motors->motors[bl3_motors->num_motors] = new_motor;
	bl3_motors->num_motors++;
	return bl3_motors->num_motors - 1;
}
void bl3_motor_turn_off(BL3MotorFD motor)
{
	BL3Motor * mymot =  bl3_motors->motors[motor];
	write_pin(mymot->pin_1_H, LOW);
	write_pin(mymot->pin_1_L, LOW);
	write_pin(mymot->pin_2_H, LOW);
	write_pin(mymot->pin_2_L, LOW);
	write_pin(mymot->pin_3_H, LOW);
	write_pin(mymot->pin_3_L, LOW);

}

BL3MotorFD bl3_motor_begin(char current,
		char pin_1_H, char pin_1_L,
		char pin_2_H, char pin_2_L,
		char pin_3_H, char pin_3_L)
{
	if(bl3_motors == NULL)
	{
		bl3_motors = malloc(sizeof(BL3MotorHolder));
		bl3_motors->num_motors = 0;
		bl3_motors->motors = malloc(sizeof(BL3Motor *) * MAX_MOTORS);
	}
	BL3MotorFD mymot =  _bl3_add_motor(current, pin_1_H, pin_1_L, pin_2_H, pin_2_L, pin_3_H, pin_3_L);
	// prevent unexpected stuff
	bl3_motor_turn_off(mymot);
	return mymot;
}


void bl3_motor_step(BL3MotorFD motor)
{

	BL3Motor * mymot =  bl3_motors->motors[motor];
	bl3_motor_turn_off(motor);
	analog_write(mymot->pin_current, mymot->current);
	switch(mymot->status)
	{
		case (0):
		{
			write_pin(mymot->pin_1_H, HIGH);
			write_pin(mymot->pin_2_L, HIGH);
			mymot->status++;
		}break;
		case (1):
		{
			write_pin(mymot->pin_3_H, HIGH);
			write_pin(mymot->pin_2_L, HIGH);
			mymot->status++;
		}break;
		case (2):
		{
			write_pin(mymot->pin_3_H, HIGH);
			write_pin(mymot->pin_1_L, HIGH);
			mymot->status++;
		}break;
		case (3):
		{
			write_pin(mymot->pin_2_H, HIGH);
			write_pin(mymot->pin_1_L, HIGH);
			mymot->status++;
		}break;
		case (4):
		{
			write_pin(mymot->pin_2_H, HIGH);
			write_pin(mymot->pin_3_L, HIGH);
			mymot->status++;
		}break;
		case (5):
		{
			write_pin(mymot->pin_1_H, HIGH);
			write_pin(mymot->pin_3_L, HIGH);
			mymot->status = 0;
		}break;
		default:
		{
			// not good :-0
			mymot->status = 0;
		}
	}
}

void bl3_motor_current_select(BL3MotorFD motor, char current)
{
	BL3Motor * mymot =  bl3_motors->motors[motor];
	mymot->current = current;
}
