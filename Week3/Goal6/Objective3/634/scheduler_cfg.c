#include "scheduler_cfg.h"
#include "pwm.h"

static const unsigned char pwm_heartbeat_lut[33] = {
    0, 0, 0, 1, 1, 1, 1, 2, 2, 21, 
    41, 60, 80, 57, 33, 10, 33, 55, 78, 100, 
    92, 85, 77, 69, 62, 54, 46, 38, 31, 23, 
    15, 8, 0
};

void scheduler_task_50ms(void)
{
    static unsigned char heartbeat_index = 0;
    
    pwm_dc(pwm_heartbeat_lut[heartbeat_index]);
    
    heartbeat_index++;
    if (heartbeat_index >= 33)
    {
        heartbeat_index = 0; 
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