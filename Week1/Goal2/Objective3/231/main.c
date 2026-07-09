#include <iom324pb.h>

void set_pin(unsigned char pin_number) 
{
    PORTC |= (1 << pin_number);
}

void main() {
  
    DDRC |= (1 << 7);
    PORTC &= ~(1 << 7);
    
    for (volatile unsigned long i = 0; i < 700000; i++);
    
    while (1) 
    {
        
       set_pin(7);
       
    }
  
}
