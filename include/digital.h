#ifndef __digital_h_
#define __digital_h_

extern void pin_mode(unsigned char pin, unsigned char mode);
extern void write_pin(unsigned char pin, unsigned char value);
extern unsigned char read_pin(unsigned char pin);
#endif
