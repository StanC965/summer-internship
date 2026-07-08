#ifndef LED_H
#define LED_H
#include "gpio.h"

extern void ledInit(unsigned char* DDR,unsigned char* PORT,unsigned char pin);
extern void ledPowerOn(unsigned char led);

extern void ledPowerOff(unsigned char led);

extern void ledBlinkSlow(unsigned char led);
extern void ledBlinkFast(unsigned char led);
#endif