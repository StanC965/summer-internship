#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "button.h"

#define BLINK_NUMBER 10

volatile unsigned char counter=0;
//STATES
void led_SW_BLOCKS();
void led_SW_OFF();
void led_SW_BLINK();

//State pointer
void (*statefunc)()=led_SW_OFF;

void led_SW_BLOCKS()
{
led_Set(LED_ONE);
led_Set(LED_TWO);
led_Set(LED_THREE);
led_Reset(LED_ZERO);

if(button_get_press_sw0() )
{
statefunc=led_SW_OFF;
led_Set(LED_ONE);
led_Set(LED_TWO);
led_Set(LED_THREE);
led_Set(LED_ZERO);
return;
}

else 
{
  if(button_get_press_bttn1())
        statefunc=led_SW_BLINK;
  if(button_get_press_bttn2())
        statefunc=led_SW_BLINK;
    
  if(button_get_press_bttn3())
        statefunc=led_SW_BLINK;
  
}
  
}

void led_SW_OFF()
{

if(button_get_press_sw0() )
{
statefunc=led_SW_OFF;
led_Set(LED_ONE);
led_Set(LED_TWO);
led_Set(LED_THREE);
led_Reset(LED_ZERO);
statefunc=led_SW_BLOCKS;
return;
}
else 
{
    if(button_get_press_bttn1())
        led_TOGGLE(LED_ONE);
  if(button_get_press_bttn2())
        led_TOGGLE(LED_TWO);
    
  if(button_get_press_bttn3())
       led_TOGGLE(LED_THREE);

}


return;
}

void led_SW_BLINK()
{
  counter++;
  led_TOGGLE(LED_ZERO);
  if(counter==6)
  {
    counter=0;
  led_Reset(LED_ZERO);
  statefunc=led_SW_BLOCKS;
  }
 return;
}

void task_10ms(void)
{
    
  button_update_all();
      (*statefunc)();
 

}

void task_50ms(void)
{
   
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {}

#endif