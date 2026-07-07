#ifndef GPIO_C
#define GPIO_C
#include "iom324pb.h"
#include "gpio.h"

void set_pin(volatile unsigned char* port,unsigned char pin){
    *port |= (1 << pin);
}

void reset_pin(volatile unsigned char* port,unsigned char pin){
    *port &= ~(1<<pin);
} 

void set_direction(volatile unsigned char* ddr, unsigned char pin,_Bool dir){
   
    *ddr = (dir == 0) ? (*ddr & ~(1 << pin)) : (*ddr | (1 << pin));
}

void toggle_pin(volatile unsigned char* reg, unsigned char pin){
    *reg ^= (1<< pin);
    
}

unsigned char get_pin(volatile unsigned char* reg, unsigned char pin){
  return ((*reg & (1<<pin)) != 0);
}
#endif