#include "iom324pb.h"
#include "gpio.h"

void gpio_set_pin(unsigned char pin)
{
    PORTC |= (1 << pin);
}

void gpio_reset_pin(unsigned char pin)
{
    PORTC &= ~(1 << pin);
}

void gpio_set_direction(unsigned char pin, unsigned char direction)
{
    if (direction)
        DDRC |= (1 << pin);
    else
        DDRC &= ~(1 << pin);
}

unsigned char gpio_read_pin(unsigned char pin)
{
    return (PINC & (1 << pin)) ? 1 : 0;
}

unsigned char gpio_debounce(unsigned char pin)
{
    if (gpio_read_pin(pin) == 0)
    {
        for (volatile int i = 0; i < 2000; i++);
        if (gpio_read_pin(pin) == 0)
            return 1;
    }
    return 0;
}