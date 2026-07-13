#ifndef SCDSIN_C
#define SCDSIN_C
#include "pwm.h"
#include "led.h"

#define led4 4

#define period 17

#define up 5
#define down 2


#define top 256
#define step 25
unsigned char cnt = 0;
unsigned char mainCnt = 0;
unsigned short int stepCnt = 0;
unsigned char sinTable[]= {0,4,15,33,50,67,85,96,100,96,85,67,50,33,15,4,0};
void task10ms(){
    
    
}
      
void task50ms(){
 

}
      
void task100ms(){
  setPwmDc(sinTable[cnt]);
  cnt = (cnt+1)%period;
  
  
}
      
void task500ms(){
}

void task1000ms(){
 
}


#endif