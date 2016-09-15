#ifndef __SPI_H_
#define __SPI_H_


int spi_err;


void spi_init(char spi_speed);
void spi_putc(char __c);
char spi_getc(void);
char spi_get_resp(char __c);

#endif
