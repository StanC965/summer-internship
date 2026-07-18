// 334 - CORE
#include "main.h"

void System_Init(void){
  BUTTON_Init();
  LED_Init();
  button_interrupt_init(SW0);
  button_interrupt_init(BUTTON1);
  button_interrupt_init(BUTTON2);
  button_interrupt_init(BUTTON3);
}

void main( void )
{
  System_Init();
  
  while(1){

    Handle_MasterControl_Event();
        
    Handle_VentControl_Event(BUTTON1, LED1, &button_events.btn1_pressed);
    Handle_VentControl_Event(BUTTON2, LED2, &button_events.btn2_pressed);
    Handle_VentControl_Event(BUTTON3, LED3, &button_events.btn3_pressed);
  
  }
}
