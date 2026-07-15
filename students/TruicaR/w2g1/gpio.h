
#ifndef GPIO_H
#define GPIO_H

void gpio_set_pin(volatile unsigned char *port, unsigned char pin);
void gpio_reset_pin(volatile unsigned char *port, unsigned char pin);
void gpio_set_direction(volatile unsigned char *ddr, unsigned char pin, unsigned char direction);
unsigned char gpio_read_pin(volatile unsigned char *pin_reg, unsigned char pin);
unsigned char gpio_debounce(volatile unsigned char *pin_reg, unsigned char pin);

#endif