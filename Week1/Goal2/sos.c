#ifndef SOS_C
#define SOS_C
#include "led.h"

void POINT(unsigned char led){
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

void LINE(unsigned char led){
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




#endif