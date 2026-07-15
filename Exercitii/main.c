#include "led.h"
#include "gpio.h"
#include "iom324pb.h"

volatile unsigned char overflow_counter = 0;

#pragma vector=TIMER0_OVF_vect
__interrupt void aprindeLed(void)
{
    overflow_counter++;
}

void setup(void)
{
    leds_initialize(1,0,0,0,0);
    led_Set(LED_ZERO);

   

    TCCR0A = 0;
    TCCR0B = 0;

    gpio_set_pin(&TCCR0B,0);
    //gpio_reset_pin(&TCCR0B,1);
    gpio_set_pin(&TCCR0B,2);      // prescaler 1024

    TIMSK0 |= (1 << TIMSK0_TOIE0);

    TCNT0 = 0;

    gpio_set_pin(&SREG,7);
}

void main(void)
{
  _Bool on=0;
    setup();

    while(1)
    {
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