#ifndef SCHEDULER_C
#define SCHEDULER_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "scheduler.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define SCHED_50MS_TICKS     (5U)      
#define SCHED_100MS_TICKS    (10U)
#define SCHED_500MS_TICKS    (50U)
#define SCHED_1000MS_TICKS   (100U)   

static volatile unsigned char sched_tick;      
static volatile unsigned char flag_10ms;
static volatile unsigned char flag_50ms;
static volatile unsigned char flag_100ms;
static volatile unsigned char flag_500ms;
static volatile unsigned char flag_1000ms;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void scheduler_init(void)
{
    sched_tick  = 0U;
    flag_10ms   = 0U;
    flag_50ms   = 0U;
    flag_100ms  = 0U;
    flag_500ms  = 0U;
    flag_1000ms = 0U;
}

void scheduler_flags_management(void)
{
    sched_tick++;

    flag_10ms = 1U;
    if ((sched_tick % SCHED_50MS_TICKS)  == 0U) flag_50ms  = 1U;
    if ((sched_tick % SCHED_100MS_TICKS) == 0U) flag_100ms = 1U;
    if ((sched_tick % SCHED_500MS_TICKS) == 0U) flag_500ms = 1U;
    if (sched_tick == SCHED_1000MS_TICKS) { flag_1000ms = 1U; sched_tick = 0U; }
}

unsigned char scheduler_flag_10ms(void)
{
    unsigned char f = flag_10ms;
    flag_10ms = 0U;
    return f;
}

unsigned char scheduler_flag_50ms(void)
{
    unsigned char f = flag_50ms;
    flag_50ms = 0U;
    return f;
}

unsigned char scheduler_flag_100ms(void)
{
    unsigned char f = flag_100ms;
    flag_100ms = 0U;
    return f;
}

unsigned char scheduler_flag_500ms(void)
{
    unsigned char f = flag_500ms;
    flag_500ms = 0U;
    return f;
}

unsigned char scheduler_flag_1000ms(void)
{
    unsigned char f = flag_1000ms;
    flag_1000ms = 0U;
    return f;
}

#endif
