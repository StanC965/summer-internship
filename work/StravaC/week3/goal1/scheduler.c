#ifndef SCHEDULER_C
#define SCHEDULER_C

#include "scheduler.h"
#include "scheduler_cfg.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Scheduler cooperativ bazat pe un system tick de 10 ms.

Acest modul nu cunoaste functionalitatea concreta
a taskurilor.

El doar:
- construieste perioadele;
- activeaza flagurile;
- apeleaza callback-urile configurate.
*/

/* ========================================================= */
/* CONSTANTS                                                 */
/* ========================================================= */

#define SCHEDULER_FALSE                       (0U)
#define SCHEDULER_TRUE                        (1U)

#define SCHEDULER_FLAG_NOT_ACTIVE             (SCHEDULER_FALSE)
#define SCHEDULER_FLAG_ACTIVE                 (SCHEDULER_TRUE)

#define SCHEDULER_COUNTER_INITIAL_VALUE       (0U)

/*
System tick = 10 ms
*/

#define SCHEDULER_50MS_PERIOD_TICKS           (5U)
#define SCHEDULER_100MS_PERIOD_TICKS          (10U)
#define SCHEDULER_500MS_PERIOD_TICKS          (50U)
#define SCHEDULER_1000MS_PERIOD_TICKS         (100U)

/* ========================================================= */
/* TYPES                                                     */
/* ========================================================= */

typedef unsigned char scheduler_uint8_t;

/* ========================================================= */
/* PRIVATE COUNTERS                                          */
/* ========================================================= */

static volatile scheduler_uint8_t scheduler_50ms_counter;
static volatile scheduler_uint8_t scheduler_100ms_counter;
static volatile scheduler_uint8_t scheduler_500ms_counter;
static volatile scheduler_uint8_t scheduler_1000ms_counter;

/* ========================================================= */
/* PRIVATE FLAGS                                             */
/* ========================================================= */

static volatile scheduler_uint8_t scheduler_10ms_flag;
static volatile scheduler_uint8_t scheduler_50ms_flag;
static volatile scheduler_uint8_t scheduler_100ms_flag;
static volatile scheduler_uint8_t scheduler_500ms_flag;
static volatile scheduler_uint8_t scheduler_1000ms_flag;

/* ========================================================= */
/* MODULE INITIALIZATION                                     */
/* ========================================================= */

void scheduler_init(void)
{
    scheduler_50ms_counter =
        SCHEDULER_COUNTER_INITIAL_VALUE;

    scheduler_100ms_counter =
        SCHEDULER_COUNTER_INITIAL_VALUE;

    scheduler_500ms_counter =
        SCHEDULER_COUNTER_INITIAL_VALUE;

    scheduler_1000ms_counter =
        SCHEDULER_COUNTER_INITIAL_VALUE;

    scheduler_10ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;

    scheduler_50ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;

    scheduler_100ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;

    scheduler_500ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;

    scheduler_1000ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;
}

/* ========================================================= */
/* FLAGS MANAGEMENT                                          */
/* ========================================================= */

void scheduler_flags_management(void)
{
    /*
    Aceasta functie este apelata din ISR la fiecare 10 ms.

    ISR-ul nu executa taskurile.
    Sunt administrate numai flagurile si contoarele.
    */

    scheduler_10ms_flag =
        SCHEDULER_FLAG_ACTIVE;

    /* 50 ms */

    scheduler_50ms_counter++;

    if (
        scheduler_50ms_counter >=
        SCHEDULER_50MS_PERIOD_TICKS
    )
    {
        scheduler_50ms_counter =
            SCHEDULER_COUNTER_INITIAL_VALUE;

        scheduler_50ms_flag =
            SCHEDULER_FLAG_ACTIVE;
    }

    /* 100 ms */

    scheduler_100ms_counter++;

    if (
        scheduler_100ms_counter >=
        SCHEDULER_100MS_PERIOD_TICKS
    )
    {
        scheduler_100ms_counter =
            SCHEDULER_COUNTER_INITIAL_VALUE;

        scheduler_100ms_flag =
            SCHEDULER_FLAG_ACTIVE;
    }

    /* 500 ms */

    scheduler_500ms_counter++;

    if (
        scheduler_500ms_counter >=
        SCHEDULER_500MS_PERIOD_TICKS
    )
    {
        scheduler_500ms_counter =
            SCHEDULER_COUNTER_INITIAL_VALUE;

        scheduler_500ms_flag =
            SCHEDULER_FLAG_ACTIVE;
    }

    /* 1000 ms */

    scheduler_1000ms_counter++;

    if (
        scheduler_1000ms_counter >=
        SCHEDULER_1000MS_PERIOD_TICKS
    )
    {
        scheduler_1000ms_counter =
            SCHEDULER_COUNTER_INITIAL_VALUE;

        scheduler_1000ms_flag =
            SCHEDULER_FLAG_ACTIVE;
    }
}

/* ========================================================= */
/* TASKS DISPATCHER                                          */
/* ========================================================= */

void scheduler_dispatcher(void)
{
    /*
    Dispatcherul contine bucla infinita a aplicatiei.

    Schedulerul apeleaza functiile declarate in
    scheduler_cfg.h, fara sa cunoasca implementarea lor.
    */

    while (SCHEDULER_TRUE)
    {
        if (
            scheduler_10ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_10ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            scheduler_task_10ms();
        }

        if (
            scheduler_50ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_50ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            scheduler_task_50ms();
        }

        if (
            scheduler_100ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_100ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            scheduler_task_100ms();
        }

        if (
            scheduler_500ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_500ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            scheduler_task_500ms();
        }

        if (
            scheduler_1000ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_1000ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            scheduler_task_1000ms();
        }
    }
}

#endif