#ifndef TIMER_C
#define TIMER_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "timer.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define TIMER_TOIE0_BIT     (0U)
#define TIMER_OCIE0A_BIT    (1U)
#define TIMER_WGM01_BIT     (1U)
#define TIMER_CS_MASK       (0x07U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void timer_init_normal(void)
{
    TCCR0A = 0x00;                             /* normal mode, no OC0x output */
    TCCR0B = 0x00;                             /* WGM02 = 0, timer stopped */
    TIMSK0 |= (1 << TIMER_TOIE0_BIT);          /* overflow interrupt enable */
}

void timer_init_ctc(unsigned char top)
{
    TCCR0A = (1 << TIMER_WGM01_BIT);           /* CTC mode (WGM = 010), no OC0x output */
    TCCR0B = 0x00;                             /* WGM02 = 0, timer stopped */
    OCR0A  = top;                              /* TOP value */
    TIMSK0 |= (1 << TIMER_OCIE0A_BIT);         /* compare match A interrupt enable */
}

void timer_start(unsigned char prescaler)
{
    TCCR0B = (TCCR0B & ~TIMER_CS_MASK) | (prescaler & TIMER_CS_MASK);
}

void timer_stop(void)
{
    TCCR0B &= ~TIMER_CS_MASK;
}

#endif
