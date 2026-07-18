#ifndef LED_C
#define LED_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "led.h"
#include "gpio.h"       
#include "iom324pb.h"  




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void leds_initialize(_Bool led0, _Bool led1, _Bool led2, _Bool led3, _Bool led4)
{       
    if(led0)
    {
        gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);
        gpio_reset_pin(&PORTC, 7);
    }
    if(led1)
    {
        gpio_set_direction(&DDRD, 4, GPIO_OUTPUT);
        gpio_reset_pin(&PORTD, 4);
    }
    if(led2)
    {
        gpio_set_direction(&DDRD, 5, GPIO_OUTPUT);
        gpio_reset_pin(&PORTD, 5);
    }
    if(led3)
    {
        gpio_set_direction(&DDRA, 3, GPIO_OUTPUT);
        gpio_reset_pin(&PORTA, 3);
    }
    if(led4)
    {
        gpio_set_direction(&DDRB, 3, GPIO_OUTPUT);
        gpio_reset_pin(&PORTB, 3);
    }
}

void led_Set(unsigned char Led_id)
{ 
    switch(Led_id)
    {
        case LED_ZERO:  gpio_set_pin(&PORTC, 7); break;
        case LED_ONE:   gpio_set_pin(&PORTD, 5); break;
        case LED_TWO:   gpio_set_pin(&PORTD, 4); break;
        case LED_THREE: gpio_set_pin(&PORTA, 3); break;
        case LED_FOUR:  gpio_set_pin(&PORTB, 3); break;
        default: break;
    }
}

void led_Reset(unsigned char Led_id)
{ 
    switch(Led_id)
    {
        case LED_ZERO:  gpio_reset_pin(&PORTC, 7); break;
        case LED_ONE:   gpio_reset_pin(&PORTD, 5); break;
        case LED_TWO:   gpio_reset_pin(&PORTD, 4); break;
        case LED_THREE: gpio_reset_pin(&PORTA, 3); break;
        case LED_FOUR:  gpio_reset_pin(&PORTB, 3); break;
        default: break;
    }
}

void led_TOGGLE(unsigned char Led_id)
{ 
    switch(Led_id)
    {
        case LED_ZERO:  gpio_toggle_pin(&PORTC, 7); break;
        case LED_ONE:   gpio_toggle_pin(&PORTD, 5); break;
        case LED_TWO:   gpio_toggle_pin(&PORTD, 4); break;
        case LED_THREE: gpio_toggle_pin(&PORTA, 3); break;
        case LED_FOUR:  gpio_toggle_pin(&PORTB, 3); break;
        default: break;
    }
}

void led_TEST_Fast(unsigned char Led_id)
{
  
    int counter=0;
    gpio_Timer1_start(0.09,8);
  
    while(1)
    { 
     
          if(TCNT1>=OCR1A)
          {
   
              TCNT1=0;
              led_TOGGLE(Led_id); 
              counter++; 
   
          }
 
          if(counter==12)
          {
   
              gpio_Timer1_stop();
              return;
 
          }
 
      }
  
 
 }
        
void led_TEST_Slow(unsigned char Led_id)
 {
   
      int counter=0; 
      gpio_Timer1_start(0.25,8);
  
      while(1)
      {
    
          if(TCNT1>=OCR1A)
          {
   
              TCNT1=0;
              led_TOGGLE(Led_id); 
              counter++; 
 
          }
 
          if(counter==4)
          { 
   
              gpio_Timer1_stop();
              return;
 
          }
 
      }
  
 

 }


  void led_TEST_Blink(unsigned char Led_id, float secunde, int limite_clipiri)
{
    int counter = 0;
    gpio_Timer1_start(secunde, 8);
    
    while(1)
    { 
      
        if(TCNT1 >= OCR1A)
        {
            TCNT1 = 0;
            led_TOGGLE(Led_id); 
            counter++; 
        }
        
        if(counter == limite_clipiri)
        {  
            gpio_Timer1_stop();
            return;
        }
    }
}
        
#endif