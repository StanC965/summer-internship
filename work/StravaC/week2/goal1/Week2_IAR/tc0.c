#ifndef TC0_C
#define TC0_C

#include "iom324pb.h"

#include "tc0.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului Timer/Counter0.

Timerul functioneaza in Normal Mode:
0x00 -> ... -> 0xFF -> 0x00

Clock:
fCPU = 1 MHz
prescaler = 64

Un overflow:
256 * 64 / 1.000.000 = 16,384 ms

61 overflow-uri:
61 * 16,384 ms = 999,424 ms
*/

/* Normal Mode: WGM02:0 = 000 */

#define TC0_NORMAL_MODE_WGM02_VALUE          (0U)
#define TC0_NORMAL_MODE_WGM01_VALUE          (0U)
#define TC0_NORMAL_MODE_WGM00_VALUE          (0U)

/* Compare outputs disabled */

#define TC0_COMPARE_OUTPUT_DISABLED          (0U)
#define TC0_FORCE_COMPARE_DISABLED           (0U)

/* Interrupt configuration */

#define TC0_COMPARE_INTERRUPT_DISABLE        (0U)
#define TC0_OVERFLOW_INTERRUPT_ENABLE        (1U)

/* Timer stopped: CS02:0 = 000 */

#define TC0_CLOCK_STOPPED_CS02_VALUE         (0U)
#define TC0_CLOCK_STOPPED_CS01_VALUE         (0U)
#define TC0_CLOCK_STOPPED_CS00_VALUE         (0U)

/* Prescaler 64: CS02:0 = 011 */

#define TC0_PRESCALER_64_CS02_VALUE          (0U)
#define TC0_PRESCALER_64_CS01_VALUE          (1U)
#define TC0_PRESCALER_64_CS00_VALUE          (1U)

/* Period configuration */

#define TC0_OVERFLOWS_PER_SECOND             (61U)
#define TC0_OVERFLOW_COUNTER_INITIAL_VALUE   (0U)

/* Private module variables */

static volatile tc0_uint8_t tc0_overflow_counter;
static volatile tc0_uint8_t tc0_period_status;

/* Timer0 overflow ISR */

#pragma vector=TIMER0_OVF_vect
__interrupt void tc0_overflow_isr(void)
{
    tc0_overflow_counter++;

    if (tc0_overflow_counter >= TC0_OVERFLOWS_PER_SECOND)
    {
        tc0_overflow_counter =
            TC0_OVERFLOW_COUNTER_INITIAL_VALUE;

        tc0_period_status = TC0_PERIOD_ELAPSED;
    }
}

/* Module initialization */

void tc0_init(void)
{
    tc0_overflow_counter =
        TC0_OVERFLOW_COUNTER_INITIAL_VALUE;

    tc0_period_status =
        TC0_PERIOD_NOT_ELAPSED;

    /*
    Opreste timerul in timpul configurarii.
    */

    TCCR0B_CS02 = TC0_CLOCK_STOPPED_CS02_VALUE;
    TCCR0B_CS01 = TC0_CLOCK_STOPPED_CS01_VALUE;
    TCCR0B_CS00 = TC0_CLOCK_STOPPED_CS00_VALUE;

    /*
    Dezactiveaza output compare pentru canalele A si B.
    */

    TCCR0A_COM0A1 = TC0_COMPARE_OUTPUT_DISABLED;
    TCCR0A_COM0A0 = TC0_COMPARE_OUTPUT_DISABLED;

    TCCR0A_COM0B1 = TC0_COMPARE_OUTPUT_DISABLED;
    TCCR0A_COM0B0 = TC0_COMPARE_OUTPUT_DISABLED;

    /*
    Selecteaza Normal Mode:
    WGM02:0 = 000.
    */

    TCCR0A_WGM00 = TC0_NORMAL_MODE_WGM00_VALUE;
    TCCR0A_WGM01 = TC0_NORMAL_MODE_WGM01_VALUE;
    TCCR0B_WGM02 = TC0_NORMAL_MODE_WGM02_VALUE;

    /*
    Nu forteaza semnale compare.
    */

    TCCR0B_FOC0A = TC0_FORCE_COMPARE_DISABLED;
    TCCR0B_FOC0B = TC0_FORCE_COMPARE_DISABLED;

    /*
    Activeaza numai intreruperea de overflow.
    */

    TIMSK0_OCIE0A = TC0_COMPARE_INTERRUPT_DISABLE;
    TIMSK0_OCIE0B = TC0_COMPARE_INTERRUPT_DISABLE;
    TIMSK0_TOIE0 = TC0_OVERFLOW_INTERRUPT_ENABLE;
}

/* Atomic actions */

void tc0_start(void)
{
    /*
    Selectarea prescalerului porneste timerul.
    Aceasta operatie este facuta ultima.
    */

    TCCR0B_CS02 = TC0_PRESCALER_64_CS02_VALUE;
    TCCR0B_CS01 = TC0_PRESCALER_64_CS01_VALUE;
    TCCR0B_CS00 = TC0_PRESCALER_64_CS00_VALUE;
}

void tc0_stop(void)
{
    TCCR0B_CS02 = TC0_CLOCK_STOPPED_CS02_VALUE;
    TCCR0B_CS01 = TC0_CLOCK_STOPPED_CS01_VALUE;
    TCCR0B_CS00 = TC0_CLOCK_STOPPED_CS00_VALUE;
}

tc0_uint8_t tc0_is_period_elapsed(void)
{
    return tc0_period_status;
}

void tc0_clear_period_status(void)
{
    tc0_period_status = TC0_PERIOD_NOT_ELAPSED;
}

#endif