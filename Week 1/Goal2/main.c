//234
#include "iom324pb.h"

void setup(){
  DDRC=0x80;
}

void set_pin(unsigned char pin){
  PORTC=PORTC | (1<<pin);
}

void reset_pin(unsigned char pin){
  PORTC= PORTC & ~(1<<pin);
}

void set_direction(unsigned char pin, unsigned char direction){
  DDRC= (direction==1)?  (DDRC | (1<<pin)) : (DDRC & ~(1<<pin));
    
}

void toggle_pin(unsigned char pin){
  PORTC= PORTC ^ (1<<pin);
}

void main(void){
  setup();
  while(1);
}