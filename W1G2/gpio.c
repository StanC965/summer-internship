#ifndef GPIO_C
#define GPIO_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "gpio.h"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


void gpio_set_pin(volatile unsigned char *PORT, gpio_uint8_t bit)
{
    *PORT |= (1 << bit);  
}

void gpio_reset_pin(volatile unsigned char *port, gpio_uint8_t bit)
{
    (*port) &= ~(1 << bit);                 
}

void gpio_toggle_pin(volatile unsigned char *PORT, gpio_uint8_t bit)
{
    *PORT ^= (1 << bit);              
}

void gpio_set_direction(volatile unsigned char *ddr, gpio_uint8_t bit, gpio_uint8_t intrare)
{
    if(intrare == GPIO_TRUE)
    {
        *ddr &= ~(1 << bit);                             
    }
    else                                  
    {
        *ddr |= (1 << bit);
    }
}
#endif