#include "gpio.h"

void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin) {
    *ddr_register = (direction == OUTPUT) ? (*ddr_register | (1 << pin)) : (*ddr_register & ~(1 << pin)); 
}

void gpio_set_pin(volatile uint8_t *port, uint8_t pin) {
    *port |= (1 << pin);
}

void gpio_reset_pin(volatile uint8_t *port, uint8_t pin) {
    *port &= ~(1 << pin);
}

void gpio_toggle_pin(volatile uint8_t *port, uint8_t pin) {
    *port ^= (1 << pin);
}

uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin) {
    return (*pin_register & (1 << pin)) ? 1 : 0;
}