#ifndef GPIO_H
#define GPIO_H

void set_pin(unsigned char pin);
void reset_pin(unsigned char pin);
void set_direction(unsigned char pin, unsigned char direction);
unsigned char read_pin(unsigned char pin);   

#endif