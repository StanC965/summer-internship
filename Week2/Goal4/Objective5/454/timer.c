#ifndef TIMER_C
#define TIMER_C

#include "timer.h"

void timer_init(void)
{
    //timer0
    TCCR0A = 0x00;
    TIMSK0 |= (1 << TIMER_T0_OVERFLOW_INT);
    timer_stop_t0();
    
    //timer1
    TCCR1A = 0x00; // Normal port operation, Normal WGM mode
    TCCR1B = 0x00; // Stopped initially
    TCNT1  = 0x0000; // Clear the 16-bit counter register
}

void timer_init_ctc_t0(unsigned char compare_value)
{
    TCCR0A = (1 << TIMER_T0_CTC_MODE); 
        
    OCR0A = compare_value;
    
    TIMSK0 &= ~(1 << TIMER_T0_OVERFLOW_INT);
    TIMSK0 |= (1 << TIMER_T0_A_COMP_INT);
    
    TCNT0 = 0;
    
    timer_stop_t0();
}    

void timer_start_t0(unsigned int division_value)
{
    unsigned char reg_bits;

    switch (division_value)
    {
        case 1:
            reg_bits = 0x01; 
            break;
        case 8:
            reg_bits = 0x02; 
            break;
        case 64:
            reg_bits = 0x03; 
            break;
        case 256:
            reg_bits = 0x04; 
            break;
        case 1024:
            reg_bits = 0x05;
            break;
        default:
            reg_bits = 0x01;
            break;
    }

    TCCR0B &= ~0x07;
    TCCR0B |= reg_bits;
}

void timer_stop_t0(void)
{
    TCCR0B = TIMER_T0_STOPPED;
}

void timer_start_t1(unsigned int division_value)
{
    unsigned char reg_bits;

    TCNT1 = 0x0000;

    switch (division_value)
    {
        case 1:
            reg_bits = 0x01; 
            break;
        case 8:
            reg_bits = 0x02; 
            break;
        case 64:
            reg_bits = 0x03; 
            break;
        case 256:
            reg_bits = 0x04; 
            break;
        case 1024:
            reg_bits = 0x05;
            break;
        default:
            reg_bits = 0x01;
            break;
    }

    TCCR1B &= ~0x07;
    TCCR1B |= reg_bits;
}

void timer_stop_t1(void)
{
    TCCR1B &= ~0x07;
}

void timer_t1_init_icu(void)
{
    DDRD |= (1 << 6);
    PORTD |= (1 << 6);
  
    TCCR1A = 0x00; 
    TCCR1B = 0x00;

    // ICES1 = 0: Capture on falling edge
    // ICNC1 = 1: Enable Noise Canceler
    TCCR1B &= ~(1 << TIMER_ICES1); 
    TCCR1B |= (1 << TIMER_ICNC1);

    TCNT1 = 0x0000;

    // Enable the Input Capture Interrupt in TIMSK1
    TIMSK1 |= (1 << TIMER_ICIE1); 
}

#endif