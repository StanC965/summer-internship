#ifndef TIMER_C
#define TIMER_C

#include "timer.h"

void timer_init(void)
{
    TCCR0A = 0x00;
    
    TIMSK0 |= (1 << TIMER_TO_OVERFLOW_INT);
    
    timer_stop_t0();
}

void timer_start_t0(void)
{
    TCCR0B = TIMER_T0_STOPPED;
    
    TCCR0B |= TIMER_T0_NO_PRESCALE;
}

void timer_stop_t0(void)
{
    TCCR0B = TIMER_T0_STOPPED;
}

#endif