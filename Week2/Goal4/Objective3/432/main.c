#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#pragma vector = TIMER0_COMPA_vect
__interrupt void timer0_compare_a_isr(void)
{
    if (PINB & (1 << LED_IO_LED_PIN))
    {
        led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    }
    else
    {
        led_power_on(LED_LED0_PORT, LED_LED0_PIN); 
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
    
    timer_init_ctc_t0(127);
    
    timer_start_t0(1024);
  
    
    while (1)
    {
        
    }
}