//226
#include "iom324pb.h"

void setup(){
  DDRC=0x80;
}

void set_pin(unsigned char pin){
  PORTC=PORTC | (1<<pin);
}

void main(void){
    setup();
    PORTC=0x7F;
    for(long i=0;i<200000;i++);
    set_pin(7);
    

  while(1);
}