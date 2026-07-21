#include "Led.h"

void led_init(){
   DDRD=Led1+Led2;
   DDRA=0x08;
   DDRC=0x80;
   DDRB=Led4;
   PORTC|=0x80;
   PORTA|=0x08;
   PORTD|=Led1+Led2;
   PORTB|=0x08;
}

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
void led0_set_state(unsigned char led_state){
  led_state ? set_pin(&PORTC,PIN7) : reset_pin(&PORTC,PIN7);
}