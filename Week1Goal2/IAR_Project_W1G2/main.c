// 332 - 333 - CORE
#include "main.h"


void main( void )
{
  BUTTON_Init();
  LED_Init();
  button_interrupt_init(SW0);
  button_interrupt_init(BUTTON1);
  button_interrupt_init(BUTTON2);
  button_interrupt_init(BUTTON3);

  
  
  while(1){

    if (button_events.sw0_pressed == 1) {
      PowerOff_LED(LED1);
      PowerOff_LED(LED2);
      PowerOff_LED(LED3);
      PowerOn_LED(LED0);
      button_events.sw0_pressed = 0; 
    }
    
    if (button_events.btn1_pressed == 1) {
      Toggle_LED(LED1); 
      button_events.btn1_pressed = 0;
    }
    
    if (button_events.btn2_pressed == 1) {
      Toggle_LED(LED2); 
      button_events.btn2_pressed = 0;
    }
    
    if (button_events.btn3_pressed == 1) {
      Toggle_LED(LED3); 
      button_events.btn3_pressed = 0;
    }
  
    
  }
}
