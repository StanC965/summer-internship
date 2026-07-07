#include "iom324pb.h"

void set_pin(volatile unsigned char* port,unsigned char pin){
    *port |= (1 << pin);
}

void reset_pin(volatile unsigned char* port,unsigned char pin){
    *port &= ~(1<<pin);
} 

void main(void){
  PORTC = 0xff;
  DDRC = 0xFF;
  reset_pin(&PORTC,7);
  while(1){}
}