#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#pragma vector = TIMER0_COMPA_vect
__interrupt void timer0_compare_a_isr(void)
{
    led_toggle(LED_LED0_PORT, LED_LED0_PIN);
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
    
    timer_init_ctc_t0(127);
    
    timer_start_t0(256);
  
    
    while (1)
    {
        
    }
}