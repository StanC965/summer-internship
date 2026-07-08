#include "iom324pb.h"

void delay_half_second(void)
{
    volatile unsigned long i;

    for (i = 0; i < 50000UL; i++)
    {

    }
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
    if (direction == 1)
    {
        DDRC |= (1 << pin);
    }
    else
    {
        DDRC &= ~(1 << pin);
    }
}

void main(void)
{
    set_direction(7, 1);

    while (1)
    {
        reset_pin(7);
        delay_half_second();

        set_pin(7);
        delay_half_second();
    }
}