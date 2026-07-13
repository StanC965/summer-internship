#include "main.h" 
#include "led.h"
#include "button.h"
#include "sos.h"
#include "delay.h"

void main (void){

  led_init();
  button_init();
  button_enable_pullup(BUTTON_ONBOARD);
  
  uint8_t button_pressed;
  
  while(1){
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      delay(10 * MILISECOND);
      
      button_pressed = button_read(BUTTON_ONBOARD);
      
      if(!button_pressed){
        while(1){
          sos_play(LED_ONBOARD);
          delay(SECOND);
      
        }
      }
    }
  }
}