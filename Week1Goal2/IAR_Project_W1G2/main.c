// 331 - CORE
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

    
  }
}
