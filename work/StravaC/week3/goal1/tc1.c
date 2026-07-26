#ifndef TC1_C
#define TC1_C

#include "iom324pb.h"

#include "tc1.h"
#include "scheduler.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Timer/Counter1 dedicat system tick-ului schedulerului.

Configuratie:
- fCPU = 16 MHz;
- external crystal;
- CKDIV8 disabled;
- TC1 CTC Mode;
- prescaler = 8;
- OCR1A = 19999;
- interrupt periodic la fiecare 10 ms.

Calcul:

Ttick = (OCR1A + 1) * prescaler / fCPU

Ttick = (19999 + 1) * 8 / 16000000
      = 0.010 s
      = 10 ms
*/

/* ========================================================= */
/* CTC MODE                                                  */
/* ========================================================= */

/*
TC1 Mode 4:
WGM13:0 = 0100
TOP = OCR1A
*/

#define TC1_CTC_MODE_WGM13_VALUE              (0U)
#define TC1_CTC_MODE_WGM12_VALUE              (1U)
#define TC1_CTC_MODE_WGM11_VALUE              (0U)
#define TC1_CTC_MODE_WGM10_VALUE              (0U)

/* ========================================================= */
/* OUTPUT COMPARE                                            */
/* ========================================================= */

/*
TC1 este folosit numai pentru system tick.
Iesirile OC1A si OC1B nu sunt utilizate.
*/

#define TC1_OUTPUT_COMPARE_DISABLED           (0U)
#define TC1_FORCE_COMPARE_DISABLED            (0U)

/* ========================================================= */
/* INTERRUPTS                                                */
/* ========================================================= */

#define TC1_COMPARE_A_INTERRUPT_ENABLE        (1U)
#define TC1_COMPARE_B_INTERRUPT_DISABLE       (0U)
#define TC1_OVERFLOW_INTERRUPT_DISABLE        (0U)
#define TC1_INPUT_CAPTURE_INTERRUPT_DISABLE   (0U)

/* ========================================================= */
/* CLOCK CONFIGURATION                                       */
/* ========================================================= */

/*
Timer stopped:
CS12:0 = 000
*/

#define TC1_CLOCK_STOPPED_CS12_VALUE          (0U)
#define TC1_CLOCK_STOPPED_CS11_VALUE          (0U)
#define TC1_CLOCK_STOPPED_CS10_VALUE          (0U)

/*
Prescaler 8:
CS12:0 = 010
*/

#define TC1_PRESCALER_8_CS12_VALUE            (0U)
#define TC1_PRESCALER_8_CS11_VALUE            (1U)
#define TC1_PRESCALER_8_CS10_VALUE            (0U)

/* ========================================================= */
/* SYSTEM TICK CONFIGURATION                                 */
/* ========================================================= */

#define TC1_SYSTEM_TICK_TOP_VALUE             (19999U)
#define TC1_COUNTER_INITIAL_VALUE             (0U)

/*
Flagurile TIFR1 se sterg scriind logic 1.
*/

#define TC1_CLEAR_COMPARE_A_FLAG              (1U)

/* ========================================================= */
/* INTERRUPT SERVICE ROUTINE                                 */
/* ========================================================= */

#pragma vector=TIMER1_COMPA_vect
__interrupt void tc1_compare_a_isr(void)
{
    /*
    ISR-ul este executat la fiecare 10 ms.

    Nu executa taskurile direct.
    Administreaza numai contoarele si flagurile
    schedulerului.
    */

    scheduler_flags_management();
}

/* ========================================================= */
/* MODULE INITIALIZATION                                     */
/* ========================================================= */

void tc1_init(void)
{
    /*
    Timerul trebuie sa fie oprit inainte de configurare.
    */

    tc1_stop();

    /*
    Deconecteaza iesirea hardware OC1A.
    */

    TCCR1A_COM1A1 =
        TC1_OUTPUT_COMPARE_DISABLED;

    TCCR1A_COM1A0 =
        TC1_OUTPUT_COMPARE_DISABLED;

    /*
    Deconecteaza iesirea hardware OC1B.
    */

    TCCR1A_COM1B1 =
        TC1_OUTPUT_COMPARE_DISABLED;

    TCCR1A_COM1B0 =
        TC1_OUTPUT_COMPARE_DISABLED;

    /*
    Selecteaza CTC Mode 4:
    WGM13:0 = 0100.
    */

    TCCR1A_WGM10 =
        TC1_CTC_MODE_WGM10_VALUE;

    TCCR1A_WGM11 =
        TC1_CTC_MODE_WGM11_VALUE;

    TCCR1B_WGM12 =
        TC1_CTC_MODE_WGM12_VALUE;

    TCCR1B_WGM13 =
        TC1_CTC_MODE_WGM13_VALUE;

    /*
    Nu se forteaza Compare Match A sau B.
    */

    TCCR1C_FOC1A =
        TC1_FORCE_COMPARE_DISABLED;

    TCCR1C_FOC1B =
        TC1_FORCE_COMPARE_DISABLED;

    /*
    OCR1A reprezinta TOP in CTC Mode.

    Compare Match A apare la fiecare 10 ms.
    */

    OCR1A =
        TC1_SYSTEM_TICK_TOP_VALUE;

    /*
    Counterul porneste de la zero.
    */

    TCNT1 =
        TC1_COUNTER_INITIAL_VALUE;

    /*
    Dezactiveaza intreruperea Input Capture.
    */

    TIMSK1_ICIE1 =
        TC1_INPUT_CAPTURE_INTERRUPT_DISABLE;

    /*
    Dezactiveaza Compare Match B.
    */

    TIMSK1_OCIE1B =
        TC1_COMPARE_B_INTERRUPT_DISABLE;

    /*
    Dezactiveaza overflow interrupt.
    In CTC Mode folosim Compare Match A.
    */

    TIMSK1_TOIE1 =
        TC1_OVERFLOW_INTERRUPT_DISABLE;

    /*
    Activeaza Compare Match A Interrupt.
    */

    TIMSK1_OCIE1A =
        TC1_COMPARE_A_INTERRUPT_ENABLE;
}

/* ========================================================= */
/* TIMER START                                               */
/* ========================================================= */

void tc1_start(void)
{
    /*
    Porneste fiecare masurare de la zero.
    */

    TCNT1 =
        TC1_COUNTER_INITIAL_VALUE;

    /*
    Sterge un eventual Compare Match A flag
    ramas dintr-o utilizare anterioara.
    */

    TIFR1_OCF1A =
        TC1_CLEAR_COMPARE_A_FLAG;

    /*
    Selectarea sursei de clock porneste timerul.

    Prescaler = 8.
    Aceasta este ultima operatie de configurare.
    */

    TCCR1B_CS12 =
        TC1_PRESCALER_8_CS12_VALUE;

    TCCR1B_CS11 =
        TC1_PRESCALER_8_CS11_VALUE;

    TCCR1B_CS10 =
        TC1_PRESCALER_8_CS10_VALUE;
}

/* ========================================================= */
/* TIMER STOP                                                */
/* ========================================================= */

void tc1_stop(void)
{
    /*
    CS12:0 = 000 opreste timerul.
    Restul configuratiei registrelor ramane neschimbat.
    */

    TCCR1B_CS12 =
        TC1_CLOCK_STOPPED_CS12_VALUE;

    TCCR1B_CS11 =
        TC1_CLOCK_STOPPED_CS11_VALUE;

    TCCR1B_CS10 =
        TC1_CLOCK_STOPPED_CS10_VALUE;
}

#endif