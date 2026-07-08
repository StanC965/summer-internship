#include "iom324pb.h"
#include "gpio.h" 
#include "gpio.h" 
#include "led.h" 


int count=0;
void setup(void)
{
    //leds_initialize(1, 1, 1, 1, 1);
    //led_Reset(LED_ZERO);
   
    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    
    
}

void main(void)
{
    setup();
   gpio_uint8_t button_state_before = GPIO_TRUE;
    while(1)
    {
      gpio_uint8_t button_state_now=gpio_read_pin(&PINC,6);    // pentru a stii cand s-a apasat o sa scriem 2 variabile,una care tine starea anterioara si una tine starea curenta
                                                              // principiul e similar ca la codul gray ,adica doar atunci cand apare o diferenta se schimba starea(incrementeaza count)
      if(button_state_before==1&& button_state_now==0)          //totusi  daca rulam normal poate aparea efectul de debounce
      {
        count++;
      }
     button_state_before=button_state_now;   
    }
}
