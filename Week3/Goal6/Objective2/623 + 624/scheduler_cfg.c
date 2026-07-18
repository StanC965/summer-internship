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
    
}

void scheduler_task_1000ms(void)
{
    static unsigned char pwm_case_step = 0;

    switch (pwm_case_step)
    {
        case 0:
            pwm_set_duty_cycle(0);   
            pwm_case_step = 1;
            break;
            
        case 1:
            pwm_set_duty_cycle(25); 
            pwm_case_step = 2;
            break;
            
        case 2:
            pwm_set_duty_cycle(50); 
            pwm_case_step = 3;
            break;
            
        case 3:
            pwm_set_duty_cycle(75); 
            pwm_case_step = 4;
            break;
            
        case 4:
            pwm_set_duty_cycle(100); 
            pwm_case_step = 0;     
            break;
            
        default:
            pwm_set_duty_cycle(0);
            pwm_case_step = 0;
            break;
    }
}