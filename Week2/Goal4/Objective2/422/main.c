#include "timer.h"
#include "intrinsics.h"

volatile unsigned long timer_t0_overflow_count = 0;


#pragma vector = TIMER0_OVF_vect
__interrupt void timer_t0_overflow_isr(void)
{
    timer_t0_overflow_count++;
    
    if (timer_t0_overflow_count >= 10000)
    {
        timer_t0_overflow_count = 0;
    }
}

void init_system(void)
{
    timer_init();   
    
    __enable_interrupt();
}

void main(void)
{
    init_system();
  
    timer_start_t0();
    
    while (1)
    {
        
    }
}