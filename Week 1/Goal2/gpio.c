#ifndef GPIO_C
#define GPIO_C

#include "gpio.h"
#include "iom324pb.h"

void set_pin(volatile unsigned char *port,unsigned char pin){
  *port|= (1<<pin);
}

void reset_pin(volatile unsigned char *port,unsigned char pin){
  *port &=  ~(1<<pin);
}

void set_direction(volatile unsigned char *ddr,unsigned char pin, unsigned char direction){
  *ddr= (direction==1)?  (*ddr | (1<<pin)) : (*ddr & ~(1<<pin));
}

void toggle_pin(volatile unsigned char *port,unsigned char pin){
  *port^= (1<<pin);
}

#endif