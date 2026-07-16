#include <iom324pb.h>

#define INPUT  0
#define OUTPUT 1

void set_pin(unsigned char pin_number) 
{
    PORTC |= (1 << pin_number);
}

void reset_pin(unsigned char pin_number) 
{
    PORTC &= ~(1 << pin_number);
}

void set_direction(unsigned char pin_number, unsigned char direction) 
{
    if (direction == OUTPUT) 
    {
        DDRC |= (1 << pin_number);
    } 
    else 
    {
        DDRC &= ~(1 << pin_number);
    }
}

void main() {
  
    set_direction(7, OUTPUT);
    PORTC &= ~(1 << 7);
        
    while (1) 
    {
        
       
    }
  
}
