#ifndef SCDCFG_C
#define SCDCFG_C
#include "adc.h"
#include "led.h"

#define led0 0
#define led1 1
#define led2 2
#define led3 3



#define dark 100
#define semiDark 80
#define semiLight 40

void task10ms(){
  unsigned short int value = getAdcValue();
  
  disableAdc();
  
  if(value < semiLight)
  {
    ledPowerOn(led1);
      ledPowerOn(led2);
      ledPowerOn(led3);
  }
  else
    if(value >= semiLight && value < semiDark){
      ledPowerOn(led1);
      ledPowerOn(led2);
      ledPowerOff(led3);
    }
  else
    if(value >= semiDark && value < dark){
      ledPowerOn(led1);
      ledPowerOff(led2);
      ledPowerOff(led3);
    }
    else{
    ledPowerOff(led1);
      ledPowerOff(led2);
      ledPowerOff(led3);
    }
}
      
void task50ms(){
 
 enableAdc();
  startConversionAdc();
}
      
void task100ms(){
}
      
void task500ms(){

}

void task1000ms(){

}

#endif