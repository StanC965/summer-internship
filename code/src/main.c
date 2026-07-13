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
      // Button is pressed, turn on the onboard LED
      led_power_on(LED_ONBOARD); 
    }
    else{
      // Button is not pressed, turn off the onboard LED
      led_power_off(LED_ONBOARD); 
    }
    
  }
  
}