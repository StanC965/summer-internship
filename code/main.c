#include <iom324pb.h>

void main (void){
  
  DDRC |= 1 << 7;
  PORTC &= ~(1 << 7);
  
  while(1){
    
  }
}