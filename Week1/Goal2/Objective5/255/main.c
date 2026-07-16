#include "led.h"

#define THRESHOLD 500

void main() {
  
    set_direction(&DDRC, 6, INPUT);    
    set_pin(&PORTC, 6);
    
    Init_LED(LED0_DDR, LED0_PIN);
    PowerOff_LED(LED0_PORT, LED0_PIN); 
    
    unsigned char pressed = 0;
    int pressed_confidence = 0;
    int released_confidence = 0;
        
    while (1) 
    {
              
      if (read_pin(&PINC, 6) == 0)
        {
            pressed_confidence++;
            if(pressed_confidence > THRESHOLD)
            {
              if(pressed == 0)
              {
                PowerOn_LED(LED0_PORT, LED0_PIN);
                pressed = 1;
              }
              pressed_confidence = 0;
            }
        } 
        else 
        {
            released_confidence++;
            if(released_confidence > THRESHOLD)
            {
              PowerOff_LED(LED0_PORT, LED0_PIN);
              pressed = 0;
              released_confidence = 0;
            }
            
        }
      
    }
  
}
