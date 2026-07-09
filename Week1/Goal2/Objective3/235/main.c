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
    (direction == OUTPUT) ? (DDRC |= (1 << pin_number)) : (DDRC &= ~(1 << pin_number));
}

void toggle_pin(unsigned char pin_number) 
{
    PORTC ^= (1 << pin_number);
}

void main() {
  
    set_direction(7, OUTPUT);
    set_pin(7);
        
    while (1) 
    {
        
      toggle_pin(7); 
        
      for (unsigned long i = 0; i < 350000; i++); 
      
    }
  
}
