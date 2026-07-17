#include "scheduler.h"

volatile unsigned char scheduler_flag_50ms   = 0;
volatile unsigned char scheduler_flag_100ms  = 0;
volatile unsigned char scheduler_flag_500ms  = 0;
volatile unsigned char scheduler_flag_1000ms = 0;

void scheduler_init(void)
{
    scheduler_flag_50ms   = 0;
    scheduler_flag_100ms  = 0;
    scheduler_flag_500ms  = 0;
    scheduler_flag_1000ms = 0;
}

void scheduler_flags_management(void)
{
    static unsigned char scheduler_tick_counter = 0;

    scheduler_tick_counter++;

    if ((scheduler_tick_counter % 5) == 0)
    {
        scheduler_flag_50ms = 1;
    }

    if ((scheduler_tick_counter % 10) == 0)
    {
        scheduler_flag_100ms = 1;
    }

    if ((scheduler_tick_counter % 50) == 0)
    {
        scheduler_flag_500ms = 1;
    }

    if (scheduler_tick_counter >= 100)
    {
        scheduler_flag_1000ms = 1;
        scheduler_tick_counter = 0;
    }
}