#include "iom324pb.h"
void set_pin(unsigned char pin)
{
  PORTC = PORTC | (1<<pin);
}

void reset_pin(unsigned char pin)
{
  PORTC = PORTC & ~(1<<pin);
}

void set_direction_pin(unsigned char pin, unsigned char direction)
{
  if (direction)
        DDRC |= (1 << pin);
    else
        DDRC &= ~(1 << pin);
}

void main(void)
{
  
    set_direction_pin(7, 1);   
    reset_pin(7); 
    while (1)
    { 
  
        
    }
}