#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"

int pressed_confidence_level = 0;
int released_confidence_level = 0;
_Bool button_stable_state = 0;
int count=0;

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 0); 
}

void main(void)
{
    setup();

 while(1)
    {
       
        if(gpio_read_pin(&PINC, 6)) 
        {
            pressed_confidence_level++;
            released_confidence_level = 0; 
        }
        else 
        {
            released_confidence_level++;
            pressed_confidence_level = 0;  
        }

  
       
        if(pressed_confidence_level > 200) 
        {
          
            if(button_stable_state == 1) 
            {
                count++;                  
                led_TOGGLE(LED_ZERO);     
                button_stable_state = 1; 
                SOS();
                
             gpio_Timer1_start(1, 64);
              led_TOGGLE(LED_ZERO); 
             
             while(TCNT1 < OCR1A);
             gpio_Timer1_stop();
            }
            pressed_confidence_level = 0; 
        }

        
        if(released_confidence_level > 200) 
        {
            button_stable_state = 1;    // am luat codul de  problema 254 si am pus 1 aici ca sa intre mereu pe ramura cu SOS    
            released_confidence_level = 0;
        }
    }
}