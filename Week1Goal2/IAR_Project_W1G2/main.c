// 262 - CORE
#include "main.h"



void main( void )
{
  BUTTON_Init();

  unsigned char button_state;
  unsigned char pressed = 0;
  
  while(1){
    
    button_state = button_read_state(SW0);
    if(button_state == 0){
      SOS_play(LED0); 
    }
  }
}
