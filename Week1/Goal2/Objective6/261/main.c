#include "sos.h"


void main() {
  
    Init_LED(LED0_DDR, LED0_PIN);
    PowerOff_LED(LED0_PORT, LED0_PIN);
        
    while (1) 
    {
              
      Play_SOS();
      
    }
  
}
