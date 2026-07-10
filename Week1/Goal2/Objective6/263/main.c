#include "sos.h"
#include "button.h"


void main() {
  
    Init_Button(SW0_DDR, SW0_PORT, SW0_PIN);
    Init_LED(LED0_DDR, LED0_PIN);
    PowerOff_LED(LED0_PORT, LED0_PIN);
    
    int sw0_pressed_conf = 0;
    int sw0_released_conf = 0;
    
    unsigned char stop_requested = 0;
    unsigned char sos_active = 0;
        
    while (1) 
    {
           
      if (sos_active == 0)
        {
            if (Is_Button_Pressed(SW0_PINR, SW0_PIN, &sw0_pressed_conf, &sw0_released_conf) == 1)
            {
                sos_active = 1;
                stop_requested = 0;
            }
        }

        if (sos_active == 1)
        {
            Play_Letter_S();
            
            for (unsigned long i = 0; i < 150000; i++) 
            {
                if (read_pin(SW0_PINR, SW0_PIN) == 0) { stop_requested = 1; }
            }

            if (stop_requested == 0) 
            {
                Play_Letter_O();
                
                for (unsigned long i = 0; i < 150000; i++) 
                {
                    if (read_pin(SW0_PINR, SW0_PIN) == 0) { stop_requested = 1; }
                }
            }

            if (stop_requested == 0) 
            {
                Play_Letter_S();
                
                for (unsigned long i = 0; i < 150000; i++) 
                {
                    if (read_pin(SW0_PINR, SW0_PIN) == 0) { stop_requested = 1; }
                }
            }

            if (stop_requested == 1) 
            {
                sos_active = 0;
                PowerOff_LED(LED0_PORT, LED0_PIN);
                
                while (read_pin(SW0_PINR, SW0_PIN) == 0); 
            }
        }
      
    }
  
}
