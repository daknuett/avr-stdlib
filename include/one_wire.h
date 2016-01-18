#ifndef __ONE_WIRE_H_
#define __ONE_WIRE_H_

extern void one_wire_begin(char pin);
extern char one_wire_reset(void);
extern void write_bit(char bit);
extern char read_bit(void);
extern char read_byte(void);
extern void write_byte(char __b);

#endif
