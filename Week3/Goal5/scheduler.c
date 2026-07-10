#ifndef SCH_C
#define SCH_C
#include "scheduleCFG.h"

void scheduleTaskDispatcher(void){
 while(1){
    if(flag10ms){
      flag10ms = 0;
      task10ms();
      
      
    }
    if(flag50ms){
      flag50ms = 0;
      task50ms();
    }
    if(flag100ms){
      flag100ms = 0;
      task100ms();
    }
    if(flag500ms){
      flag500ms = 0;
      task500ms();
    }
    if(flag1000ms){
      flag1000ms = 0;
      task100ms();
    }
  }
}

void schedulerFlasgsManagement(void){
  static unsigned char cnt50 = 0;
  static unsigned char cnt100 = 0;
  static unsigned short int cnt500 = 0;
  static unsigned short int cnt1000 = 0;
  flag10ms = 1;
  cnt50++;
  cnt100++;
  cnt500++;
  cnt1000++;
  if(cnt50 == 5){
    cnt50 = 0;
    flag50ms = 1;
    
  }
   if(cnt100 == 10){
    cnt100 = 0;
    flag100ms = 0;
  }
  if(cnt500 ==50){
    cnt500 = 0;
    flag500ms = 1;
  }
  
  if(cnt1000 == 100){
    cnt1000 = 0;
    flag1000ms = 1;
  }
}



#endif