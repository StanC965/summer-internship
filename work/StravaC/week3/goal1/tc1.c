#include "iom324pb.h"

#include "scheduler.h"
#include "tc1.h"

/*
TC1 scheduler configuration:

CPU frequency = 16 MHz
Prescaler = 8
Scheduler tick = 10 ms

OCR1A =
    (16000000 * 0.010 / 8) - 1

OCR1A =
    19999
*/

#define TC1_ZERO                         (0U)
#define TC1_ONE                          (1U)

#define TC1_COMPARE_A_VALUE              (19999U)

#define TC1_WGM12_BIT                    (3U)

#define TC1_CS12_BIT                     (2U)
#define TC1_CS11_BIT                     (1U)
#define TC1_CS10_BIT                     (0U)

#define TC1_OCIE1A_BIT                   (1U)
#define TC1_OCF1A_BIT                    (1U)

#define TC1_CLOCK_SELECT_MASK            \
    ((TC1_ONE << TC1_CS12_BIT) |         \
     (TC1_ONE << TC1_CS11_BIT) |         \
     (TC1_ONE << TC1_CS10_BIT))

#define TC1_PRESCALER_8_MASK             \
    (TC1_ONE << TC1_CS11_BIT)

void tc1_init(void)
{
    TCCR1A = TC1_ZERO;
    TCCR1B = TC1_ZERO;

    TCNT1 = TC1_ZERO;

    /*
    CTC mode:
    WGM12 = 1
    */

    TCCR1B |= (unsigned char)(
        TC1_ONE << TC1_WGM12_BIT
    );

    OCR1A =
        TC1_COMPARE_A_VALUE;

    /*
    Clear pending compare flag.
    */

    TIFR1 |= (unsigned char)(
        TC1_ONE << TC1_OCF1A_BIT
    );

    /*
    Enable compare A interrupt.
    */

    TIMSK1 |= (unsigned char)(
        TC1_ONE << TC1_OCIE1A_BIT
    );
}

void tc1_start(void)
{
    TCCR1B &= (unsigned char)(
        ~TC1_CLOCK_SELECT_MASK
    );

    TCNT1 = TC1_ZERO;

    TCCR1B |=
        TC1_PRESCALER_8_MASK;
}

void tc1_stop(void)
{
    TCCR1B &= (unsigned char)(
        ~TC1_CLOCK_SELECT_MASK
    );
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void tc1_compare_a_isr(void)
{
    scheduler_flags_management();
}