#include "main.h" 
#include "led.h"
#include "delay.h"
#include "gpio.h"
#include "button.h"

void main (void){

  led_init();
  button_init();
  button_enable_pullup(BUTTON_ONBOARD);
  
  uint8_t button_pressed;
  
  while(1){
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      delay((SECOND / 1000) * 10);
      button_pressed = button_read(BUTTON_ONBOARD);
      
      if(!button_pressed){
        led_power_on(LED_ONBOARD);

        delay((SECOND / 1000) * 10));
      }

    }

    else{
      led_power_off(LED_ONBOARD); 

    }
    
  }
  
}