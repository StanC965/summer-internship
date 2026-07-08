#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

int counter = 0;
_Bool state = 1;

void setup(void)
{
    leds_initialize(1, 1, 1, 1, 1);
    led_Reset(LED_ZERO);
    
    TCNT1 = 0;
    OCR1A = 15625;     // 1 secunda
    TCCR1A = 0;
    TCCR1B = 0x03;     // Prescaler 64, Mod Normal
}

void main(void)
{
    setup();

    while(1)
    {
        if (TCNT1 >= OCR1A)   
        {
            led_Set(LED_ZERO);   
                                                                                                        
            if(state)
            {
                 led_Reset(LED_ZERO); 
            }
            else                        
            {
                led_Set(LED_ZERO); 
            }
            
            state = !state;
              
            TCNT1 = 0;
            counter++;
            
            if(counter == 5)
            {
                
                gpio_set_direction(&DDRC, 7, GPIO_INPUT);
            }
        }
    }
}