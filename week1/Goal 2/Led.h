#include "gpio.h"
#include "iom324pb.h"

#define ON 0
#define OFF 1
//DDRD Led 1 POTRD5
#define Led1 0x20
//DDRD Led 2 PORTD4
#define Led2 0x10
//DDRA PORTA3
#define Led3 0x08

void LedOn(volatile unsigned char *reg,PIN_Number pin);
void LedOff(volatile unsigned char *reg,PIN_Number pin);
void LedBlinkFast(volatile unsigned char *reg,PIN_Number pin);
void LedBlinkSlow(volatile unsigned char *reg,PIN_Number pin);
void led0_set_state(unsigned char led_state);
void led_init();