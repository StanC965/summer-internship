#ifndef TIMER_C
#define TIMER_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <iom324pb.h>
#include "timer.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void timer0_init(void)
{
    timer0_enable_peripheral_clock();
    timer0_select_normal_mode();
    timer0_configure_control_settings();
}

void timer0_init_ctc(void)
{
    timer0_enable_peripheral_clock();
    timer0_select_ctc_mode();
    timer0_configure_ctc_settings();
}

void timer0_enable_peripheral_clock(void)
{

    PRR0 &= ~BIT_MASK(PRTIM0);
}

void timer0_select_normal_mode(void)
{
    TCCR0A = 0x00;
}

void timer0_select_ctc_mode(void)
{
    TCCR0A = (BIT_MASK(WGM01)) | (BIT_MASK(1 << COM0A0));
}

void timer0_configure_control_settings(void)
{
    TCNT0 = TIMER0_PRELOAD_VALUE;
    timer0_enable_overflow_interrupt();
}

void timer0_configure_ctc_settings(void)
{
    OCR0A = TIMER0_CTC_TARGET;
    TCNT0 = 0x00;
    timer0_enable_compare_a_interrupt();
}

void timer0_enable_overflow_interrupt(void)
{
    TIMSK0 |= BIT_MASK(TOIE0);
}

void timer0_enable_compare_a_interrupt(void)
{
    TIMSK0 |= BIT_MASK(OCIE0A);
}

void timer0_start_no_prescaling(void)
{
    TCCR0B &= ~TCCR0B_CS_MASK;
    TCCR0B |= (TIMER0_PRESCALER_NO_DIVISION & TCCR0B_CS_MASK);
}

void timer0_start_prescaler_64(void)
{
    TCCR0B &= ~TCCR0B_CS_MASK;
    TCCR0B |= (TIMER0_PRESCALER_64 & TCCR0B_CS_MASK);
}

void timer1_init_10ms(void)
{
    timer1_enable_peripheral_clock();

    TCCR1A = 0x00; 
    TCCR1B = BIT_MASK(WGM12);  

    OCR1A = TIMER1_10MS_OCR1A_VALUE; 

    TCNT1 = 0x0000;
    
    timer1_enable_compare_a_interrupt();
    
    TCCR1B |= BIT_MASK(CS11); 
}

void timer1_init_ctc_100ms(void)
{
    timer1_enable_peripheral_clock();

    TCCR1A = BIT_MASK(COM1A0); 
    TCCR1B = BIT_MASK(WGM12);  

    OCR1A = TIMER1_100MS_OCR1A_VALUE; 

    TCCR1B |= BIT_MASK(CS11); 
}

void timer1_enable_peripheral_clock(void)
{

    PRR0 &= ~BIT_MASK(PRTIM1);
}

void timer1_enable_compare_a_interrupt(void)
{
    TIMSK1 |= BIT_MASK(OCIE1A);
}

void timer1_airbag_configure(void)
{
    timer1_enable_peripheral_clock();

    TCCR1A = BIT_MASK(COM1A1);
    TCCR1B = BIT_MASK(WGM12);

    OCR1A = TIMER1_AIRBAG_OCR1A_VALUE ;
}

void timer1_airbag_start(void)
{
    TCNT1 = 0x0000;
    TCCR1B |= BIT_MASK(CS10);
}

#endif /* TIMER_C */
