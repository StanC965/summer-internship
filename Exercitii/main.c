#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"

extern volatile _Bool sos_stop; 

#pragma vector = PCINT2_vect
__interrupt void PinChangePortC_ISR(void)
{
  

    
    if ( (PINC & (1 << 6)) == 0 )  
    {
         sos_stop = !sos_stop;    
    }
    
   
  
}

void setup(void)
{
    leds_initialize(1, 0, 0, 0, 0); 
    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    gpio_set_pin(&PORTC, 6); 
    gpio_set_pin(&PCICR, 2);
    gpio_set_pin(&PCMSK2, 6);
    gpio_set_pin(&SREG, 7);
    sos_stop = 1; 
}

void main(void)
{
    setup();
                                                                      
    while(1)    
    {
        if(sos_stop == 0)
        {
            SOS();
        }
        else
        {
          
            led_Set(LED_ZERO);
        }
    }
}