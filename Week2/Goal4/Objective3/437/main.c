#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#define MATCHES_STATE_HIGH       350  
#define MATCHES_STATE_LOW        150

volatile unsigned int compare_match_count = 0;
volatile unsigned char current_logical_state = 1;

#pragma vector = TIMER0_COMPA_vect
__interrupt void timer0_compare_a_isr(void)
{
    compare_match_count++;
    
    if (current_logical_state == 1)
    {
        if (compare_match_count >= MATCHES_STATE_HIGH)
        {
            current_logical_state = 0;  
            compare_match_count = 0;   
            
            led_power_on(LED_LED0_PORT, LED_LED0_PIN); 
        }
    }
    else 
    {
        if (compare_match_count >= MATCHES_STATE_LOW)
        {
            current_logical_state = 1;  
            compare_match_count = 0;  
            
            led_power_off(LED_LED0_PORT, LED_LED0_PIN); 
        }
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