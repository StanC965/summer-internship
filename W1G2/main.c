#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"


extern volatile _Bool sos_stop; 

int pressed_confidence_level = 0;
int released_confidence_level = 0;
_Bool button_stable_state = 0;
int count = 0;

void setup(void)
{
    leds_initialize(1, 0, 0, 0, 0); 
    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    
    
    gpio_set_pin(&PORTC, 6);  
    
    sos_stop = 1;
}

void main(void)
{
    setup();

    while(1)
    {
      
        if(gpio_read_pin(&PINC, 6) == 0) 
        {
            pressed_confidence_level++;
            released_confidence_level = 0; 
        }
        else 
        {
            released_confidence_level++;
            pressed_confidence_level = 0;  
        }

                                                                // Nu am reusit sa implementez functia de toggle la SOS
        if(pressed_confidence_level > 200)              //momentan programul va activa sos doar atata timp cat este apasat butonul
        {                                       //imi este dificil sa dau debug deoarece,valorile de confidence se bazeaza pe sute de iteratii de while(1).
            if(button_stable_state == 0)         //
            {
                count++;  
                button_stable_state = 1;
                
                if(count % 2 == 0)
                {
                    sos_stop = 1; 
                }
                else
                {
                    sos_stop = 0; 
                }
            }
            pressed_confidence_level = 0; 
        }

      
        if(released_confidence_level > 200) 
        {
            button_stable_state = 0;      
            released_confidence_level = 0; 
        }

       
        if(count % 2 == 1)
        {
            SOS(); 
            
         
            if(sos_stop == 1)
            {
                count = 0; 
                
              
                button_stable_state = 1; 
            }
        }
        else
        {
            led_Reset(LED_ZERO); 
        }
    }
}