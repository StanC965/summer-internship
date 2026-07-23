#include <iom324pb.h>
#include "scheduler_cfg.h"


#pragma vector = TIMER0_COMPA_vect
__interrupt void Timer0_SystemTick_ISR(void);


void task_init();
void schedule_tasks_dispatcher();
void scheduler_flags_management();