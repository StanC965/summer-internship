#ifndef GPIO_C
#define GPIO_C
#include "iom324pb.h"
#include "gpio.h"

void setPin(volatile unsigned char* port,unsigned char pin){
    *port |= (1 << pin);
}

void resetPin(volatile unsigned char* port,unsigned char pin){
    *port &= ~(1<<pin);
} 

void setDirection(volatile unsigned char* ddr, unsigned char pin,_Bool dir){
   
    *ddr = (dir == 0) ? (*ddr & ~(1 << pin)) : (*ddr | (1 << pin));
}

void togglePin(volatile unsigned char* reg, unsigned char pin){
    *reg ^= (1<< pin);
    
}

unsigned char getPin(volatile unsigned char* reg, unsigned char pin){
  return ((*reg & (1<<pin)) != 0);
}
#endif