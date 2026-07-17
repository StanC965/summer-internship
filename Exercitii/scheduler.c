#ifndef SCHEDULER_C
#define SCHEDULER_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/     
#include "iom324pb.h" 
#include "scheduler.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  variables
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
volatile bool flag_10ms   = false;
volatile bool flag_50ms   = false;
volatile bool flag_100ms  = false;
volatile bool flag_500ms  = false;
volatile bool flag_1000ms = false;
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
if(count_100ms>=PERIOD_OF_50MS)
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
        


#endif