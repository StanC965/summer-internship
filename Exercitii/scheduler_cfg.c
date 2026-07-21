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
#include "button.h"
#include "pwm.h"

#ifdef ADC_USE_8_BIT_RESOLUTION
    #define THRESHOLD_1 64
    #define THRESHOLD_2 128
    #define THRESHOLD_3 192
    #define DAY_LIGHT   102
#else
    #define THRESHOLD_1 255    //bloc decizie rezolutiede 8 sau 10
    #define THRESHOLD_2 511
    #define THRESHOLD_3 767
    #define DAY_LIGHT   410
#endif





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

volatile _Bool day=1;
volatile _Bool headlights=0;
static const unsigned char anim_night[11] = {0, 1, 1, 3, 7, 16, 16, 14, 12, 10, 8};
static const unsigned char anim_day[11]   = {0, 4, 7, 16, 44, 59, 59, 55, 50, 45, 40};
static int system_state = 0;       
static int anim_step = 0;
static _Bool animation_request = 0;
static int current_anim_mode = 0; 



void task_10ms(void)
{
    button_update_all();
    
    if (button_get_press_sw0())
    {
        led_TOGGLE(LED_ZERO);
        headlights = !headlights;
        
        if (headlights)
        {
            //request de animatie 
            animation_request = 1; 
        }
        else
        {
            
            system_state = 0;
            pwm_dc(0);
        }
    }
}
void task_50ms(void)
{
    if(headlights)
    {
        adc_read_and_update();

        int target_pwm = 0;
        unsigned short current_light = adc_get_data();
        
        unsigned short light_percent = ((unsigned long)current_light * 100) / 1023; 

        if (light_percent <= 20)      target_pwm = 15;
        else if (light_percent <= 40) target_pwm = 20;
        else if (light_percent <= 50) target_pwm = 42;
        else if (light_percent <= 70) target_pwm = 80;   //determinare luminozitate 
        else                          target_pwm = 90;
        
        if (animation_request)
        {
            animation_request = 0;
          
            current_anim_mode = (light_percent <= 40) ? 0 : 1; 
            system_state = 1;                              
            anim_step = 0;                                 
        }

    
        if (current_light < THRESHOLD_1) 
        {
            led_Set(LED_ONE); led_Set(LED_TWO); led_Set(LED_THREE);
        }
        else if (current_light < THRESHOLD_2) 
        {
            led_Reset(LED_ONE); led_Set(LED_TWO); led_Set(LED_THREE);
        }
        else if (current_light < THRESHOLD_3) 
        {
            led_Reset(LED_ONE); led_Reset(LED_TWO); led_Set(LED_THREE);
        }
        else 
        {
            led_Reset(LED_ONE); led_Reset(LED_TWO); led_Reset(LED_THREE);
        }

        day = (current_light > DAY_LIGHT) ? 1 : 0; //verifica daca e zi sau noapte 
        adc_start_conversie();
        
        if (system_state == 2)
        {
            pwm_dc(target_pwm);     //daca e zi
        }
    }
    else
    {
        led_Set(LED_ONE);
        led_Set(LED_TWO);
        led_Set(LED_THREE);
        pwm_dc(0); 
    }
}


void task_100ms(void)
{
    static unsigned char tick_200ms = 0;

    if (headlights && system_state == 1)
    {
        tick_200ms++;

        if (tick_200ms >= 2)
        {
            tick_200ms = 0;

            
            if (current_anim_mode == 0)
            {
                pwm_dc(anim_night[anim_step]);
            }
            else                                //animatie de zi sau noapte
            {
                pwm_dc(anim_day[anim_step]);   
            }

            anim_step++;

            if (anim_step >= 11)
            {
                system_state = 2; 
            }
        }
    }
    else
    {
        tick_200ms = 0;
    }
}
void task_500ms(void)
{
   
}

void task_1000ms(void)
{
   
}
            
       


#endif


/*

Time [sec]	Entry phase Night mode RELATIVE steps	Entry phase Day mode RELATIVE steps
0	0	0
0.2	1	4
0.4	1	7
0.6	3	16
0.8	7	44
1	16	59
1.2	16	59
1.4	14	55
1.6	12	50
1.8	10	45
2	8	40
Success in winning the project !!! Enjoy your 22h flight and don't forget to come


*/
