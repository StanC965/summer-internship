#ifndef SOS_C
#define SOS_C
#include "led.h"

void ledPoint(unsigned char led){
    for(long i = 0;i<50000;i++);
    PowerOn_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOff_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOn_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOff_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOn_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOff_LED(led);
      
}

void ledLine(unsigned char led){
    for(long i = 0;i<50000;i++);
    PowerOn_LED(led);
    for(long i = 0;i<100000;i++);
    PowerOff_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOn_LED(led);
    for(long i = 0;i<100000;i++);
    PowerOff_LED(led);
    for(long i = 0;i<50000;i++);
    PowerOn_LED(led);
    for(long i = 0;i<100000;i++);
    PowerOff_LED(led);
      
}

void ledSos(unsigned char led){
  POINT(led);
  LINE(led);
  POINT(led);
} 



#endif