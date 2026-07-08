#ifndef GPIO_H
#define GPIO_H

extern void set_pin(volatile unsigned char *port, unsigned char pin);

extern void reset_pin(volatile unsigned char *port, unsigned char pin);

extern void set_direction(volatile unsigned char *ddr, unsigned char pin, unsigned char direction);

extern void toggle_pin(volatile unsigned char *port, unsigned char pin);

extern unsigned char read_pin(volatile unsigned char *pin_reg, unsigned char pin);

#endif