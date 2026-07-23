#include "scheduler.h"

static volatile unsigned char flag_task_10ms  = 0;
static volatile unsigned char flag_task_50ms  = 0;
static volatile unsigned char flag_task_100ms = 0;
static volatile unsigned char flag_task_500ms = 0;
static volatile unsigned char flag_task_1000ms = 0;

static unsigned char counter_50ms  = 0;
static unsigned char counter_100ms = 0;
static unsigned char counter_500ms = 0;
static unsigned char counter_1000ms = 0;

void scheduler_flags_management(void)
{

    flag_task_10ms = 1;

    if (++counter_50ms >= 5) {
        flag_task_50ms = 1;
        counter_50ms = 0;
    }


    if (++counter_100ms >= 10) {
        flag_task_100ms = 1;
        counter_100ms = 0;
    }


    if (++counter_500ms >= 50) {
        flag_task_500ms = 1;
        counter_500ms = 0;
    }
    if (++counter_1000ms >= 50) {
        flag_task_1000ms = 1;
        counter_1000ms = 0;
    }
}

__interrupt void Timer0_SystemTick_ISR(void)
{
    scheduler_flags_management();
}

void task_init(void)
{

   TCCR0A=0x02;
  OCR0A=0xe4;
  TIMSK0=0x02;
  SREG_I=1;
  TCNT0=0;
  TCCR0B=0x05;
}

void schedule_tasks_dispatcher(void)
{      
    while (1)
    {
        if (flag_task_10ms) {
            flag_task_10ms = 0;
            task_10ms();
        }

        if (flag_task_50ms) {
            flag_task_50ms = 0;
            task_50ms();
        }

        if (flag_task_100ms) {
            flag_task_100ms = 0;
            task_100ms();
        }

        if (flag_task_500ms) {
            flag_task_500ms = 0;
            task_500ms();
        }
    }
}