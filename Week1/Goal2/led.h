#ifndef LED_H
#define LED_H
#include "gpio.h"


extern void PowerOn_LED(unsigned char led);

extern void PowerOff_LED(unsigned char led);

extern void LED_Blink_slow(unsigned char led);
extern void LED_Blink_fast(unsigned char led);
#endif