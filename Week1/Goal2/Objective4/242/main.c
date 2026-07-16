#include "led.h"

void main() {
  
    Init_LED(LED0_DDR, LED0_PIN);
    
    PowerOff_LED(LED0_PORT, LED0_PIN);
        
    while (1) 
    {
        
      Toggle_LED(LED0_PORT, LED0_PIN);
        
      for (unsigned long i = 0; i < 350000; i++); 
      
    }
  
}
