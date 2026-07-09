#include "gpio.h"

void main() {
  
    set_direction(&DDRC, 7, OUTPUT);
    set_pin(&PORTC, 7);
        
    while (1) 
    {
        
      toggle_pin(&PORTC,7); 
        
      for (unsigned long i = 0; i < 350000; i++); 
      
    }
  
}
