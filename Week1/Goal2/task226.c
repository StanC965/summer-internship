#include "iom324pb.h"

void main(void){
   DDRD = 0x20;
   DDRA = 0x08;
   PORTA = 0xff;
   PORTD = 0xff;
   while(1){
      PORTA = 0XFF;
      DDRD = 0x30; // se aprinde led 1,2 se stinge 3
      PORTD = 0x00;
      
      for(long i=0;i<20000;i++);
      
      DDRD = 0x10;// se aprinde ledul 3 si ramane aprins doar 2
      PORTA = 0x00;
      for(long i=0;i<20000;i++);
      DDRD = 0x20;
      // se stinge ledul 2
      for(long i=0;i<20000;i++);
      
   }
  

}