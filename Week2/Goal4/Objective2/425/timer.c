#ifndef TIMER_C
#define TIMER_C

#include "timer.h"

void timer_init(void)
{
    TCCR0A = 0x00;
    
    TIMSK0 |= (1 << TIMER_TO_OVERFLOW_INT);
    
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

#endif