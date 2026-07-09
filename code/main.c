#include <iom324pb.h>

void delay(int count){
  for(int i = 0; i < count; i++);
}

void main (void){
  
  DDRC |= 1 << 7;
  
  while(1){
    PORTC &= ~(1 << 7);
    delay(100000);
    
    PORTC |= 1 << 7;
    delay(100000);
  }
  
}