#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"


volatile short sequence[5] = {0, 64, 128, 192, 255};
volatile unsigned char index = 0;
volatile int completion_index = 0; 
volatile int break_index=0;
volatile _Bool increasing=1;

void task_10ms(void)
{
   
}

void task_50ms(void)
{
   
  if(break_index ==0)
  {
    int true__value=0;
      completion_index +=2;     
    if(increasing)
    {

   true__value=100-completion_index;    ///graficul nu a fost dat in problema ,asa ca am presupus ca s-a cerut un semnal trapezoidal
    }
    else{
      true__value=completion_index;
    }
  pwm_dc(true__value);
   if(completion_index ==100)
   {
      completion_index=0;
      
      if(!increasing)
        increasing=1;
      else
        break_index++;
     
   }
   
  }
  else{
     pwm_dc(0);
     break_index++;
     if(break_index==61)
     {
       break_index=0;
       increasing=!increasing;
     }
  }
}

void task_100ms(void) {}
void task_500ms(void) {}
void task_1000ms(void) {

  /*
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
*/

}

#endif