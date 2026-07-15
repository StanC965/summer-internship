  #include "led.h"
  #include "gpio.h"
  #include "iom324pb.h"

  volatile unsigned char overflow_counter = 0;
  volatile unsigned char cycle = 1;

  #pragma vector = PCINT2_vect
  __interrupt void my_routine(void)
  {
    if(!(PINC&(1<<6)))
    {
    cycle++;
    if(cycle>5)
      cycle=1;
    }
  }


  #pragma vector=TIMER0_OVF_vect
  __interrupt void aprindeLed(void)
  {
      overflow_counter++;
  }

  void setup(void)
  {
    leds_initialize(1,0,0,0,0);
    led_Set(LED_ZERO);
    //PRR0 &= ~(1 << PRR0_PRTIM0);

    TCCR0A = 0;
    TCCR0B = 0;

    TIMSK0 |= (1 << TIMSK0_TOIE0);//interrupt
    TCNT0 = 0;

    gpio_set_direction(&DDRC,6,GPIO_INPUT);
    gpio_set_pin(&PORTC,6);
    

   
    PCICR |= (1 << 2);    //PORTC interrupts
    PCMSK2 |= (1 << 6); //PC6 adica PCINT22

    gpio_set_pin(&SREG,7);
   
  }

  void main(void)
  {
    _Bool on=0;
    unsigned char diferenta=cycle;
      setup();

      while(1)
      {
            if(cycle!=diferenta)
             {
               diferenta=cycle;
                  switch(cycle)
                  {
                      
                      case 1:TCCR0B=1 ;break;
                      case 2:TCCR0B=2 ;break;
                      case 3:TCCR0B=3 ;break;
                      case 4:TCCR0B=4 ;break;
                      case 5:TCCR0B=5 ;break;
                  }
        
               
             }
             if(overflow_counter >= 4)
                   {
               
                      overflow_counter = 0;
                    if(on)
                      led_Set(LED_ZERO);
                    else
                      led_Reset(LED_ZERO);
                      on=!on;
                  }
      }
      
  }


