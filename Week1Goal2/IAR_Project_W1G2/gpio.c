#ifndef GPIO_C
#define GPIO_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* No private variables */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin){
  *port |= (1 << pin);
}

void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin){
  *port &= ~(1 << pin);
}

void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin){
  *port ^= (1 << pin);
}

void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction){
  direction ? (*ddr |= (1 << pin)) : (*ddr &= ~(1 << pin));
}

#endif