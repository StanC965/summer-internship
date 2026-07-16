#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 

volatile unsigned char numar_apasari = 0;
     

#pragma vector = TIMER1_CAPT_vect
__interrupt void input_capture_isr(void)
{
    numar_apasari++;
    
    if (numar_apasari == 4)
    {
        led_Reset(LED_ONE); 
    }
    else if (numar_apasari == 5)
    {
        led_Set(LED_ONE);   
        led_Reset(LED_TWO); 
    }
    else if (numar_apasari == 6)
    {
        led_Set(LED_TWO);    
        led_Reset(LED_THREE); 
    }
    else if (numar_apasari > 6)
    {
        led_Set(LED_THREE); 
        numar_apasari = 0;  
    }
}

void setup(void)
{
   
    leds_initialize(1, 1, 1, 1, 0);  
    
    
    gpio_set_direction(&DDRD, 6, GPIO_INPUT);
    gpio_set_pin(&PORTD, 6);
    
  
    led_Set(LED_ZERO);
    led_Set(LED_ONE);
     led_Set(LED_TWO);
    led_Set(LED_THREE);
    

    gpio_reset_pin(&TCCR1A, 0);
    gpio_reset_pin(&TCCR1A, 1);
    gpio_reset_pin(&TCCR1B, 3); 
      gpio_reset_pin(&TCCR1B, 4); 
    
   
    gpio_set_pin(&TCCR1B, 7);   //reduce din zgomot
    gpio_reset_pin(&TCCR1B, 6); //declansare interrupt
    
   
    gpio_reset_pin(&TCCR1B, 2); 
    gpio_set_pin(&TCCR1B, 1);  
     gpio_set_pin(&TCCR1B, 0);   
    
    
    gpio_set_pin(&TIMSK1, 5); // ICIE1 = 1
    
    
    gpio_set_pin(&SREG, 7);
    gpio_set_pin(&PORTD, 6);
}
   
void main(void)
{
    setup();
                                                
    while(1)    
    {}    
}