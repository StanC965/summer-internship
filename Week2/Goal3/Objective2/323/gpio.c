#ifndef GPIO_C
#define GPIO_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void gpio_set_pin(volatile unsigned char *port_reg, unsigned char pin_number) 
{
    *port_reg |= (1 << pin_number);
}

void gpio_reset_pin(volatile unsigned char *port_reg, unsigned char pin_number) 
{
    *port_reg &= ~(1 << pin_number);
}

void gpio_set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction) 
{
    (direction == GPIO_OUTPUT) ? (*port_reg |= (1 << pin_number)) : (*port_reg &= ~(1 << pin_number));
}

void gpio_toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number) 
{
    *port_reg ^= (1 << pin_number);
}

unsigned char gpio_read_pin(volatile unsigned char *pin_reg, unsigned char pin_number)
{
    return ((*pin_reg & (1 << pin_number)) != 0) ? 1 : 0;
}
#endif