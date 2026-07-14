#ifndef SCDCFGBMWMCU2_C
#define SCDCFGBMWMCU2_C
#include "adc.h"
#include "led.h"
#include "gpio.h"
#include "usart.h"

#define led0 'A'
#define led1 'B'
#define led2 'C'
#define led3 'D'

#define l0 0
#define l1 1
#define l2 2
#define l3 3

#define led0Off 'E'
#define led1Off 'F'
#define led2Off 'G'
#define led3Off 'H'




void task10msSlave(){
  switch(receiveUsart()){
    case led0:
      ledPowerOn(l0);
      break;
    case led0Off:
      ledPowerOff(l0);
       break;
     case led1:
      ledPowerOn(l1);
      break;
    case led1Off:
      ledPowerOff(l1);
       break;
     case led2:
      ledPowerOn(l2);
      break;
    case led2Off:
      ledPowerOff(l2);
       break;
    case led3:
      ledPowerOn(l3);
      break;
    case led3Off:
      ledPowerOff(l3);
       break;
      default:
      break;
  
  
  
  
  }
}
      
void task50msSlave(){


}
      
void task100msSlave(){
  

}
      
void task500msSlave(){

}

void task1000msSlave(){

}

#endif