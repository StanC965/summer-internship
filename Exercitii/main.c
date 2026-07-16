#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "CarCrashDetection.h"

volatile _Bool car_crashed=0;
#pragma vector=TIMER1_COMPA_vect
__interrupt void TimerCTC(void)   
{ 

 /*
  650 microsecunde inseamna 650 *10^(-6) => OCR1A= 650*10^(-6)*10^6/1-1= 650 -1 =649; (alegem minimul posibil deoarece oricum s-a pierdut timp de la impact 
pana la notificarea ca masina a facut accident 
 
*/
 led_Reset(LED_ZERO);
  gpio_reset_pin(&TCCR1B,0); 
}

void setup(void)
{
    
    leds_initialize(1, 0, 0, 0, 0);  
    
    
  
    led_Set(LED_ZERO);
    


    gpio_set_pin(&TCCR1A,0);//fast pwm
    gpio_set_pin(&TCCR1A,1);  //fast pwm
    gpio_set_pin(&TCCR1B,3);// FASTPWM
    
    //Ne asiguram ca e oprit
    gpio_reset_pin(&TCCR1B,0);
    gpio_reset_pin(&TCCR1B,1);
    gpio_reset_pin(&TCCR1B,2); 
    
    
    gpio_set_pin(&TCCR1B,4);//fast pwm
    TCNT1 = 0;  
    OCR1A =649;  
    
   //gpio_set_pin(&TIMSK1,0); //TOIE1
  gpio_set_pin(&TIMSK1,1); //OCIE1A
    
    ////// INTRERUPERI GLOBALE ///////
    gpio_set_pin(&SREG, 7);
    srand(31);
}

void main(void)
{
    setup();
                                              
    while(1)    
    {
      if(car_crashed==0)
      {
        
       if(GetCarCrashDetectionStatus())
       {
             gpio_set_pin(&TCCR1B,0);
              
       car_crashed=1;
       }
   

      }
    }
            
      
}