#ifndef SOS_C
#define SOS_C
#include "led.h"

void ledPoint(unsigned char led){
    for(long i = 0;i<50000;i++);
    
    ledPowerOn(led);
    for(long i = 0;i<50000;i++);
    
    ledPowerOff(led);
    for(long i = 0;i<50000;i++);
    ledPowerOn(led);
    for(long i = 0;i<50000;i++);
    ledPowerOff(led);
    for(long i = 0;i<50000;i++);
    ledPowerOn(led);
    for(long i = 0;i<50000;i++);
    ledPowerOff(led);
      
}

void ledLine(unsigned char led){
    for(long i = 0;i<50000;i++);
    ledPowerOn(led);
    for(long i = 0;i<100000;i++);
    ledPowerOff(led);
    for(long i = 0;i<50000;i++);
    ledPowerOn(led);
    for(long i = 0;i<100000;i++);
    ledPowerOff(led);
    for(long i = 0;i<50000;i++);
    ledPowerOn(led);
    for(long i = 0;i<100000;i++);
    ledPowerOff(led);
      
}

void ledSos(unsigned char led){
  ledPoint(led);
  ledLine(led);
  ledPoint(led);
} 



#endif