//215
#include "iom324pb.h"

void setup(){
DDRC=0x80;
}

void main(void){
  setup();
  PORTC=0x7F;
  while(1);
}