#include "main.h" 
#include "led.h"
#include "button.h"
#include "sos.h"

void main (void){

  led_init();
  button_init();
  button_enable_pullup(BUTTON_ONBOARD);
  
  while(1){
    sos_play(LED_ONBOARD);
  }
  
}