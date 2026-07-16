#include "sos.h"
#include "button.h"


void main() {
  
    Init_Button(SW0_DDR, SW0_PORT, SW0_PIN);
    Init_LED(LED0_DDR, LED0_PIN);
    PowerOff_LED(LED0_PORT, LED0_PIN);
    
    int sw0_pressed_conf = 0;
    int sw0_released_conf = 0;
    unsigned char is_sw0_pressed;
    
    unsigned char sos_active = 0;
        
    while (1) 
    {
              
      if (sos_active == 0)
        {
            is_sw0_pressed = Is_Button_Pressed(SW0_PINR, SW0_PIN, &sw0_pressed_conf, &sw0_released_conf);
            
            if (is_sw0_pressed == 1)
            {
                sos_active = 1; 
            }
        }
        else
        {
            Play_SOS();
        }
      
    }
  
}
