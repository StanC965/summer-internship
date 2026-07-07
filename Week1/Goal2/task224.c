#include "iom324pb.h"

void main(void){
   DDRD = 0x20;
   DDRA = 0x08;
   
   while(1){
      PORTA = 0xff;
      DDRD = 0x20; // se aprinde led1 si se stinge ledul 3
      PORTD = 0x00;
      
      for(long i=0;i<20000;i++);
      
      DDRD = 0x10;// se aprinde ledul 2
     
      for(long i=0;i<20000;i++);
      PORTD = 0xff;
      PORTA = 0x00;  // se aprinde ledul 3
      for(long i=0;i<20000;i++);
      
   }
  

}