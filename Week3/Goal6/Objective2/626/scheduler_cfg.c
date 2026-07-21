#include "scheduler_cfg.h"
#include "pwm.h"


void scheduler_task_50ms(void)
{
    static int current_dc = 0;
    
    pwm_dc(current_dc);
    
    current_dc++;
    if (current_dc > 100)
    {
        current_dc = 0;
    }
}

void scheduler_task_100ms(void)
{
  
}

void scheduler_task_500ms(void)
{
    
}

void scheduler_task_1000ms(void)
{
    
}