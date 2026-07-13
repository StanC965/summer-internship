#ifndef SCDCFG_C
#define SCDCFG_C
#include "pwm.h"
#include "led.h"

#define led4 4

#define period 18

#define up 5
#define down 2


#define top 256
#define step 25
unsigned char cnt = 0;
unsigned char mainCnt = 0;
unsigned short int stepCnt = 0;
void task10ms(){
    
}
      
void task50ms(){
 

}
      
void task100ms(){
  stepCnt++;
  if( mainCnt < 3){
      if(stepCnt % 3 == 0)
        cnt+= (up-1);
      else
          cnt+=up;
      
      setPwmDc(cnt);
  }
  else
    if( mainCnt < 9){
      if(stepCnt %3 == 0)
        cnt -= (down+1);
      else
         cnt -= down;
      setPwmDc(cnt);
    }
  else
    if(mainCnt <18){
      if(cnt <= down)
          cnt = 0;
      else
        if(stepCnt%5 == 0){
          cnt -= (down+1);
        }
        else
          cnt -= down;
        
        setPwmDc(cnt);
    }
  
  
}
      
void task500ms(){
    mainCnt = (mainCnt + 1)%period;
    if(mainCnt == 9)
       cnt = 100;
    if (mainCnt == 0){
      stepCnt=0;
      cnt = 0;
    }
   
}

void task1000ms(){
 
}


#endif