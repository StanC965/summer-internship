#ifndef SCDCFG_C
#define SCDCFG_C
#include "pwm.h"
#include "led.h"

#define led4 4

#define period 12

#define up 5

#define top 256
#define step 25
unsigned char cnt = 0;
unsigned char mainCnt = 0;

void task10ms(){
    
}
      
void task50ms(){
 

}
      
void task100ms(){
  
  if(mainCnt >= 0 && mainCnt < 2){
      cnt+= up;
      setPwmDc(cnt);
  }
  else
    if(mainCnt >= 7 && mainCnt < 9){
      cnt -= up;
      setPwmDc(cnt);
    }
  
  
}
      
void task500ms(){

}

void task1000ms(){
  if(mainCnt == 2){
    setPwmDc(cnt);
   
  }
  else 
    if(mainCnt == 3){
      setPwmDc(0);
      
    }
    else        
      if(mainCnt == 4){
        setPwmDc(cnt);
       
      }
      else
        if(mainCnt == 5){
          setPwmDc(0);
          
        }
        else
          if(mainCnt == 6){
           setPwmDc(cnt);
            
          }
        else
          if(mainCnt >= 9 && mainCnt <12){
            setPwmDc(0);}
        
  mainCnt = (mainCnt + 1)%period;
}


#endif