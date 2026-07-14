#ifndef SCDCFGBMW_C
#define SCDCFGBMW_C
#include "adc.h"
#include "led.h"

#define led0 0
#define led1 1
#define led2 2
#define led3 3

#define ON 1
#define OFF 0

int led0State = 0;
int led1State = 0;
int led2State = 0;
int led3State = 0;

#define PC6 6
#define PC1 1
#define PA0 0
#define PA1 1

#define lim 10

volatile unsigned char blinkFast = 0;
unsigned char led0BlinkState = 0;
unsigned char cnt = 0;

unsigned char button0Buffer = 0;
unsigned char button1Buffer = 0;
unsigned char button2Buffer = 0;
unsigned char button3Buffer = 0;

unsigned char button0State = 0;
unsigned char button1State = 0;
unsigned char button2State = 0;
unsigned char button3State = 0;

unsigned char lastButton0State = 0;
unsigned char lastButton1State = 0;
unsigned char lastButton2State = 0;
unsigned char lastButton3State = 0;

#define PRESSED  1
#define RELEASED 0

#define debounceValUp 0x1F
#define debounceValDown 0x00

void led0Funtionality(){
  ledPowerOn(led0);
  ledPowerOff(led1);
  ledPowerOff(led2);
  ledPowerOff(led3);
}


void led0FunctionalityReversed(){
  ledPowerOff(led0);
   if(led1State == ON)
            ledPowerOn(led1);
        else
            ledPowerOff(led1);
  if(led2State == ON)
          ledPowerOn(led2); 
        else
          ledPowerOff(led2);
  if(led3State == ON)
        ledPowerOn(led3);
    else
      ledPowerOff(led3);
}


void debounceButton(volatile unsigned char *PIN,unsigned char pin,unsigned char *buffer,unsigned char *state)
{
    *buffer <<= 1;

    if(!getPin(PIN, pin))
        *buffer |= 1;

    if((*buffer & debounceValUp)== debounceValUp)
        *state =PRESSED;
    else if((*buffer & debounceValUp)== debounceValDown)
        *state = RELEASED;
}

void task10ms(){
  debounceButton(&PINC, PC6, &button0Buffer, &button0State);
  debounceButton(&PINC, PC1, &button1Buffer, &button1State);
  debounceButton(&PINA, PA0, &button2Buffer, &button2State);
  debounceButton(&PINA, PA1, &button3Buffer, &button3State);
  if(button0State == PRESSED && lastButton0State == RELEASED){
      led0State ^= 1;
      if(led0State == ON){
        led0Funtionality();
      }
      else
          led0FunctionalityReversed();
      
  }
  lastButton0State = button0State;
      if(button1State == PRESSED && lastButton1State == RELEASED){
    if(led0State == ON){
        blinkFast |= ON;
        ledPowerOn(led0);}
    else{
        led1State ^= 1;
        if(led1State == ON)
            ledPowerOn(led1);
        else
          ledPowerOff(led1);}
  }
      
  lastButton1State = button1State;
      if(button2State == PRESSED && lastButton2State == RELEASED){
      if(led0State == ON){
        blinkFast |= ON;
        ledPowerOn(led0);}
    else{
        led2State ^= 1;
        if(led2State == ON)
          ledPowerOn(led2); 
        else
          ledPowerOff(led2);}
    }
     
    lastButton2State = button2State;
     if(button3State == PRESSED && lastButton3State == RELEASED){
          if(led0State == ON){
            blinkFast |= ON;
            ledPowerOn(led0);}
        else{
              led3State ^= 1;
              if(led3State == ON)
                ledPowerOn(led3);
              else
              ledPowerOff(led3);
            }
        }
     
lastButton3State = button3State;
}
      
void task50ms(){
  if(led0State == ON){
      if(blinkFast)
      {
          cnt++;
          led0BlinkState ^= 1;

          if(led0BlinkState)
              ledPowerOn(led0);
          else
              ledPowerOff(led0);
          if(cnt == lim){
            cnt =0;
            blinkFast = OFF;
          }
      }
      else
        ledPowerOn(led0);
  }

}
      
void task100ms(){
  

}
      
void task500ms(){

}

void task1000ms(){

}

#endif