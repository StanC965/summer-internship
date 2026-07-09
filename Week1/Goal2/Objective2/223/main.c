#include <iom324pb.h>

void main() {
  
    DDRD |= (1 << 4) | (1 << 5); 
    DDRA |= (1 << 3); 
    
    PORTD &= ~((1 << 4) | (1 << 5));
    PORTA &= ~((1 << 3));
    
    while (1) 
    {
    }
  
}
