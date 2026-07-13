// 255 - CORE
#include "main.h"


void main( void )
{
  LED_Init();
  BUTTON_Init();

  unsigned char button_state;
  int pressed_confidence_level = 0;
  int released_confidence_level = 0;
  
  
  while(1){
    
    button_state = button_read_state(SW0);
    if(button_state == 0){
      pressed_confidence_level++;
      if(pressed_confidence_level >PRESSED_CONFIDENCE_LEVEL_TARGET){
        PowerOn_LED(LED0);
        pressed_confidence_level = 0;
      }
    }else{
      released_confidence_level++;
      if(released_confidence_level >RELEASED_CONFIDENCE_LEVEL_TARGET){
        PowerOff_LED(LED0);
        released_confidence_level = 0;
      }
    }
  }
}
