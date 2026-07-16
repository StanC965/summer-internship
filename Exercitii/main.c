#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

volatile unsigned char count=20;
#pragma vector=TIMER0_COMPA_vect
__interrupt void TimerCTC(void)
{
   count++;
   
   
   if(count >=0&& count <=14)   // 70% din 20 este high unde o divizie este 50 milisecunde deci 50*20 =1 sec
   {
      led_Reset(LED_ZERO);   
       
   }
   else if(count>14&&count<=20)   
     led_Set(LED_ZERO);
   
   if(count>20)
     count=0;
   
}

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 1);  
    
    
    led_Set(LED_FOUR);
    led_Set(LED_ZERO);
    


    gpio_set_pin(&TCCR0A,3);
    gpio_set_pin(&TCCR0A,6);  //toggle OC0A on Compare Match.
    gpio_set_pin(&TCCR0B,2);// Prescaler 256 
    gpio_set_pin(&TCCR0B,3);//fast pwm
    TCNT0 = 0;  
    OCR0A =194; //  194.3125 pentru 50 ms   deci 194 va fi 49.91 care e neglijabil.
    
    
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