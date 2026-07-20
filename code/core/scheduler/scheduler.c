#ifndef SCHEDULER_C
#define SCHEDULER_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "scheduler.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static volatile uint32_t scheduler_tick_counter = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

volatile uint8_t scheduler_flag_10ms = 0;
volatile uint8_t scheduler_flag_50ms = 0;
volatile uint8_t scheduler_flag_100ms = 0;
volatile uint8_t scheduler_flag_500ms = 0;
volatile uint8_t scheduler_flag_1000ms = 0;

void scheduler_flags_management(void)
{
    scheduler_flags_10ms = 1;
    scheduler_tick_counter++;

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_50MS) == 0)
    {
        scheduler_flag_50ms = 1;
    }

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_100MS) == 0)
    {
        scheduler_flag_100ms = 1;
    }

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_500MS) == 0)
    {
        scheduler_flag_500ms = 1;
    }

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_1000MS) == 0)
    {
        scheduler_flag_1000ms = 1;
    }
}

void task_10ms(void)
{
}

void task_50ms(void)
{
}

void task_100ms(void)
{
}

void task_500ms(void)
{
}

void task_1000ms(void)
{
}

void scheduler_tasks_dispatcher(void)
{
    while (1)
    {
        if (scheduler_flag_10ms)
        {
            scheduler_flag_10ms = 0;
            task_10ms();
        }

        if (scheduler_flag_50ms)
        {
            scheduler_flag_50ms = 0;
            task_50ms();
        }

        if (scheduler_flag_100ms)
        {
            scheduler_flag_100ms = 0;
            task_100ms();
        }

        if (scheduler_flag_500ms)
        {
            scheduler_flag_500ms = 0;
            task_500ms();
        }

        if (scheduler_flag_1000ms)
        {
            scheduler_flag_1000ms = 0;
            task_1000ms();
        }
    }
}

#endif /* SCHEDULER_C */
