#include "led.h"

void main() {
  
    set_direction(&DDRC, 6, INPUT);    
    set_pin(&PORTC, 6);
    
    Init_LED(LED0_DDR, LED0_PIN);
    PowerOff_LED(LED0_PORT, LED0_PIN);    
        
    while (1) 
    {
              
      if (read_pin(&PINC, 6) == 0) // used newly added read_pin
        {
            PowerOn_LED(LED0_PORT, LED0_PIN);
        } 
        else 
        {
            PowerOff_LED(LED0_PORT, LED0_PIN);
        }
      
    }
  
}
