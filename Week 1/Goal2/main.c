//225
#include "iom324pb.h"

void setup(){
  DDRA=0x08;
  DDRD=0x30;;
}

//led1    PD5 7654 3210
//led2    PD4
//led3    PA3

void main(void){
    setup();

  while(1){
  PORTD=0xFF;
  PORTA=0xFF;
  for(long i=0;i<300000;i++);
  PORTD=0xCF;
  PORTA=0xFF;
  for(long i=0;i<300000;i++);
  PORTD=0xEF;
  PORTA=0xF7;
  for(long i=0;i<300000;i++);
  PORTD=0xDF;
  PORTA=0xF7;
  for(long i=0;i<300000;i++);

  }
}