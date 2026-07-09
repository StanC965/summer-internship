#include <iom324pb.h>

void main() {
  
  while(1){
    DDRC |= (1 << 7); 
    PORTC &= ~(1 << 7);
  }
  
}
