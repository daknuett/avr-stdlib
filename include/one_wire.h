#ifndef __ONE_WIRE_H_
#define __ONE_WIRE_H_
/* vim: set syntax=c: */

extern char one_wire_reset(void);
extern void one_wire_write_bit(char bit);
extern char one_wire_read_bit(void);
extern char one_wire_getb(void);
extern void one_wire_putb(char _c);

#endif
