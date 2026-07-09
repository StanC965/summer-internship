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

unsigned char debounce(unsigned char pin)
{
    if (read_pin(pin) == 0)                       
    {
        for (volatile int i = 0; i < 2000; i++);   
        if (read_pin(pin) == 0)                    
            return 1;
    }
    return 0;
}