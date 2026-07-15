#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

volatile unsigned char on=0;
#pragma vector=TIMER0_COMPA_vect
__interrupt void TimerCTC(void)
{

      if(on!=0)
      led_TOGGLE(LED_ZERO);   //
    on++;
  
}

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 1);  
    
    // Stingem ledurile (active low)
    led_Set(LED_FOUR);
    led_Set(LED_ZERO);
    


    
    TCCR0A = 2; // Modul CTC
    TCCR0A|=1<<6; //toggle OC0A on Compare Match.
    TCCR0B = 5; // Prescaler 1024
    TCNT0 = 0;  
    OCR0A = 127; // Pentru 1 MHz / 1024 => 130 ms
    
    
    TIMSK0 |= (1 <<1); 
    
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