#include "Led.h"


void LedOn(volatile unsigned char *reg,PIN_Number pin){
  reset_pin(reg,pin);
}
void LedOff(volatile unsigned char *reg,PIN_Number pin){
  set_pin(reg,pin);
}
void LedBlinkFast(volatile unsigned char *reg,PIN_Number pin){
  LedOn(reg,pin);
  delay(1);
  LedOff(reg,pin);
  delay(1);
  LedOn(reg,pin);
  delay(1);
  LedOff(reg,pin);
  delay(1);
  LedOn(reg,pin);
  delay(1);
  LedOff(reg,pin);
  delay(1);
  LedOn(reg,pin);
  delay(1);
  LedOff(reg,pin);
  delay(1);
  LedOn(reg,pin);
  delay(1);
  LedOff(reg,pin);
  delay(1);
}
void LedBlinkSlow(volatile unsigned char *reg,PIN_Number pin){
  LedOn(reg,pin);
  delay(2);
  LedOff(reg,pin);
  delay(2);
  LedOn(reg,pin);
  delay(2);
  LedOff(reg,pin);
  delay(2);
  
}