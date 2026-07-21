#ifndef SCHEDULER_CONFIG_C
#define SCHEDULER_CONFIG_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"       
#include "iom324pb.h"  
#include "timer.h"
#include "scheduler.h"
#include "led.h"
#include "adc.h"
#include "button.h"
#include "pwm.h"

#ifdef ADC_USE_8_BIT_RESOLUTION
    #define THRESHOLD_1 64
    #define THRESHOLD_2 128
    #define THRESHOLD_3 192
    #define DAY_LIGHT   102
#else
    #define THRESHOLD_1 255    //bloc decizie rezolutiede 8 sau 10
    #define THRESHOLD_2 511
    #define THRESHOLD_3 767
    #define DAY_LIGHT   410
#endif





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Implementation      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef enum { STATE_ON2S,STATE_OFF1S, STATE_ON1S,STATE_OFF3S } led_state_t;
static led_state_t current_state = STATE_OFF1S;
volatile unsigned char period=0;




void task_10ms(void)
{
    
}
void task_50ms(void)
{
    

}


void task_100ms(void)
{
    
}
void task_500ms(void)
{
   
}

void task_1000ms(void)
{
  period++;
  switch(current_state)
  {
  case STATE_OFF1S: led_Reset(LED_ZERO);
      current_state=STATE_ON1S;
      period=0;
      break;
  case STATE_ON1S: if(period ==3)
  {
    current_state=STATE_OFF3S;
    period=0;
    led_Set(LED_ZERO);
  }
  break;
  case STATE_OFF3S:if(period==2)
  {
    current_state=STATE_ON2S;
    period=0;
    led_Reset(LED_ZERO);
  }
  break;
  case STATE_ON2S: 
    period=0;
    current_state=STATE_OFF1S;
  led_Set(LED_ZERO);
  break;
  
   
    
    
  }
}
            
       


#endif


/*

Time [sec]	Entry phase Night mode RELATIVE steps	Entry phase Day mode RELATIVE steps
0	0	0
0.2	1	4
0.4	1	7
0.6	3	16
0.8	7	44
1	16	59
1.2	16	59
1.4	14	55
1.6	12	50
1.8	10	45
2	8	40
Success in winning the project !!! Enjoy your 22h flight and don't forget to come


*/
