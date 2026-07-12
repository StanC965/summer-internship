#include <iom324pb.h>

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  
  DDRD |= 1 << 5;
  DDRD |= 1 << 4;
  DDRA |= 1 << 3;
  
  while(1){
    PORTD &= ~(1 << 5);
    delay(50000);
    PORTD |= 1 << 5;
    delay(50000);
    
    PORTD &= ~(1 << 4);
    delay(50000);
    PORTD |= 1 << 4;
     delay(50000);
    
    PORTA &= ~(1 << 3);
    delay(50000);
    PORTA |= 1 << 3;
     delay(50000);
  }
  
}