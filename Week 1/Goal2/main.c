//215
#include "iom324pb.h"

void setup(){
DDRC=0x80;
}

void main(void){
  setup();
  

  while(1){
    PORTC=0x7F;
    for(volatile long i=0;i<200000;i++);
    PORTC=0xFF;
    for(volatile long i=0;i<200000;i++);
  }
}