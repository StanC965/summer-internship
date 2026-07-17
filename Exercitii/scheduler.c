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
volatile _Bool flag_10ms   = 0;
volatile _Bool flag_50ms   = 0;
volatile _Bool flag_100ms  = 0;
volatile _Bool flag_500ms  = 0;
volatile _Bool flag_1000ms = 0;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void scheduler_flags_management(void)
{
flag_10ms=1;

static unsigned char count_50ms=0;
static unsigned char count_100ms=0;
static unsigned char count_500ms=0;
static unsigned char count_1000ms=0;

count_50ms++;
if(count_50ms>=PERIOD_OF_50MS)
{
  flag_50ms=1;
  count_50ms=0;
}

count_100ms++;
if(count_100ms>=PERIOD_OF_100MS)
{
  flag_100ms=1;
  count_100ms=0;
}

count_500ms++;
if(count_500ms>=PERIOD_OF_500MS)
{
  flag_500ms=1;
  count_500ms=0;
}

count_1000ms++;
if(count_1000ms>=PERIOD_OF_1000MS)
{
  flag_1000ms=1;
  count_1000ms=0;
}


}

void schedule_tasks_dispatcher(void)
{
    while(1)
    {
        if (flag_10ms) {
            flag_10ms = 0;
            task_10ms();
        }

        if (flag_50ms) {
            flag_50ms = 0;
            task_50ms();
        }

        if (flag_100ms) {
            flag_100ms = 0;
            task_100ms();
        }

        if (flag_500ms) {
            flag_500ms = 0;
            task_500ms();
        }

        if (flag_1000ms) {
            flag_1000ms = 0;
            task_1000ms();
        }
    }
}
        


#endif