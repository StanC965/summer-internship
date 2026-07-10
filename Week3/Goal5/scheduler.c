#ifndef SCH_C
#define SCH_C
#include "scheduleCFG.h"

#include "led.h"
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0
#define OCIE1A 1

#define PD4 4
#define COM1A 6
#define PD5 5
#define PA3 3

_Bool flag10ms = 0;
_Bool flag50ms = 0;
_Bool flag100ms = 0;
_Bool flag500ms = 0;
_Bool flag1000ms = 0;
void programInit(){
  TCNT1 = 0;
  OCR1A = 9999;
  //initializam pini de care avem nevoie pentru a vedea cum se schimba unu la 10 ms si unu la 1000ms 
    
  ledInit(&DDRA,&PORTA,PA3);
  ledInit(&DDRD,&PORTD,PD4);
  setPin(&TCCR1B,WGM12);
  setPin(&TIMSK1,OCIE1A);
  setPin(&TCCR1B,CS11);
  
  setPin(&TCCR1A,COM1A);
}

void scheduleTaskDispatcher(void){
  programInit();
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