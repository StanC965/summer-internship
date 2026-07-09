#include <iom324pb.h>

void main() {
  
    DDRD |= (1 << 4) | (1 << 5); 
    DDRA |= (1 << 3); 
    
    PORTD |= (1 << 4) | (1 << 5);
    PORTA |= (1 << 3);
    
    while (1) 
    {
        
        PORTD &= ~((1 << 5) | (1 << 4)); // LED1 & LED2
        PORTA |= (1 << 3);               // LED3
        
        for (volatile unsigned long i = 0; i < 350000; i++);
        
        PORTD |= (1 << 5);
        PORTD &= ~(1 << 4);
        PORTA &= ~(1 << 3);
        
        for (volatile unsigned long i = 0; i < 350000; i++);
        
        PORTD &= ~(1 << 5);
        PORTD |= (1 << 4);
        PORTA &= ~(1 << 3);
        
        for (volatile unsigned long i = 0; i < 350000; i++);
    }
  
}
