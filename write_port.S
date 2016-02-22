/* test writing to ports */

#include<avr/io.h>

.global main
	.type main,@function

main:
	/* initialize the stack pointer: is done automatically 
	 Stackpointer geht von RAMEND_HIGH an und waechst nach
	 RAMEND_LOW
	 */


	/* setup  */
	rcall setup
	/* forever loop */
.mainloop:
	rcall loop
	rjmp .mainloop

loop:
	ldi r16, 0b00100000
	ldi r17, 0b01000000
	or r16, r17
	out PORTD, r16
	rcall delay
	ldi r16,0
	out PORTD, r16
	rcall delay

	

setup:
	/* PD5 und PD6 ausgang */
	ldi r16, 0b01100000
	out DDRD, r16
	ret

delay:
	/* 254 zyklen warten */
	ldi r22, 1
.delay_loop:
	ldi r23, 0
	inc r22
	cpse r22,r23
	rjmp .delay_loop
	ret
