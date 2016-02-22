	.file	"ram_km42c464.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	ram_putb
	.type	ram_putb, @function
ram_putb:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  44 "ram_km42c464.c" 1
	#include<avr/io.h>
#include"config/config_ram_km41c565.h"
 ;  0 "" 2
/* #NOAPP */
	in r26,__SREG__
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	movw r18,r24
	lsl r18
	mov r18,r19
	rol r18
	sbc r19,r19
	neg r19
	mov r21,r18
	andi r21,lo8(7)
	mov r18,r22
	mov r19,r23
	ldi r22,0
	ldi r23,0
.L3:
	out 0xb,r24
	out 0x5,r21
/* #APP */
 ;  54 "ram_km42c464.c" 1
	cbi RAM_ADDR_HIGH,RAS
 ;  0 "" 2
 ;  55 "ram_km42c464.c" 1
	nop
 ;  0 "" 2
 ;  56 "ram_km42c464.c" 1
	sbi RAM_ADDR_HIGH,RAS
 ;  0 "" 2
/* #NOAPP */
	out 0xb,r18
	movw r30,r18
	lsl r30
	mov r30,r31
	rol r30
	sbc r31,r31
	neg r31
	andi r30,lo8(7)
	out 0x5,r30
/* #APP */
 ;  60 "ram_km42c464.c" 1
	cbi RAM_ADDR_HIGH,CAS
 ;  0 "" 2
 ;  61 "ram_km42c464.c" 1
	nop
 ;  0 "" 2
 ;  62 "ram_km42c464.c" 1
	sbi RAM_ADDR_HIGH,CAS
 ;  0 "" 2
 ;  65 "ram_km42c464.c" 1
	push r17 
	push r18 
	mov r17,r22 
	mov r18,r20 
	lsr r17,r18
 ;  0 "" 2
 ;  66 "ram_km42c464.c" 1
	andi r17, 0b1 
	ldi r18, D 
	lsl r17,r18 
	out RAM_ADDR_HIGH,r17
 ;  0 "" 2
/* #NOAPP */
	subi r22,-1
	sbci r23,-1
	subi r18,-1
	sbci r19,-1
	cpi r22,8
	cpc r23,__zero_reg__
	brne .L3
	out __SREG__,r26
	ret
	.size	ram_putb, .-ram_putb
	.ident	"GCC: (GNU) 4.8.1"
