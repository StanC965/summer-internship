#ifndef GPIO_H
#define GPIO_H

void gpio_set_pin(unsigned char pin);
void gpio_reset_pin(unsigned char pin);
void gpio_set_direction(unsigned char pin, unsigned char direction);
unsigned char gpio_read_pin(unsigned char pin);
unsigned char gpio_debounce(unsigned char pin);

#endif