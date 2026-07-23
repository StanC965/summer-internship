
#include "week1\Goal 2\adc.h"
#include "week1\Goal 2\timer.h"
#include "CarCrashDetection.h"
#include "scheduler.h"


void main (void)
{
   led_init();
   btn_init();
   ADC_init();
   resolution(Rez10bit);
   InterruptADC();
   task_init();
   Timer1_Scheduler_Init();
   PWM_TC1_Init();
   schedule_tasks_dispatcher();   
  
}