#include "iom324pb.h"
#include "gpio.h" 

/* Variabile globale de control */
int counter = 0;
_Bool state = 1;

void setup(void)
{
    
    gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);
    gpio_reset_pin(&PORTC, 7);
    
    
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
            gpio_set_pin(&PORTC, 7);    
                                                                        
            if(state)
            {
                gpio_reset_pin(&PORTC, 7);  
            }
            else                        
            {
                gpio_set_pin(&PORTC, 7);
            }
            
            state = !state;
              
            TCNT1 = 0;
            counter++;
            
            if(counter == 5)
            {
                //Dupa 5 perioade, transformam pinul in intrare (stinge LED-ul ) 
                gpio_set_direction(&DDRC, 7, GPIO_INPUT);
            }
        }
    }
}