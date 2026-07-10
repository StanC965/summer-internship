#include "led.h"

void main() {
  
    set_direction(&DDRC, 6, INPUT);    
    set_pin(&PORTC, 6);
    
    unsigned char pinc_value;
    
        
    while (1) 
    {
        
      pinc_value = PINC;
      
    }
  
}
