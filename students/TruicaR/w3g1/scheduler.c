#include "scheduler.h"

#define TICKS_50MS    5
#define TICKS_100MS   10
#define TICKS_500MS   50
#define TICKS_1000MS  100

volatile unsigned char flag_10ms   = 0;
volatile unsigned char flag_50ms   = 0;
volatile unsigned char flag_100ms  = 0;
volatile unsigned char flag_500ms  = 0;
volatile unsigned char flag_1000ms = 0;

static unsigned int tick_count = 0;

void scheduler_flags_management(void)
{
    tick_count++;

    flag_10ms = 1;

    if (tick_count % TICKS_50MS == 0)   flag_50ms = 1;
    if (tick_count % TICKS_100MS == 0)  flag_100ms = 1;
    if (tick_count % TICKS_500MS == 0)  flag_500ms = 1;
    if (tick_count % TICKS_1000MS == 0)
    {
        flag_1000ms = 1;
        tick_count = 0;  
    }
}