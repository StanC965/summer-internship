#include "tasks.h"

volatile int i=0;
volatile unsigned int prescale=0;
static volatile int sec=0;
volatile unsigned char flag_task_10ms = 0;
volatile unsigned char flag_task_50ms = 0;
volatile unsigned char flag_task_100ms = 0;
volatile unsigned char flag_task_500ms = 0;
volatile unsigned char flag_task_1000ms = 0;
volatile unsigned int halfsecond=0;
volatile unsigned int second=0;
__interrupt void flags(){
  i++;
  scheduler_flags_management();
 
}
void scheduler_flags_management(){
flag_task_10ms=1;
sec++;
i++;
  if(sec>=5){  
    flag_task_50ms=1;
    halfsecond++;
    if(halfsecond>=10)
    {
      flag_task_500ms=1;
      halfsecond=0;
  }
  sec=0;
  }
  if(i>=10){
    second++;
    if(second>=10){
      flag_task_1000ms=1;
      second=0;
    }
    flag_task_100ms=1;
    i=0;
  }
}
void task_init(){
  TCCR0A=0x02;
  OCR0A=0xe4;
  TIMSK0=0x02;
  SREG_I=1;
}
