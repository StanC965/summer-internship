#include "scheduler_cfg.h"
#include "pwm.h"


void scheduler_task_50ms(void)
{
    
}

void scheduler_task_100ms(void)
{
  
}

void scheduler_task_500ms(void)
{
   static unsigned char step = 0;
    unsigned char dynamic_dc = 50; 
    
    if (step < 16)
    {
        long x = step;
        long target_amplitude = (4 * x * (16 - x) * 50) / 256; 
        dynamic_dc = 50 + (unsigned char)target_amplitude;
    }
    else
    {
        long x = step - 16;
        long target_amplitude = (4 * x * (16 - x) * 50) / 256;
        dynamic_dc = 50 - (unsigned char)target_amplitude;
    }

    pwm_dc(dynamic_dc);

    step++;
    if (step >= 32)
    {
        step = 0;
    } 
}

void scheduler_task_1000ms(void)
{
    
}