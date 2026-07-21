#include "timer.h"
#include "led.h"
#include "intrinsics.h"

volatile unsigned long timer_t0_overflow_count = 0;

#define TIMER_T0_TARGET_OVERFLOWS    15

#pragma vector = TIMER0_OVF_vect
__interrupt void timer_t0_overflow_isr(void)
{
    timer_t0_overflow_count++;
    
    if (timer_t0_overflow_count >= TIMER_T0_TARGET_OVERFLOWS)
    {
        led_toggle(LED_LED0_PORT, LED_LED0_PIN);
        timer_t0_overflow_count = 0;
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
  
    timer_start_t0(256);
    
    while (1)
    {
        
    }
}