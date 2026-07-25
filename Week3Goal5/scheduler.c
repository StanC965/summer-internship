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
#define SCHED_DBG_PIN        (7U)      

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
    if ((sched_tick % SCHED_500MS_TICKS) == 0U) { flag_500ms = 1U; PINC = (1 << SCHED_DBG_PIN); } 
    if (sched_tick == SCHED_1000MS_TICKS) { flag_1000ms = 1U; sched_tick = 0U; }
}

#endif
