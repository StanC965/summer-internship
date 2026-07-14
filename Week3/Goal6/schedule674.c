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

void ledOn2s();
void ledOff();
void ledOn();
void ledOff3s();

void (*statefunc)() = ledOn2s;

void ledOn2s(){
  ledPowerOn(led0);
  if(secs >= 1){
    statefunc = ledOff;
    secs = 0;
  }
}

void ledOff(){
  ledPowerOff(led0);
  statefunc = ledOn;
  
}

void ledOn(){
  ledPowerOn(led0);
   statefunc = ledOff3s;
   secs = 0;
}

void ledOff3s(){
  ledPowerOff(led0);
  if(secs >= 2){
    statefunc = ledOn2s;
    secs = 0;
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
  (*statefunc)();
  secs++;
}

#endif