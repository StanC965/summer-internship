#ifndef SCDCFG_C
#define SCDCFG_C
#include "pwm.h"
#include "led.h"

#define led0 0


enum states{ 
  LED_ON2S,
  LED_OFF1S,
  LED_ON1S,
  LED_OFF3S
};
enum states state = LED_ON2S;
unsigned char secs = 0;


void stateMachine(void){
  switch (state){
      case LED_ON2S:
        ledPowerOn(led0);
        if(secs >= 1){
          state = LED_OFF1S;
          secs = 0;
        }
        break;
      case LED_OFF1S:
        ledPowerOff(led0);
        state = LED_ON1S;
        break;
      case LED_ON1S:
        ledPowerOn(led0);
        state = LED_OFF3S;
        secs = 0;
        break;
      case LED_OFF3S:
        ledPowerOff(led0);
        if(secs >= 2){
          state = LED_ON2S;
          secs = 0;
          
        }
        break;
  }   
  secs ++;
}

void task10ms(){
    
    
}
      
void task50ms(){
 

}
      
void task100ms(){
}
      
void task500ms(){

}

void task1000ms(){
  stateMachine();
}

#endif