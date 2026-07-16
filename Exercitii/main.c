#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

//volatile unsigned char count=20;
#pragma vector=TIMER1_COMPA_vect
__interrupt void TimerCTC(void)   
{ 
  /*
avem cerinta urmatoare:with the first 200ms on HIGH (1 logic), then 300ms on LOW (0 logic), 
then 500ms on HIGH again, and finally 200ms on LOW again. Apply it to an LED.
din tot ce e aici cel mai mic divizor comun este 100 :
regula de 3 simpla : 1200 ms ..... 18750
                      100 ms .......x  x=18750 *100/1200=18750/12=  1562.5
daca alegem 1562 in loc de 1562.5 diferenta este neglijabila datorita faptului ca e un timer de 16 bits si e o valoarea mare
daca era de 8 bits trebuia ca la anumite intervale sa eliminam desincronizarea
  */
 
    led_Reset(LED_ZERO);  // acest  interrupt isi are rolul doar pentru primele 200 ms 
  
  
}

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 1);  
    
    
    led_Set(LED_FOUR);
    led_Set(LED_ZERO);
    


    gpio_set_pin(&TCCR1A,0);//fast pwm
    gpio_set_pin(&TCCR1A,1);  //fast pwm
    gpio_set_pin(&TCCR1B,3);// FASTPWM
    gpio_set_pin(&TCCR1B,1);//64
    gpio_set_pin(&TCCR1B,0);//64
    gpio_set_pin(&TCCR1B,4);//fast pwm
    TCNT1 = 0;  
    OCR1A =18750; // 18750 pentru 1.2 secunde cu prescale de 64  
    
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
          if(TCNT1 >= (2 *1562.5)&&TCNT1<= (5*1562.5) || TCNT1 >= 10* 1562.5)
            led_Set(LED_ZERO);
          else 
            {
              led_Reset(LED_ZERO);
             }
    }   
}