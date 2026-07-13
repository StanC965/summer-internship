/* 233 - set_direction: set the direction (input/output) of any PORTC pin
   DDRC bit = 1 -> output 
   DDRC bit = 0 -> input. 
   Parameters: pin number and direction 
   Returns: nothing (void) it only configures the DDRC register */

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

void main( void )
{
    set_direction(LED0_PIN, OUTPUT);

    while(1)
    {
        reset_pin(LED0_PIN);      /* LED0 ON  */
        delay();
        set_pin(LED0_PIN);        /* LED0 OFF */
        delay();
    }
}
