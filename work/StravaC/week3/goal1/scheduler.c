#ifndef SCHEDULER_C
#define SCHEDULER_C

#include "scheduler.h"
#include "scheduler_cfg.h"

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

typedef unsigned char scheduler_uint8_t;

static volatile scheduler_uint8_t scheduler_50ms_counter;
static volatile scheduler_uint8_t scheduler_100ms_counter;
static volatile scheduler_uint8_t scheduler_500ms_counter;
static volatile scheduler_uint8_t scheduler_1000ms_counter;

static volatile scheduler_uint8_t scheduler_10ms_flag;
static volatile scheduler_uint8_t scheduler_50ms_flag;
static volatile scheduler_uint8_t scheduler_100ms_flag;
static volatile scheduler_uint8_t scheduler_500ms_flag;
static volatile scheduler_uint8_t scheduler_1000ms_flag;

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

void scheduler_flags_management(void)
{
    scheduler_10ms_flag =
        SCHEDULER_FLAG_ACTIVE;

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

void scheduler_dispatcher(void)
{
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