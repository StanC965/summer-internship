#ifndef SCHEDULER_C
#define SCHEDULER_C

#include "scheduler.h"
#include "tasks.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Scheduler cooperativ bazat pe un system tick de 10 ms.

Functia scheduler_flags_management() este apelata
din ISR-ul TC1.

Functia scheduler_tasks_dispatcher() contine bucla
principala si executa taskurile activate.
*/

/* ========================================================= */
/* PERIOD CONFIGURATION                                      */
/* ========================================================= */

/*
System tick = 10 ms

50 ms   = 5 system ticks
100 ms  = 10 system ticks
500 ms  = 50 system ticks
1000 ms = 100 system ticks
*/

#define SCHEDULER_50MS_PERIOD_TICKS          (5U)
#define SCHEDULER_100MS_PERIOD_TICKS         (10U)
#define SCHEDULER_500MS_PERIOD_TICKS         (50U)
#define SCHEDULER_1000MS_PERIOD_TICKS        (100U)

#define SCHEDULER_COUNTER_INITIAL_VALUE      (0U)

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
    Aceasta functie este apelata de TC1 ISR
    la fiecare 10 ms.

    ISR-ul nu executa taskuri.
    El activeaza numai flagurile.
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

void scheduler_tasks_dispatcher(void)
{
    /*
    Aceasta este bucla principala a aplicatiei.

    Taskurile sunt executate cooperativ:
    - nu au prioritati;
    - nu se intrerup intre ele;
    - fiecare task trebuie sa returneze controlul;
    - nu sunt permise delay-uri blocante.
    */

    while (SCHEDULER_TRUE)
    {
        /*
        Flagul este resetat inaintea apelului.

        Astfel, daca in timpul executiei taskului apare
        urmatoarea perioada, ISR-ul poate activa din nou
        flagul pentru urmatoarea executie.
        */

        if (
            scheduler_10ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_10ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            task_10ms();
        }

        if (
            scheduler_50ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_50ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            task_50ms();
        }

        if (
            scheduler_100ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_100ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            task_100ms();
        }

        if (
            scheduler_500ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_500ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            task_500ms();
        }

        if (
            scheduler_1000ms_flag ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_1000ms_flag =
                SCHEDULER_FLAG_NOT_ACTIVE;

            task_1000ms();
        }
    }
}

#endif