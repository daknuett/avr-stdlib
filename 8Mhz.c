#include<avr/io.h>

int main(void)
{
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
	while(1);
}
