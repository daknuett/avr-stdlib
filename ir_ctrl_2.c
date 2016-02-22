#define F_CPU 8000000UL

#define IO_IR PB0

#define LED_ON() PORTB |= (1 << IO_IR)
#define LED_OFF() PORTB &=~(1 << IO_IR)

// Length of a clock in microseconds (ca. 38,4kHz)
#define CLOCK_DURATION 9

// Number of clocks per data burst
#define BURST_LENGTH 3088

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

// Clock-counts at which the LED state has to be toggled
// The values are determined by experimenting, they work
// with a 8MHz crystal oscillator
const uint16_t thresholds[8] = {2,164, 2564, 2597, 2727, 2760, 3054, 3087};

// Sends a single data burst (two of them are needed)
void burst() {
	uint16_t clock = 0;
	uint8_t current_threshold = 0;
	uint8_t status = 0;

	while(clock++ < BURST_LENGTH) {
		if (clock == thresholds[current_threshold]) {
			status ^= 1;
			current_threshold++;
		}

		if (clock & status) {
			LED_ON();
		} else {
			LED_OFF();
		}      

		_delay_us(CLOCK_DURATION);
	}

	LED_OFF();
	return;
}

int main(void) {
	// Initialize port
	DDRB |= (1 << IO_IR);

	// 8 Mhz herstellen
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
//	CLKPR &= ~(0|(1<<CLKPS1) | (1<<CLKPS0));

	burst();
	_delay_ms(63);
	burst();

	while(1) {
		_delay_ms(500);
		burst();
		_delay_ms(63);
		burst();
	}
}
