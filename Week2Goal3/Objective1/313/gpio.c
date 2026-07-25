#ifndef GPIO_C
#define GPIO_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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

void gpio_enable_pullup(unsigned char pin)
{
    /* when the pin is an input, writing 1 in PORTC enables the internal pull-up */
    PORTC |= (1 << pin);
}

unsigned char gpio_read_pin(unsigned char pin)
{
    /* PINC holds the actual state of the port C pins */
    if ((PINC & (1 << pin)) != 0)
        return GPIO_HIGH;
    else
        return GPIO_LOW;
}

#endif
