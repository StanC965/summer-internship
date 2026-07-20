#ifndef GPIO_C
#define GPIO_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* include private types and definitions for the module mod */

#include "iom324pb.h"
#include "gpio.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void gpio_set_pin(unsigned char pin)
{
    PORTC |= (1 << pin);
}

void gpio_reset_pin(unsigned char pin)
{
    PORTC &= ~(1 << pin);
}

void gpio_toggle_pin(unsigned char pin)
{
    PORTC ^= (1 << pin);
}

void gpio_set_direction(unsigned char pin, unsigned char direction)
{
    if (direction == GPIO_OUTPUT)
        DDRC |= (1 << pin);
    else
        DDRC &= ~(1 << pin);
}

#endif
