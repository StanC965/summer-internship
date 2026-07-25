#ifndef TIMER_C
#define TIMER_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "timer.h"
#include "scheduler.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define TIMER_TOIE0_BIT     (0U)
#define TIMER_OCIE0A_BIT    (1U)
#define TIMER_WGM01_BIT     (1U)
#define TIMER_COM0A0_BIT    (6U)
#define TIMER_CS_MASK       (0x07U)

#define TIMER_SYSTICK_TOP   (1249U)   /* (1249+1)*8us = 10.000ms @1MHz, prescaler 8 */
#define TIMER_WGM12_BIT     (3U)
#define TIMER_CS11_BIT      (1U)
#define TIMER_OCIE1A_BIT    (1U) 

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void timer_init_normal(void)
{
    TCCR0A = 0x00;                             /* normal mode, no OC0x output */
    TCCR0B = 0x00;                             /* WGM02 = 0, timer stopped */
    TCNT0  = 0x00;
    TIMSK0 |= (1 << TIMER_TOIE0_BIT);          /* overflow interrupt enable */
}

void timer_init_ctc(unsigned char top)
{
    TCCR0A = (1 << TIMER_WGM01_BIT);           /* CTC mode (WGM = 010), no OC0x output */
    TCCR0B = 0x00;                             /* WGM02 = 0, timer stopped */
    TCNT0  = 0x00;
    OCR0A  = top;                              /* TOP value */
    TIMSK0 |= (1 << TIMER_OCIE0A_BIT);         /* compare match A interrupt enable */
}

void timer_ctc_enable_oc0a_toggle(void)
{
    TCCR0A |= (1 << TIMER_COM0A0_BIT);
}

void timer_start(unsigned char prescaler)
{
    TCCR0B = (TCCR0B & ~TIMER_CS_MASK) | (prescaler & TIMER_CS_MASK);
}

void timer_stop(void)
{
    TCCR0B &= ~TIMER_CS_MASK;
}

void timer_systick_init(void)
{
    TCCR1A = 0x00;                             /* CTC (WGM13:0 = 0100), no OC1x output */
    TCCR1B = (1 << TIMER_WGM12_BIT);           /* WGM12 = 1, timer stopped */
    TCNT1  = 0x0000;
    OCR1A  = TIMER_SYSTICK_TOP;                /* TOP -> 10ms */
    TIMSK1 |= (1 << TIMER_OCIE1A_BIT);         /* compare match A interrupt enable */
    TCCR1B |= (1 << TIMER_CS11_BIT);           /* prescaler 8 -> starts counting (written last) */
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void timer_systick_isr(void)
{
    scheduler_flags_management();
}

#endif
