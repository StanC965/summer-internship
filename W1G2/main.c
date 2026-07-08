#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 


int count=0;
int pressed_confidence_level=0;
int released_confidence_level=0;

_Bool button_state=0;
void setup(void)
{
    leds_initialize(1, 1, 1, 1, 1);
    led_Set(LED_ZERO);
    led_Set(LED_TWO);
    led_Set(LED_THREE);
    led_Set(LED_ONE);
   
    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    
    
}

void main(void)
{
    setup();
   
    while(1)
    {
      if(gpio_read_pin(&PINC,6))
      {
        pressed_confidence_level++;
         released_confidence_level=0;
      }
      else
      {
      released_confidence_level++;
      pressed_confidence_level=0;
      
      }
      
      
      if(pressed_confidence_level>200)
      {
        if(button_state==0)
        {
          count++;
          led_TOGGLE(LED_ZERO);
          button_state=1;
        }
        pressed_confidence_level=0;
      }   
      
      if(released_confidence_level > 200) 
        {
            button_state = 0;       
            released_confidence_level = 0; 
        }
    }
}
