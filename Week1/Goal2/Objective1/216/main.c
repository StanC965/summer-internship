#include <iom324pb.h>

void main() {
  
  DDRC |= (1 << 7); 
  
  while(1){
    
        PORTC &= ~(1 << 7); 
        
        for (unsigned long i = 0; i < 700000; i++) {
        }
        
        PORTC |= (1 << 7);  
        
        for (unsigned long i = 0; i < 700000; i++) {
        }
  }
  
}
