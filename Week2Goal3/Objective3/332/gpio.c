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

void gpio_set_pin(gpio_reg_t port, unsigned char pin)
{
    *port |= (1 << pin);
}

void gpio_reset_pin(gpio_reg_t port, unsigned char pin)
{
    *port &= ~(1 << pin);
}

void gpio_toggle_pin(gpio_reg_t port, unsigned char pin)
{
    *port ^= (1 << pin);
}

void gpio_set_direction(gpio_reg_t ddr, unsigned char pin, unsigned char direction)
{
    if (direction == GPIO_OUTPUT)
        *ddr |= (1 << pin);
    else
        *ddr &= ~(1 << pin);
}

void gpio_enable_pullup(gpio_reg_t port, unsigned char pin)
{
    *port |= (1 << pin);
}

unsigned char gpio_read_pin(gpio_reg_t pinx, unsigned char pin)
{
    if ((*pinx & (1 << pin)) != 0)
        return GPIO_HIGH;
    else
        return GPIO_LOW;
}

#endif
