#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 


#pragma vector=TIMER0_COMPA_vect
__interrupt void TimerCTC(void)
{
    led_TOGGLE(LED_ZERO);
}

void setup(void)
{
    
    leds_initialize(1, 1, 1, 1, 0);  
    
    // Stingem ledurile (active low)
    led_Set(LED_ONE);
    led_Set(LED_TWO);        
    led_Set(LED_THREE);
    led_Set(LED_ZERO);
    


    ////// TIMER 0 SETUP //////
    TCCR0A = 2; // Modul CTC
    TCCR0B = 5; // Prescaler 1024
    TCNT0 = 0;  
    OCR0A = 127; // Pentru 1 MHz / 1024 => 130 ms
    
    
    TIMSK0 |= (1 << TIMSK0_OCIE0A); 
    
    ////// INTRERUPERI GLOBALE ///////
    gpio_set_pin(&SREG, 7);
}

void main(void)
{
    setup();
                                                
    while(1)    
    {
       
    }
}