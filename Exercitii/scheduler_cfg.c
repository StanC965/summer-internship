#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"


volatile short sequence[5] = {0, 64, 128, 192, 255};
volatile unsigned char index = 0;

void task_10ms(void)
{
   
}

void task_50ms(void)
{
   
   
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {

 index++;
    if(index > 4)
        index = 0;
    
   switch(index)
   {
   case 0:  pwm_dc(0);break;
   case 1:  pwm_dc(25);break;
   case 2:  pwm_dc(50);break;
   case 3:  pwm_dc(75);break;
   case 4:  pwm_dc(100);break;
   }

}

#endif