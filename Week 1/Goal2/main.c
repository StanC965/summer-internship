//225
#include "iom324pb.h"

void setup(){
  DDRA=0x08;
  DDRD=0x30;;
}

void main(void){
    setup();

  while(1){
  PORTA=0xF7;
  PORTD=0xDF;
  for(long i=0;i<200000;i++);
  PORTD=0xEF;
  PORTA=0xFF;
  for(long i=0;i<200000;i++);

  }
}