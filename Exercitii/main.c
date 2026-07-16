#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

//volatile unsigned char count=20;
#pragma vector=TIMER1_COMPA_vect
__interrupt void TimerCTC(void)   
{ 
  /*
  regula de trei simpla : 975 .... 1 secunda
                           X ...... 0.7 secunde => x=975*0.7/1=682.5 => daca 975.56 .... 1 secunda 
                                                                              682 .........x secunde  x=682/975.56=0.699085653368322 neglijabil
  */
 
    led_Reset(LED_ZERO);
  
  
}

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 1);  
    
    
    led_Set(LED_FOUR);
    led_Set(LED_ZERO);
    


    gpio_set_pin(&TCCR1A,0);//fast pwm
    gpio_set_pin(&TCCR1A,1);  //fast pwm
    gpio_set_pin(&TCCR1B,3);// FASTPWM
    gpio_set_pin(&TCCR1B,2);//1024
    gpio_set_pin(&TCCR1B,0);//1024
    gpio_set_pin(&TCCR1B,4);//fast pwm
    TCNT1 = 0;  
    OCR1A =975; // 975.56 pentru o secunda fix  => pentru 975 o sa fie 0.999425970724507 secunde o diferenta neglijabila
    
    gpio_set_pin(&TIMSK1,0); //TOIE1
    gpio_set_pin(&TIMSK1,1); //OCIE1A
    
    ////// INTRERUPERI GLOBALE ///////
    gpio_set_pin(&SREG, 7);
}

void main(void)
{
    setup();
                                                
    while(1)    
    {
        if(TCNT1 >= 682)
    led_Set(LED_ZERO);
    }   
}