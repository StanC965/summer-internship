#ifndef LED_C
#define LED_C
#include "gpio.h"
#include "led.h"
#define OUTPUT 1
void ledInit(unsigned char* DDR, unsigned char* PORT, unsigned char pin){
  setDirection(DDR,pin,OUTPUT);
  setPin(PORT,pin);
}

void ledPowerOn(unsigned char led){
  if(led == 0){
 
    resetPin(&PORTC,7);
    
  }
  else
  if(led == 1){
  
    resetPin(&PORTD,5);
    
  }
  else
  if(led == 2){
   
    resetPin(&PORTD,4);
    
  }
  else
  if(led == 3){
  
    resetPin(&PORTA,3);
    
  }
  else{
    
    resetPin(&PORTB,3);
    
  }
}

void ledPowerOff(unsigned char led){
  if(led == 0){
    
    setPin(&PORTC,7);
    
  }
  else
  if(led == 1){
   
    setPin(&PORTD,5);
    
  }
  else
  if(led == 2){
    
    setPin(&PORTD,4);
    
  }
  else
  if(led == 3){
   
    setPin(&PORTA,3);
    
  }
  else{
    
    setPin(&PORTB,3);
    
  }
}


void ledBlinkSlow(unsigned char led){
  ledPowerOn(led);
  for(int i = 0;i<10000;i++);
  ledPowerOff(led);
  for(int i = 0;i<10000;i++);
  ledPowerOn(led);
  for(int i = 0;i<10000;i++);
  ledPowerOff(led);

}
void ledBlinkFast(unsigned char led){
  ledPowerOn(led);
  for(int i = 0;i<5000;i++);
  ledPowerOff(led);
  for(int i = 0;i<5000;i++);
  ledPowerOn(led);
  for(int i = 0;i<5000;i++);
  ledPowerOff(led);
  for(int i = 0;i<5000;i++);
  ledPowerOn(led);
  for(int i = 0;i<5000;i++);
  ledPowerOff(led);
  for(int i = 0;i<5000;i++);
  ledPowerOn(led);
  for(int i = 0;i<5000;i++);
  ledPowerOff(led);
  for(int i = 0;i<5000;i++);
  ledPowerOn(led);
  for(int i = 0;i<5000;i++);
  ledPowerOff(led);
  for(int i = 0;i<5000;i++);
  ledPowerOn(led);
  for(int i = 0;i<5000;i++);
  ledPowerOff(led);
}

#endif