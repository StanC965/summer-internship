  #include "iom324pb.h"
  #include "gpio.h" 
  #include "led.h" 


  volatile _Bool timer_pornit=0;
  volatile unsigned char perioade=0;

  #pragma vector=PCINT2_vect
  __interrupt void BUTTON_PRESS(void)   
  { 
    
      gpio_set_pin(&TCCR1B,0);
      gpio_set_pin(&TCCR1B,1);
      led_Reset(LED_ZERO);
      led_Reset(LED_ONE);
      TCNT1=0;
      
    timer_pornit=1;
  }

 #pragma vector = TIMER1_COMPA_vect
__interrupt void perioada(void)
{
    perioade++; // o secunda e o perioada
    
    if (timer_pornit)
    {
       
        if (perioade == 1)
        {
            led_Set(LED_ONE);
            led_Reset(LED_TWO); // Aprindem LED2
        }
        
        
        if (perioade == 5)
        {
            led_Set(LED_TWO);   
            led_Reset(LED_THREE); // Aprindem LED3
        }
    }
}
  void setup(void)
  {
      
      leds_initialize(1, 1, 1, 1, 0);  
      
      gpio_set_direction(&DDRC,6,GPIO_INPUT);
      gpio_set_pin(&PORTC,6);// active low 
    
      led_Set(LED_ZERO);
      led_Set(LED_ONE);
      led_Set(LED_TWO);
      led_Set(LED_THREE);
      


      gpio_set_pin(&TCCR1A,0);//fast pwm
      gpio_set_pin(&TCCR1A,1);  //fast pwm
      gpio_set_pin(&TCCR1B,3);// FASTPWM
       gpio_set_pin(&TCCR1B,4);//FAST PWM
      
      //Ne asiguram ca e oprit
      gpio_reset_pin(&TCCR1B,0);
      gpio_reset_pin(&TCCR1B,1);
      gpio_reset_pin(&TCCR1B,2); 
      
  
      TCNT1 = 0;  
      OCR1A =15625;  
      
    
    gpio_set_pin(&TIMSK1,1); //OCIE1A
      
      
      gpio_set_pin(&SREG, 7);
      gpio_set_pin(&PCMSK2,6);
      gpio_set_pin(&PCICR,2);
  }
   
  void main(void)
  {
      setup();
                                                
      while(1)    
      {
       
            if(PINC & (1<<6))
              {
                gpio_reset_pin(&TCCR1B,0);
                gpio_reset_pin(&TCCR1B,1);
                gpio_reset_pin(&TCCR1B,2); 
                timer_pornit=0;
                perioade=0;
                   led_Set(LED_ZERO);
                led_Set(LED_ONE);
                led_Set(LED_TWO);
                led_Set(LED_THREE);
      
          
              }

        }
      
              
        
  }