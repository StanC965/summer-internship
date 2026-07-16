#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#define PHASE_0_LIMIT       100  
#define PHASE_1_LIMIT       150  
#define PHASE_2_LIMIT       250  
#define PHASE_3_LIMIT       100

volatile unsigned int compare_match_count = 0;
volatile unsigned char current_phase = 0;

#pragma vector = TIMER0_COMPA_vect
__interrupt void timer0_compare_a_isr(void)
{
    compare_match_count++;
    
    switch (current_phase)
    {
        case 0:
            if (compare_match_count >= PHASE_0_LIMIT)
            {
                current_phase = 1;         
                compare_match_count = 0;  
                led_power_on(LED_LED0_PORT, LED_LED0_PIN); 
            }
            break;

        case 1:
            if (compare_match_count >= PHASE_1_LIMIT)
            {
                current_phase = 2;         
                compare_match_count = 0;   
                led_power_off(LED_LED0_PORT, LED_LED0_PIN); 
            }
            break;

        case 2:
            if (compare_match_count >= PHASE_2_LIMIT)
            {
                current_phase = 3;         
                compare_match_count = 0;  
                led_power_on(LED_LED0_PORT, LED_LED0_PIN); 
            }
            break;

        case 3:
            if (compare_match_count >= PHASE_3_LIMIT)
            {
                current_phase = 0;      
                compare_match_count = 0;   
                led_power_off(LED_LED0_PORT, LED_LED0_PIN); 
            }
            break;

        default:
            current_phase = 0;
            compare_match_count = 0;
            break;
    }
}

void init_system(void)
{
    gpio_init();
    timer_init();   
    led_init();
    
    __enable_interrupt();
}

void main(void)
{
    init_system();
    
    timer_init_ctc_t0(249);
    
    timer_start_t0(8);
  
    
    while (1)
    {
        
    }
}