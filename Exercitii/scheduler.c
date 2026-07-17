#ifndef SCHEDULER_C
#define SCHEDULER_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/     
#include "iom324pb.h" 
#include "scheduler.h"
#include "timer.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  variables
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
volatile scheduler_t scheduler = {0};
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void scheduler_flags_management(void)
{
scheduler.flag_10ms=1;

static unsigned char count_50ms=0;
static unsigned char count_100ms=0;
static unsigned char count_500ms=0;
static unsigned char count_1000ms=0;

count_50ms++;
if(count_50ms>=PERIOD_OF_50MS)
{
  scheduler.flag_50ms=1;
  count_50ms=0;
}

count_100ms++;
if(count_100ms>=PERIOD_OF_100MS)
{
  scheduler.flag_100ms=1;
  count_100ms=0;
}

count_500ms++;
if(count_500ms>=PERIOD_OF_500MS)
{
  scheduler.flag_500ms=1;
  count_500ms=0;
}

count_1000ms++;
if(count_1000ms>=PERIOD_OF_1000MS)
{
  scheduler.flag_1000ms=1;
  count_1000ms=0;
}


}

void schedule_tasks_dispatcher(void)
{
    while(1)
    {
        if (scheduler.flag_10ms) {
            scheduler.flag_10ms = 0;
            task_10ms();
        }

        if (scheduler.flag_50ms) {
            scheduler.flag_50ms = 0;
            task_50ms();
        }

        if (scheduler.flag_100ms) {
            scheduler.flag_100ms = 0;
            task_100ms();
        }

        if (scheduler.flag_500ms) {
            scheduler.flag_500ms = 0;
            task_500ms();
        }

        if (scheduler.flag_1000ms) {
            scheduler.flag_1000ms = 0;
            task_1000ms();
        }
    }
}
        


#endif