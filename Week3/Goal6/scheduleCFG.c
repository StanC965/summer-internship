#ifndef SCDCFG_C
#define SCDCFG_C
#include "pwm.h"
#include "led.h"




#define top 4
#define step 25
unsigned char cnt = 0;

void task10ms(){
    pwmSetDutyCycle(cnt*step);
    cnt = (cnt + 1)%top;
    
}
      
void task50ms(){
 

}
      
void task100ms(){
}
      
void task500ms(){

}

void task1000ms(){

}

#endif