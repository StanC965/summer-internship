/* 234 - toggle_pin: toggle (invert) any PORTC pin without affecting the other pins
   XOR: a bit XOR 1 flips it, a bit XOR 0 stays the same. */

#include "iom324pb.h"

#define LED0_PIN 7
#define DELAY_HALF_SECOND 15000UL

#define INPUT  0
#define OUTPUT 1

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

void set_direction(unsigned char pin, unsigned char direction)
{
    if (direction == OUTPUT)
        DDRC |= (1 << pin);
    else
        DDRC &= ~(1 << pin);
}

void toggle_pin(unsigned char pin)
{
    PORTC ^= (1 << pin);
}

void main( void )
{
    set_direction(LED0_PIN, OUTPUT);

    while(1)
    {
        toggle_pin(LED0_PIN);     /* each call flips LED0: ON -> OFF -> ON ... */
        delay();
    }
}
