#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#define TARGET_COMPARE_MATCHES    100

volatile unsigned char compare_match_count = 0;

#pragma vector = TIMER0_COMPA_vect
__interrupt void timer0_compare_a_isr(void)
{
    compare_match_count++;
    
    if (compare_match_count >= TARGET_COMPARE_MATCHES)
    {
        led_toggle(LED_LED0_PORT, LED_LED0_PIN);
        compare_match_count = 0;
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