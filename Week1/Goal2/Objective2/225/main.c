#include <iom324pb.h>

void main() {
  
    DDRD |= (1 << 4) | (1 << 5); 
    DDRA |= (1 << 3); 
    
    PORTD |= (1 << 4) | (1 << 5);
    PORTA |= (1 << 3);
    
    while (1) 
    {
        
        PORTD &= ~(1 << 5); // LED1
        PORTA &= ~(1 << 3); // LED3
        PORTD |= (1 << 4);  // LED2
        
        for (volatile unsigned long i = 0; i < 350000; i++);
        
        PORTD |= (1 << 5);
        PORTA |= (1 << 3);
        PORTD &= ~(1 << 4);
        
        for (volatile unsigned long i = 0; i < 350000; i++);
        
    }
  
}
