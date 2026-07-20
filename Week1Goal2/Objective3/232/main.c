/* 232 - reset_pin: reset (write 0 to) any pin of PORTC  */

#include "iom324pb.h"

#define LED0_PIN 7
#define DELAY_HALF_SECOND 15000UL

void delay(void)
{
    volatile unsigned long i;
    for (i = 0; i < DELAY_HALF_SECOND; i++) { }
}

void set_pin(unsigned char pin)
{
    PORTC |= (1 << pin);
}

void reset_pin(unsigned char pin)
{
    PORTC &= ~(1 << pin);
}

void main( void )
{
    DDRC |= (1 << LED0_PIN);      /* PC7  */

    while(1)
    {
        reset_pin(LED0_PIN);      /* write 0 -> LED0 ON  */
        delay();

        set_pin(LED0_PIN);        /* write 1 -> LED0 OFF */
        delay();
    }
}
