#include "led.h"

void main() {
  
    set_direction(&DDRC, 6, INPUT);    
    set_pin(&PORTC, 6);
    
    Init_LED(LED0_DDR, LED0_PIN);
    PowerOff_LED(LED0_PORT, LED0_PIN);
    
    unsigned char pinc_value;
    
        
    while (1) 
    {
        
      pinc_value = PINC;
      
      if ((pinc_value & (1 << 6)) == 0) 
        {
            PowerOn_LED(LED0_PORT, LED0_PIN);
        } 
        else 
        {
            PowerOff_LED(LED0_PORT, LED0_PIN);
        }
      
    }
  
}
