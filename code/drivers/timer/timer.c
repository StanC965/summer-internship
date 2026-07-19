#ifndef TIMER_C
#define TIMER_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "timer.h"
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void timer_init(void)
{
    timer_enable_peripheral_clock();
    timer_select_normal_mode();
    timer_configure_control_settings();
}

void timer_enable_peripheral_clock(void)
{
    PRR0 &= ~BIT_MASK(PRTIM0);
}

void timer_select_normal_mode(void)
{
    TCCR0A = 0x00;
}

void timer_configure_control_settings(void)
{
    //TCCR0B &= ~(TCCR0B_CS_MASK);
    TCNT0 = TIMER0_PRELOAD_VALUE;
    timer_enable_overflow_interrupt();
}

void timer_enable_overflow_interrupt()
{
    TIMSK0 |= (1 << TOIE0);
}

void timer_start_no_prescaling(void)
{
    TCCR0B &= ~TCCR0B_CS_MASK;
    TCCR0B |= (TIMER_PRESCALER_NO_DIVISION & TCCR0B_CS_MASK);
}

void timer_start_prescaler_64(void)
{
    TCCR0B &= ~TCCR0B_CS_MASK;
    TCCR0B |= (TIMER_PRESCALER_64 & TCCR0B_CS_MASK);
}

#endif /* TIMER_C */
