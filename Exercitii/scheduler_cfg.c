#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"       
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "adc.h"

#ifdef ADC_USE_8_BIT_RESOLUTION
    #define THRESHOLD_1 64
    #define THRESHOLD_2 128
    #define THRESHOLD_3 192
#else
    #define THRESHOLD_1 255    //bloc decizie rezolutiede 8 sau 10
    #define THRESHOLD_2 511
    #define THRESHOLD_3 767
#endif
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/




void task_10ms(void)
{
  
void task_10ms(void)
{
   
    unsigned char sw0_status = button_read_sw0_safe();
    
 
    if(sw0_status == 1)
    {

    }
}

  
}

void task_50ms(void)
{
    
}

void task_100ms(void)
{
    
    adc_read_and_update();
    
 
    unsigned short current_light = adc_get_data();
    

    if (current_light < THRESHOLD_1) 
    {
        led_Set(LED_ONE);
        led_Set(LED_TWO);
        led_Set(LED_THREE);
    }
    else if (current_light < THRESHOLD_2) 
    {
        led_Reset(LED_ONE);
        led_Set(LED_TWO);
        led_Set(LED_THREE);
    }
    else if (current_light < THRESHOLD_3) 
    {
        led_Reset(LED_ONE);
        led_Reset(LED_TWO);
        led_Set(LED_THREE);
    }
    else 
    {
        led_Reset(LED_ONE);
        led_Reset(LED_TWO);
        led_Reset(LED_THREE);
    }
    
  
    adc_start_conversie();
}

void task_500ms(void)
{
   
}

void task_1000ms(void)
{
   
}
            
       


#endif

