#include <iom324pb.h>

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  
  // set PC as OUTPUT by setting bit 7 to 1
  DDRC |= 1 << 7;
  
  while(1){
    // drive PC7 LOW by clearing bit 7 to 0
    PORTC &= ~(1 << 7);
    delay(100000); // 2000 000
    
    // drive PC7 LOW by setting bit 7 to 1
    PORTC |= 1 << 7;
    delay(100000);
  }
  
}