#include "gpio.h"

void LedOn(volatile unsigned char *reg,PIN_Number pin);
void LedOff(volatile unsigned char *reg,PIN_Number pin);
void LedBlinkFast(volatile unsigned char *reg,PIN_Number pin);
void LedBlinkSlow(volatile unsigned char *reg,PIN_Number pin);