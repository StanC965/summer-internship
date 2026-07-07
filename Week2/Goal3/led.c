#ifndef LED_C
#define LED_C
#include "gpio.h"
#include "led.h"
void PowerOn_LED(unsigned char led){
  if(led == 0){
 
    reset_pin(&PORTC,7);
    
  }
  else
  if(led == 1){
  
    reset_pin(&PORTD,5);
    
  }
  else
  if(led == 2){
   
    reset_pin(&PORTD,4);
    
  }
  else
  if(led == 3){
  
    reset_pin(&PORTA,3);
    
  }
  else{
    
    reset_pin(&PORTB,3);
    
  }
}

void PowerOff_LED(unsigned char led){
  if(led == 0){
    
    set_pin(&PORTC,7);
    
  }
  else
  if(led == 1){
   
    set_pin(&PORTD,5);
    
  }
  else
  if(led == 2){
    
    set_pin(&PORTD,4);
    
  }
  else
  if(led == 3){
   
    set_pin(&PORTA,3);
    
  }
  else{
    
    set_pin(&PORTB,3);
    
  }
}


void LED_Blink_slow(unsigned char led){
  PowerOn_LED(led);
  for(int i = 0;i<10000;i++);
  PowerOff_LED(led);
  for(int i = 0;i<10000;i++);
  PowerOn_LED(led);
  for(int i = 0;i<10000;i++);
  PowerOff_LED(led);

}
void LED_Blink_fast(unsigned char led){
  PowerOn_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOff_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOn_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOff_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOn_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOff_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOn_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOff_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOn_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOff_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOn_LED(led);
  for(int i = 0;i<5000;i++);
  PowerOff_LED(led);
}

#endif