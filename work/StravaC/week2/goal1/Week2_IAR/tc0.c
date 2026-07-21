#ifndef TC0_C
#define TC0_C

#include "iom324pb.h"

#include "tc0.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului Timer/Counter0.

Timerul functioneaza in NORMAL MODE:
0x00 -> 0x01 -> ... -> 0xFF -> 0x00

La revenirea de la 0xFF la 0x00 se produce overflow,
iar CPU-ul executa rutina de intrerupere TC0_OVF_vect.
*/

/* ========================================================= */
/* NORMAL MODE CONFIGURATION                                 */
/* ========================================================= */

/*
WGM02:0 = 000
*/

#define TC0_NORMAL_MODE_WGM02_VALUE       (0U)
#define TC0_NORMAL_MODE_WGM01_VALUE       (0U)
#define TC0_NORMAL_MODE_WGM00_VALUE       (0U)

/* ========================================================= */
/* COMPARE OUTPUT CONFIGURATION                              */
/* ========================================================= */

/*
COM0A[1:0] = 00
COM0B[1:0] = 00
*/

#define TC0_COMPARE_OUTPUT_DISABLED       (0U)

/* ========================================================= */
/* FORCE OUTPUT COMPARE                                     */
/* ========================================================= */

#define TC0_FORCE_COMPARE_DISABLED        (0U)

/* ========================================================= */
/* INTERRUPT CONFIGURATION                                   */
/* ========================================================= */

#define TC0_OVERFLOW_INTERRUPT_ENABLE     (1U)
#define TC0_COMPARE_INTERRUPT_DISABLE     (0U)

/* ========================================================= */
/* CLOCK CONFIGURATION                                       */
/* ========================================================= */

/*
CS02:0 = 001
Clock source = system clock
Prescaler = 1
*/

#define TC0_CLOCK_STOPPED_CS02_VALUE      (0U)
#define TC0_CLOCK_STOPPED_CS01_VALUE      (0U)
#define TC0_CLOCK_STOPPED_CS00_VALUE      (0U)

#define TC0_NO_PRESCALER_CS02_VALUE       (0U)
#define TC0_NO_PRESCALER_CS01_VALUE       (0U)
#define TC0_NO_PRESCALER_CS00_VALUE       (1U)

/* ========================================================= */
/* PRIVATE VARIABLES                                         */
/* ========================================================= */

static volatile tc0_uint8_t tc0_overflow_status;

/* ========================================================= */
/* INTERRUPT SERVICE ROUTINE                                 */
/* ========================================================= */

#pragma vector=TIMER0_OVF_vect
__interrupt void tc0_overflow_isr(void)
{
    tc0_overflow_status = TC0_OVERFLOW_OCCURRED;
}

/* ========================================================= */
/* MODULE INITIALIZATION                                     */
/* ========================================================= */

void tc0_init(void)
{
    tc0_overflow_status = TC0_OVERFLOW_NOT_OCCURRED;

    /*
    Opreste timerul in timpul configurarii.
    */

    TCCR0B_CS02 = TC0_CLOCK_STOPPED_CS02_VALUE;
    TCCR0B_CS01 = TC0_CLOCK_STOPPED_CS01_VALUE;
    TCCR0B_CS00 = TC0_CLOCK_STOPPED_CS00_VALUE;

    /*
    Dezactiveaza output compare pentru canalul A.
    */

    TCCR0A_COM0A1 = TC0_COMPARE_OUTPUT_DISABLED;
    TCCR0A_COM0A0 = TC0_COMPARE_OUTPUT_DISABLED;

    /*
    Dezactiveaza output compare pentru canalul B.
    */

    TCCR0A_COM0B1 = TC0_COMPARE_OUTPUT_DISABLED;
    TCCR0A_COM0B0 = TC0_COMPARE_OUTPUT_DISABLED;

    /*
    Selecteaza NORMAL MODE:
    WGM02:0 = 000.
    */

    TCCR0A_WGM01 = TC0_NORMAL_MODE_WGM01_VALUE;
    TCCR0A_WGM00 = TC0_NORMAL_MODE_WGM00_VALUE;
    TCCR0B_WGM02 = TC0_NORMAL_MODE_WGM02_VALUE;

    /*
    Nu se forteaza iesiri compare.
    */

    TCCR0B_FOC0A = TC0_FORCE_COMPARE_DISABLED;
    TCCR0B_FOC0B = TC0_FORCE_COMPARE_DISABLED;

    /*
    Dezactiveaza intreruperile Compare Match A si B.
    */

    TIMSK0_OCIE0A = TC0_COMPARE_INTERRUPT_DISABLE;
    TIMSK0_OCIE0B = TC0_COMPARE_INTERRUPT_DISABLE;

    /*
    Activeaza doar intreruperea de overflow.
    */

    TIMSK0_TOIE0 = TC0_OVERFLOW_INTERRUPT_ENABLE;

    /*
    Timerul ramane oprit dupa init.
    Pornirea este o actiune atomica separata.
    */
}

/* ========================================================= */
/* ATOMIC ACTIONS                                             */
/* ========================================================= */

void tc0_start(void)
{
    /*
    Selectarea clock-ului porneste timerul.

    Clock direct din sistem:
    fTC0 = 1 MHz.
    */

    TCCR0B_CS02 = TC0_NO_PRESCALER_CS02_VALUE;
    TCCR0B_CS01 = TC0_NO_PRESCALER_CS01_VALUE;
    TCCR0B_CS00 = TC0_NO_PRESCALER_CS00_VALUE;
}

void tc0_stop(void)
{
    TCCR0B_CS02 = TC0_CLOCK_STOPPED_CS02_VALUE;
    TCCR0B_CS01 = TC0_CLOCK_STOPPED_CS01_VALUE;
    TCCR0B_CS00 = TC0_CLOCK_STOPPED_CS00_VALUE;
}

tc0_uint8_t tc0_is_overflow_detected(void)
{
    return tc0_overflow_status;
}

void tc0_clear_overflow_status(void)
{
    tc0_overflow_status = TC0_OVERFLOW_NOT_OCCURRED;
}

#endif