#include "gpio.h"
#include "iom324pb.h"

#define ON 0
#define OFF 1

void LedOn(volatile unsigned char *reg,PIN_Number pin);
void LedOff(volatile unsigned char *reg,PIN_Number pin);
void LedBlinkFast(volatile unsigned char *reg,PIN_Number pin);
void LedBlinkSlow(volatile unsigned char *reg,PIN_Number pin);
void led0_set_state(unsigned char led_state);