#include "timer.h"
#include "led.h"
#include "button.h"
#include "intrinsics.h"

#define TIMER_T0_TARGET_OVERFLOWS    50

volatile unsigned long timer_t0_overflow_count = 0;

const unsigned int timer_prescalers[5] = {1, 8, 64, 256, 1024};
unsigned char current_prescaler_idx = 0;

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

#pragma vector = PCINT2_vect
__interrupt void button_sw0_pcint_isr(void)
{
    if (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN))
    {
        current_prescaler_idx = (current_prescaler_idx + 1) % 5;
        
        timer_t0_overflow_count = 0;
        
        timer_start_t0(timer_prescalers[current_prescaler_idx]);
    }
}

void init_system(void)
{
    gpio_init();
    timer_init();   
    led_init();
    button_init();
    
    __enable_interrupt();
}

void main(void)
{
    init_system();
  
    timer_start_t0(timer_prescalers[current_prescaler_idx]);
    
    while (1)
    {
        
    }
}