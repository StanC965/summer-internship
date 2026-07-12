#ifndef GPIO_C
#define GPIO_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void gpio_set_pin(volatile uint8_t *port_register, uint8_t pin){
  *port_register |= (1 << pin);
}

void gpio_reset_pin(volatile uint8_t *port_register, uint8_t pin){
  *port_register &= ~(1 << pin);
}

void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin){
  *ddr_register = (direction == GPIO_OUTPUT) ? (*ddr_register | (1 << pin)) : (*ddr_register & ~(1 << pin)); 
}

void gpio_toggle_pin(volatile uint8_t *port_register, uint8_t pin){
  *port_register ^= (1 << pin);
}
  
uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin){
  return (*pin_register & (1 << pin));
}

#endif /* GPIO_C */