#include <iom324pb.h>

void main() {
  
    DDRD |= (1 << 4) | (1 << 5); 
    DDRA |= (1 << 3); 
    
    PORTD |= (1 << 4) | (1 << 5);
    PORTA |= (1 << 3);
    
    while (1) 
    {
        
        //LED1
        PORTD &= ~(1 << 5);
        for (unsigned long i = 0; i < 350000; i++); 
        PORTD |= (1 << 5); 
        for (unsigned long i = 0; i < 350000; i++); 
        
        //LED2
        PORTD &= ~(1 << 4);
        for (unsigned long i = 0; i < 350000; i++);
        PORTD |= (1 << 4); 
        for (unsigned long i = 0; i < 350000; i++);

        //LED3
        PORTA &= ~(1 << 3);
        for (unsigned long i = 0; i < 350000; i++); 
        PORTA |= (1 << 3);
        for (unsigned long i = 0; i < 350000; i++);
    }
  
}
