  #include "led.h"
  #include "gpio.h"
  #include "iom324pb.h"

  volatile unsigned char overflow_counter = 0;
  volatile _Bool start = 1;

  #pragma vector = PCINT2_vect
  __interrupt void my_routine(void)
  {
    if(!(PINC&(1<<6)))
    {
    start=!start;
    }
  
  }


  #pragma vector=TIMER0_OVF_vect
  __interrupt void aprindeLed(void)
  {
      overflow_counter++;
  }

void setup(void)
{
    
    leds_initialize(1, 1, 1, 1, 1);  //initializam cele 3 led-uri  in manual spune ca sunt active low 

    led_Set(LED_ONE);
    led_Set(LED_TWO);        //le punem pe high(le stingem)
    led_Set(LED_THREE);
    led_Set(LED_ZERO);
    led_Set(LED_FOUR);

    ///////DIRECTIE BUTOANE/////////   
 
    gpio_set_direction(&DDRC,6, GPIO_INPUT); 
    gpio_set_pin(&PORTC, 6);



       gpio_set_pin(&PORTC, 1);
       gpio_set_pin(&PORTA, 1);            //fara asta led-urile se comporta instabil
       gpio_set_pin(&PORTA, 0);
       gpio_set_pin(&PORTC, 7);
       gpio_set_pin(&PORTB, 3);

     ////////INTRERUPERI BUTOANE/////////

    
     gpio_set_pin(&PCMSK2, 6); 

     //////INTRERUPERI GLOBALE///////
     gpio_set_pin(&SREG, 7);
     
    TCCR0A = 0;
    TCCR0B = 0;

    TIMSK0 |= (1 << TIMSK0_TOIE0);
    TCNT0 = 0;

   
    

    PCICR |= (1 << 2);    //PORTC interrupts
    PCMSK2 |= (1 << 6); //PC6 adica PCINT22
}


 int seq[5]={LED_ZERO,LED_ONE,LED_TWO,LED_THREE,LED_FOUR};
  _Bool on=0;
  void main(void)
  {
 
      setup();
      int i=0;
      while(1)
      {
         if(start)
         {
              TCCR0B=5;
              if(overflow_counter >= 4)
          {
              overflow_counter = 0;
              if(on)
                  led_Reset(seq[i++]);
             
              on = !on;
              if(i==5)
              {
                
                  i=0;
              
                  led_Set(LED_ONE);
                  led_Set(LED_TWO);
                  led_Set(LED_THREE);
                  led_Set(LED_ZERO);
                  led_Set(LED_FOUR);
                
                
               }
              
            }
            
          }
          else
            {
                i=0;

              
                led_Set(LED_ONE);
                led_Set(LED_TWO);
                led_Set(LED_THREE);
                led_Set(LED_ZERO);
                led_Set(LED_FOUR);

            }
        }
      
  }
  
 