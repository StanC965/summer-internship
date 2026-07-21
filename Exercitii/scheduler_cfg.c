#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"


volatile short sequence[33] = {0,0,0,1,1,1,1,2,2,21,41,60,80,57,33,10,33,55,77,100,92,85,77,69,62,54,46,38,31,23,15,8,0};
volatile unsigned char index = 0;




void task_10ms(void)
{
   
}
/*
0	0.00
0.05	0.22
0.1	0.44
0.15	0.65
0.2	0.87
0.25	1.09
0.3	1.31
0.35	1.52
0.4	1.74
0.45	21.31
0.5	40.87
0.55	60.44         HEARTBEAT
0.6	80.00
0.65	56.67
0.7	33.33
0.75	10.00
0.8	32.50
0.85	55.00
0.9	77.50
0.95	100.00
1	92.31
1.05	84.62
1.1	76.92
1.15	69.23
1.2	61.54
1.25	53.85
1.3	46.15
1.35	38.46
1.4	30.77
1.45	23.08
1.5	15.38
1.55	7.69
1.6	0.00
*/

void task_50ms(void)
{
   
  int true_value=100-sequence[index];
 pwm_dc(true_value);
 index++;
 if (index==33)
   index=0;
   
  
  
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