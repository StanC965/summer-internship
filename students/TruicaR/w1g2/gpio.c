#include "iom324pb.h"
#include "gpio.h"

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
    if (direction)
        DDRC |= (1 << pin);
    else
        DDRC &= ~(1 << pin);
}

unsigned char read_pin(unsigned char pin)
{
    return (PINC & (1 << pin)) ? 1 : 0;
}