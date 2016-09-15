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


#include<extra/spi.h>
#include<stdlib.h>
#include<stdint.h>
#include<pins.h>

// XXX test:
#define MAX_SD_CARDS 2

struct _SDCard
{
	char ss; // pin to select/unselect the slave
	uint32_t blocksize;
};
typedef struct _SDCard * SDCard;
#define sizeof_SDCard sizeof(struct _SDCard)
typedef size_t SDCardFD;

struct _SDCommand
{
	char opcode,
	     autodelete, // automatically delete the command after sending it
	     cs;
	char * args; // len(args) == 4
};

typedef struct _SDCommand * SDCommand; 
#define sizeof_SDCommand sizeof(struct _SDCommand)


SDCommand newSDCommand(char opcode, char autodelete, char cs, 
		char arg1, char arg2, char arg3, char arg4)
{
	SDCommand c = malloc(sizeof_SDCommand);
	c->opcode = opcode;
	c->autodelete = autodelete;
	c->cs = cs;
	c->args = malloc(sizeof(char) * 4);
	c->args[0] = arg1;
	c->args[1] = arg2;
	c->args[2] = arg3;
	c->args[3] = arg4;
	return c;
}

#define sd_command_with_int32_t(opcode, autodelete, cs, int_32_t_args) newSDCommand(opcode, autodelete, cs,\
		( int_32_t_args & 0xff),\
		( int_32_t_args >> 8) & 0xff,\
		( int_32_t_args >> 16) & 0xff,\
		( int_32_t_args >> 24) & 0xff)

#define CMD0 newSDCommand(0x40, 1, 0x95, 0,0,0,0)

#define __sd_select_card(sdcard) write_pin(sdcard->ss, 0)
#define __sd_deselect_card(sdcard) write_pin(sdcard->ss, 1)

volatile SDCard * sdcards = NULL;
volatile SDCardFD sdcard_pointer = 0;
// just grab some ram to read responses from sdcards
char ** unused_buffer8;

SDCardFD sd_register_card(char ss)
{
	if(sdcards == NULL)
	{
		sdcards = malloc(sizeof_SDCard * MAX_SD_CARDS);
		char * c = (malloc(sizeof(char) * 8));
		unused_buffer8 = &c;
	}
	sdcards[sdcard_pointer] = malloc(sizeof_SDCard);
	sdcards[sdcard_pointer]->ss = ss;
	sdcards[sdcard_pointer]->blocksize = 512; // blocksize is initialized as 512 on the device
	return sdcard_pointer++;
}


char __sd_write_command( SDCommand com)
{
	spi_get_resp(com->opcode);
	register char count;
	for(count = 0; count < 4; count ++)
	{
		spi_get_resp(com->args[count]);
	}
	char res = spi_get_resp(com->cs);
	if(com->autodelete)
	{
		free(com->args);
		free(com);
	}
	return res;
}

char sd_read_resp(SDCardFD card, SDCommand com, size_t resp_len, char ** buffer)
{
	SDCard mycard = sdcards[card];
	__sd_select_card(mycard);
	char command_ok = __sd_write_command(com);
	register size_t iter;
	for(iter = 0; iter < resp_len; iter++)
	{
		*(buffer)[iter] = spi_get_resp(0xff);
	}
	__sd_deselect_card(mycard);
	return command_ok;
}

char sd_init_card(SDCardFD card)
{
	SDCard mycard = sdcards[card];
	__sd_deselect_card(mycard);
	size_t count;
	for(count = 0; count < 10; count ++)
	{
		// 80 clock cycles
		spi_get_resp(0xff);
	}
	sd_read_resp(card, CMD0, 8, unused_buffer8);

}
