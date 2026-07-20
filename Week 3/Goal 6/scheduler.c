#include "iom324pb.h"
#include "scheduler.h"
#include "scheduler_cfg.h"

static volatile unsigned char flag_10ms=0;
static volatile unsigned char flag_50ms=0;
static volatile unsigned char flag_100ms=0;
static volatile unsigned char flag_500ms=0;
static volatile unsigned char flag_1000ms=0;

void schedule_tasks_dispatcher(void) {
  while(1){
    if(flag_10ms==1){
      flag_10ms=0;
      task_10ms();
    }   
  }
}

void scheduler_flags_management(void){
  flag_10ms=1; 
}
