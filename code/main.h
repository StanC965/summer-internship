#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define INPUT 0
#define OUTPUT 1

void gpio_set_pin(volatile uint8_t *port, uint8_t pin);
void gpio_reset_pin(volatile uint8_t *port, uint8_t pin);
void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin);
void gpio_toggle_pin(volatile uint8_t *port, uint8_t pin);
void delay(long count);

#endif 

void gpio_set_pin(volatile uint8_t *port, uint8_t pin){
  *port |= (1 << pin);
}

void gpio_reset_pin(volatile uint8_t *port, uint8_t pin){
  *port &= ~(1 << pin);
}

void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin){
  *ddr_register = (direction == OUTPUT) ? (*ddr_register | (1 << pin)) : (*ddr_register & ~(1 << pin)); 
}

void gpio_toggle_pin(volatile uint8_t *port, uint8_t pin){
  *port ^= (1 << pin);
}

void delay(long count){
  for(long i = 0; i < count; i++);
}