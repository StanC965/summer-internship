//223
#include "iom324pb.h"

void setup(){
  DDRA=0x08;
  DDRD=0x30;;
}

void main(void){
  setup();
  PORTA=0xF7;
  PORTD=0xCF;

  while(1);
}