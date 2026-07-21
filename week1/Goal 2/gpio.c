#include "gpio.h"

void set_pin(volatile unsigned char *reg,PIN_Number pin){
  *reg |=(0x01<<pin);
}
void reset_pin(volatile unsigned char *reg,PIN_Number pin){
  *reg &=~(0x01<<pin);
}
void toggle_pin(volatile unsigned char *reg,PIN_Number pin){
  *reg ^=(0x01<<pin);
}
void set_direction(volatile unsigned char *registru,PIN_Number pin, int direction ){
  (direction==1)? (*registru |=(0x01<<pin)) : (*registru &=~(0x01<<pin));     
}
void delay(unsigned long i){
  i*=100000;
  while(i>0){
  i--;
  }
}