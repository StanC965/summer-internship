#include "Led.h"


void LedOn(volatile unsigned char *reg,PIN_Number pin){
  reset_pin(reg,pin);
}
void LedOff(volatile unsigned char *reg,PIN_Number pin){
  set_pin(reg,pin);
}