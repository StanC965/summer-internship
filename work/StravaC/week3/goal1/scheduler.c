#ifndef SCHEDULER_C
#define SCHEDULER_C

#include "scheduler.h"

/*
System tick = 10 ms

50 ms   / 10 ms = 5 ticks
100 ms  / 10 ms = 10 ticks
500 ms  / 10 ms = 50 ticks
1000 ms / 10 ms = 100 ticks
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
    Aceasta functie este apelata la fiecare 10 ms
    din ISR-ul Timer/Counter1.

    Flagul de 10 ms este activat la fiecare system tick.
    */

    scheduler_10ms_flag =
        SCHEDULER_FLAG_ACTIVE;

    /* 50 ms period */

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

    /* 100 ms period */

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

    /* 500 ms period */

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

    /* 1000 ms period */

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
/* FLAG STATE FUNCTIONS                                      */
/* ========================================================= */

scheduler_uint8_t scheduler_is_10ms_flag_active(void)
{
    return scheduler_10ms_flag;
}

scheduler_uint8_t scheduler_is_50ms_flag_active(void)
{
    return scheduler_50ms_flag;
}

scheduler_uint8_t scheduler_is_100ms_flag_active(void)
{
    return scheduler_100ms_flag;
}

scheduler_uint8_t scheduler_is_500ms_flag_active(void)
{
    return scheduler_500ms_flag;
}

scheduler_uint8_t scheduler_is_1000ms_flag_active(void)
{
    return scheduler_1000ms_flag;
}

/* ========================================================= */
/* FLAG CLEAR FUNCTIONS                                      */
/* ========================================================= */

void scheduler_clear_10ms_flag(void)
{
    scheduler_10ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;
}

void scheduler_clear_50ms_flag(void)
{
    scheduler_50ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;
}

void scheduler_clear_100ms_flag(void)
{
    scheduler_100ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;
}

void scheduler_clear_500ms_flag(void)
{
    scheduler_500ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;
}

void scheduler_clear_1000ms_flag(void)
{
    scheduler_1000ms_flag =
        SCHEDULER_FLAG_NOT_ACTIVE;
}

#endif