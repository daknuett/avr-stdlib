#ifndef __LCD_H_
#define __LCD_H_
/* vim: set syntax=c: */

extern void lcd_setb(char __b);
extern void lcd_trig_en(void);
extern void lcd_putc(char __c);
extern void lcd_put_com(char com);
extern void lcd_begin(void);
extern void lcd_set_cursor(char line,char col);
extern void lcd_puts(const char * str);
extern void lcd_clear(void);

#endif
