#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "button.h"
#include "usart.h"

#define BLINK_NUMBER 10






static _Bool sw0_block = 0;
static unsigned char led0_blink_counter = 0;

void task_10ms(void)
{
    button_update_all();

    if (button_get_press_sw0()) 
    {
        sw0_block = !sw0_block; 
        
        if (sw0_block) {
            
            USART0_Transmit(CMD_LED0_OFF); 
            USART0_Transmit(CMD_LED1_ON);
            USART0_Transmit(CMD_LED2_ON);
            USART0_Transmit(CMD_LED3_ON);
        } else {
            USART0_Transmit(CMD_LED0_ON); 
            led0_blink_counter = 0; 
        }
    }
   
    if (button_get_press_bttn1()) 
    {
        if (sw0_block) led0_blink_counter = BLINK_NUMBER; 
        else USART0_Transmit(CMD_LED1_TOGGLE); 
    }
    
    if (button_get_press_bttn2()) 
    {
        if (sw0_block) led0_blink_counter = BLINK_NUMBER; 
        else USART0_Transmit(CMD_LED2_TOGGLE); 
    }
    
    if (button_get_press_bttn3()) 
    {
        if (sw0_block) led0_blink_counter = BLINK_NUMBER; 
        else USART0_Transmit(CMD_LED3_TOGGLE); 
    }
}

void task_50ms(void)
{
    if (sw0_block && led0_blink_counter > 0) 
    {
        USART0_Transmit(CMD_LED0_TOGGLE);
        led0_blink_counter--;
        
        if (led0_blink_counter == 0) {
            USART0_Transmit(CMD_LED0_OFF); 
        }
    }
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {}

#endif