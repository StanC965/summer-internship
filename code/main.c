#include <iom324pb.h>

void main (void){
  
  DDRD |= 1 << 5;
  DDRD |= 1 << 4;
  DDRA |= 1 << 3;
  
  PORTD &= ~(1 << 5);
  PORTD &= ~(1 << 4);
  PORTA &= ~(1 << 3);
  
  while(1){
    
  }
  
}