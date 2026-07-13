#ifndef SCDHEART_C
#define SCDHEART_C
#include "pwm.h"
#include "led.h"

#define led4 4

#define period 34

#define up 5
#define down 2


#define top 256
#define step 25
unsigned char cnt = 0;
unsigned char mainCnt = 0;
unsigned short int stepCnt = 0;
const unsigned char sinTable[] = {0, 0, 0, 1, 1, 1, 1, 2, 2, 21,41, 60, 80, 57, 33, 10, 33, 55,78, 100, 92, 85, 77, 69, 62, 54,46, 38, 31, 23, 15, 8, 0};
void task10ms(){
    
    
}
      
void task50ms(){
  setPwmDc(sinTable[cnt]);
  cnt = (cnt+1)%period;

}
      
void task100ms(){
  
  
  
}
      
void task500ms(){
}

void task1000ms(){
 
}


#endif