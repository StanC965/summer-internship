#include <iom324pb.h>

#define INPUT  0
#define OUTPUT 1

void set_pin(volatile unsigned char *port_reg, unsigned char pin_number) 
{
    *port_reg |= (1 << pin_number);
}

void reset_pin(volatile unsigned char *port_reg, unsigned char pin_number) 
{
    *port_reg &= ~(1 << pin_number);
}

void set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction) 
{
    (direction == OUTPUT) ? (*port_reg |= (1 << pin_number)) : (*port_reg &= ~(1 << pin_number));
}

void toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number) 
{
    *port_reg ^= (1 << pin_number);
}

void main() {
  
    set_direction(&DDRC, 7, OUTPUT);
    set_pin(&PORTC, 7);
        
    while (1) 
    {
        
      toggle_pin(&PORTC,7); 
        
      for (unsigned long i = 0; i < 350000; i++); 
      
    }
  
}
