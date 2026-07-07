#include "iom324pb.h"

void set_pin(volatile unsigned char* port,unsigned char pin){
    *port = (1 << pin);
}

void main(void){

  DDRC = 0xFF;
  set_pin(&PORTC,7);
  while(1){}
}