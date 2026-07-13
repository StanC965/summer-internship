#ifndef SCDCFG_C
#define SCDCFG_C
#include "pwm.h"
#include "led.h"

#define led0 0


enum states{ 
  LED_ON,
  LED_OFF};
enum states state = LED_OFF;


void stateMachine(void){
  switch (state){
      case LED_ON:
        ledPowerOn(led0);
        state = LED_OFF;
        break;
      case LED_OFF:
        ledPowerOff(led0);
        state = LED_ON;
  }
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