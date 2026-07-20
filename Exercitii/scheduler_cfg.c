#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "button.h"

#define BLINK_NUMBER 10

static _Bool sw0_block = 0;
static unsigned char led0_blink_counter = 0;

void task_10ms(void)
{
    // citeste siaplicadebounce la toate butoannele
  button_update_all();

 
    if (button_get_press_sw0()) 
    {
        sw0_block = !sw0_block; // Toggle sw0
        
        if (sw0_block) {
           
            
            led_Reset(LED_ZERO); 
            
            
            led_Set(LED_ONE);
            led_Set(LED_TWO);
            led_Set(LED_THREE);
        } else {
            led_Set(LED_ZERO); 
            led0_blink_counter = 0; 
        }
    }

   
    if (button_get_press_bttn1()) 
    {
        if (sw0_block) led0_blink_counter = BLINK_NUMBER; // blink rapid
        else led_TOGGLE(LED_ONE); 
    }
    
    if (button_get_press_bttn2()) 
    {
        if (sw0_block) led0_blink_counter = BLINK_NUMBER; 
        else led_TOGGLE(LED_TWO); 
    }
    
    if (button_get_press_bttn3()) 
    {
        if (sw0_block) led0_blink_counter = BLINK_NUMBER; 
        else led_TOGGLE(LED_THREE); 
    }
}

void task_50ms(void)
{
   
    if (sw0_block && led0_blink_counter > 0) 
    {
        led_TOGGLE(LED_ZERO);
        led0_blink_counter--;
        
       
        if (led0_blink_counter == 0) {
            led_Reset(LED_ZERO);
        }
    }
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {}

#endif