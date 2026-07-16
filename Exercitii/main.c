#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

//volatile unsigned char count=20;
#pragma vector=TIMER0_COMPA_vect
__interrupt void TimerCTC(void)   // la 436 se cere  400 ms cu 50/50 duty cycle   pai atunci o sa modific top-ul prin prescale sa fie de 200 ms si dau toggle din 200 in 200
{                                       //astfel perioada e de 200 +200 adica 400 si duty cycle de 50%
   //count++;
    
   
   //if((count >=0&& count <=4 )|| ( count>10&& count <=20)) 
   //{
      led_TOGGLE(LED_ZERO);   
       
  // }
  // else if((count>4&&count<=10 )||(count>20&&count<=24))   
    // led_Set(LED_ZERO);
   
  // if(count>24)
//count=0;
   //
}

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 1);  
    
    
    led_Set(LED_FOUR);
    led_Set(LED_ZERO);
    


    gpio_set_pin(&TCCR0A,3);
    gpio_set_pin(&TCCR0A,6);  //toggle OC0A on Compare Match.
    gpio_set_pin(&TCCR0B,0);// Prescaler 1024 
    gpio_set_pin(&TCCR0B,2);//1024
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