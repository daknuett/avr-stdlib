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
/* provide an interface for my DEM10485 LCD */

/*
   PORTB is data register, 8 bit mode
 */

// every command is done after 1.52 ms
#define LCD_LAT 2 //ms
#define LCD_TRIG 20 //us
#define __DEV_M168_
#include<pins.h>
#ifndef F_CPU
	#define F_CPU 1000000ul
#endif
#include<util/delay.h>

#include"lcd_config.h"
/*
   das ist ein fucking trigger-impuls, kein enable impuls!
   wer euch erzaehlt, dass das irgendwas mit enable zu tun
   hat, dem braucht ihr nicht zuhoeren.
   enable heisst an/aus!
   das hier macht: "hey lies mal meinen port!"
   das ist ein trigger!
 */

char lcd_cursor_line = 0,lcd_cursor_col = 0;

void lcd_trig_en(void)
{
	write_pin(LCD_EN,1);
	_delay_us(LCD_TRIG);
	write_pin(LCD_EN,0);
}

void lcd_setb(char __b)
{
	PORTB = __b;
	lcd_trig_en();
	_delay_ms(LCD_LAT);
}


void lcd_put_com(char com)
{
	lcd_setb(com);
}

#define LCD_SOFT_RESET 0x30
#define LCD_CLEAR 1
void lcd_begin(void)
{
	/*
	   register und so weiter fertig machen
	 */

	DDRB = 0xff;
	PORTB = 0;
	write_pin(LCD_EN,0);
	write_pin(LCD_RW,0);
	write_pin(LCD_RS,0);
	// auf lcd warten
	_delay_ms(40);


	/* 
	 absolut geil: ich lese ca. 5h lang das gottverdammte Datenblatt von
	 diesem display.
	 steht da ein einziges mal drin, das man den mist so initialisieren muss?
	 NEIN! steht da nicht drin!

	 wenn ihr den seht der das geschrieben hat( OYQ von DISPLAY Elektronik GmbH),
	 schneidet ihm die bremsleitungen durch.
	 */
	lcd_put_com(LCD_SOFT_RESET);
	_delay_ms(3);
	lcd_put_com(LCD_SOFT_RESET);
	lcd_put_com(LCD_SOFT_RESET);


	/*
	   
	 */
	// 8bit modus  4 zeilen
	lcd_put_com(0b111000);

	// cursor move right no display shift
	lcd_put_com(0b110);
	// cursor off und display on
	lcd_put_com(0b1100);
	lcd_put_com(LCD_CLEAR);


}

void lcd_set_cursor(char line,char col)
{
	if(line > LCD_LINES)
	{
		lcd_put_com(LCD_CLEAR);
	}
	// only 4 lines
	line %= LCD_LINES + 1;
	lcd_cursor_line = line;
	char addr = 0;
	switch(line)
	{
		case 0:
			break;
		case 1:
			{
				addr = 0x40;
			}break;
		case 2:
			{
				addr = 0x14;
			}break;
		case 3:
			{
				addr = 0x54;
			}break;
	}
	addr += col;
	lcd_cursor_col = col;
	lcd_put_com(0b10000000 | addr);
	
}

void lcd_clear(void)
{
	lcd_set_cursor(0,0);
	lcd_put_com(1);
}

void lcd_putc(char __c)
{
	if(__c == '\n')
	{
		lcd_set_cursor(lcd_cursor_line+1,0);
	}
	else if(__c == '\r')
	{
		lcd_set_cursor(lcd_cursor_line,0);
	}
	else
	{
		write_pin(LCD_RS,1);
		lcd_setb(__c); 
		write_pin(LCD_RS,0);
	}
}

void lcd_puts(const char * str)
{
	int iter = 0;
	while( str[iter] )
	{
		lcd_putc(str[iter++]);
	}
}
