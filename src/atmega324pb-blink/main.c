#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*
 * Change LED_PORT/LED_DDR/LED_PIN if your board LED is on another pin.
 * ATmega324PB Xplained Pro commonly uses PORTB for onboard user LED.
 */
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB0

int main(void)
{
    LED_DDR |= (1u << LED_PIN);

    for (;;) {
        LED_PORT ^= (1u << LED_PIN);
        _delay_ms(250);
    }
}
