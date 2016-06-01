#include<avr/io.h>

int main(void)
{
	CLKPR = (1 << CLKPCE);
	CLKPR = (1<<CLKPS1) | (1<<CLKPS0) ;
	while(1);
}

