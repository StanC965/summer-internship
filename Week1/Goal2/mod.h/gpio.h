#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define INPUT  0
#define OUTPUT 1

void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin);
void gpio_set_pin(volatile uint8_t *port, uint8_t pin);
void gpio_reset_pin(volatile uint8_t *port, uint8_t pin);
void gpio_toggle_pin(volatile uint8_t *port, uint8_t pin);

// Reads the current digital state of a pin from a target PINx register
uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin);

#endif /* GPIO_H */