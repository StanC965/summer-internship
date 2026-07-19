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

void timer_init_ctc(void)
{
    timer_enable_peripheral_clock();
    timer_select_ctc_mode();
    timer_configure_ctc_settings();
}

void timer1_init_ctc_100ms(void)
{
    timer1_enable_peripheral_clock();

    TCCR1A = (1 << COM1A0);      // toggle OC1A on compare match, WGM11:10 = 00
    TCCR1B = (1 << WGM12);       // CTC mode, OCR1A as TOP (WGM13:12 = 01)

    OCR1A = 6249;                // (OCR1A+1) * 8us = 50ms half-period -> 100ms full period

    TCCR1B |= (1 << CS11);       // prescaler = 8 (CS12:10 = 010)
}


void timer_enable_peripheral_clock(void)
{

    PRR0 &= ~BIT_MASK(PRTIM0);
}

void timer1_enable_peripheral_clock(void)
{

    PRR0 &= ~BIT_MASK(PRTIM1);
}

void timer_select_normal_mode(void)
{
    TCCR0A = 0x00;
}

void timer_select_ctc_mode(void)
{
    TCCR0A = (1 << WGM01) | (1 << COM0A0);
}

void timer_configure_control_settings(void)
{
    // TCCR0B &= ~TCCR0B_CS_MASK;
    TCNT0 = TIMER0_PRELOAD_VALUE;
    timer_enable_overflow_interrupt();
}

void timer_configure_ctc_settings(void)
{
    OCR0A = TIMER0_CTC_TARGET;
    TCNT0 = 0x00;
    timer_enable_compare_a_interrupt();
}

void timer_enable_overflow_interrupt(void)
{
    TIMSK0 |= (1 << TOIE0);
}

void timer_enable_compare_a_interrupt(void)
{
    TIMSK0 |= (1 << OCIE0A);
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
