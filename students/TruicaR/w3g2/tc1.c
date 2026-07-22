#include "iom324pb.h"
#include "tc1.h"
#include "scheduler.h"

void tc1_systick_init(void)
{
    TCCR1B_WGM13 = 0;
    TCCR1B_WGM12 = 1;   
    TCCR1A_WGM11 = 0;
    TCCR1A_WGM10 = 0;

    OCR1A = 9999;       

    TIMSK1_OCIE1A = 1;

    TCCR1B_CS12 = 0;
    TCCR1B_CS11 = 0;
    TCCR1B_CS10 = 1;   
}

#pragma vector = TIMER1_COMPA_vect
__interrupt void tc1_compa_isr(void)
{
    scheduler_flags_management(); 
}