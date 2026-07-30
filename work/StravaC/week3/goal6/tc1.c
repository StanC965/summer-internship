#ifndef TC1_C
#define TC1_C

#include "iom324pb.h"

#include "scheduler.h"
#include "tc1.h"

/*
TC1 is dedicated to the task scheduler.

System clock:
16 MHz

Prescaler:
8

Scheduler tick:
10 ms

Calculation:

OCR1A =
    (fCPU * tick_time / prescaler) - 1

OCR1A =
    (16000000 * 0.010 / 8) - 1

OCR1A =
    20000 - 1

OCR1A = 19999
*/

#define TC1_ZERO                              (0U)
#define TC1_ONE                               (1U)

#define TC1_COMPARE_A_VALUE                   (19999U)

/*
TCCR1B bit positions:

bit 3: WGM12
bit 2: CS12
bit 1: CS11
bit 0: CS10
*/

#define TC1_WGM12_BIT                         (3U)
#define TC1_CS12_BIT                          (2U)
#define TC1_CS11_BIT                          (1U)
#define TC1_CS10_BIT                          (0U)

/*
TIMSK1 bit positions:

bit 1: OCIE1A
*/

#define TC1_OCIE1A_BIT                        (1U)

/*
TIFR1 bit positions:

bit 1: OCF1A
*/

#define TC1_OCF1A_BIT                         (1U)

#define TC1_CLOCK_SELECT_MASK                 \
    ((TC1_ONE << TC1_CS12_BIT) |              \
     (TC1_ONE << TC1_CS11_BIT) |              \
     (TC1_ONE << TC1_CS10_BIT))

/*
Prescaler 8:

CS12 = 0
CS11 = 1
CS10 = 0
*/

#define TC1_PRESCALER_8_MASK                  \
    (TC1_ONE << TC1_CS11_BIT)

void tc1_init(void)
{
    /*
    Stop TC1 before configuration.
    */

    TCCR1B &= (unsigned char)(
        ~TC1_CLOCK_SELECT_MASK
    );

    /*
    Reset Timer1 control registers.
    */

    TCCR1A = TC1_ZERO;
    TCCR1B = TC1_ZERO;

    /*
    Reset counter.
    */

    TCNT1 = TC1_ZERO;

    /*
    Configure CTC mode.

    WGM13:WGM10 = 0100

    WGM12 = 1
    WGM13 = 0
    WGM11 = 0
    WGM10 = 0
    */

    TCCR1B |= (unsigned char)(
        TC1_ONE << TC1_WGM12_BIT
    );

    /*
    Compare value for a 10 ms scheduler tick.
    */

    OCR1A = TC1_COMPARE_A_VALUE;

    /*
    Clear a possible pending Output Compare A flag.

    AVR interrupt flags are cleared by writing logic 1.
    */

    TIFR1 |= (unsigned char)(
        TC1_ONE << TC1_OCF1A_BIT
    );

    /*
    Enable Timer1 Output Compare A interrupt.
    */

    TIMSK1 |= (unsigned char)(
        TC1_ONE << TC1_OCIE1A_BIT
    );
}

void tc1_start(void)
{
    /*
    Clear existing clock selection.
    */

    TCCR1B &= (unsigned char)(
        ~TC1_CLOCK_SELECT_MASK
    );

    /*
    Reset the counter before starting.
    */

    TCNT1 = TC1_ZERO;

    /*
    Start TC1 with prescaler 8.
    */

    TCCR1B |= TC1_PRESCALER_8_MASK;
}

void tc1_stop(void)
{
    /*
    CS12:CS10 = 000.
    Timer1 stops counting.
    */

    TCCR1B &= (unsigned char)(
        ~TC1_CLOCK_SELECT_MASK
    );
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void tc1_compare_a_isr(void)
{
    scheduler_flags_management();
}

#endif