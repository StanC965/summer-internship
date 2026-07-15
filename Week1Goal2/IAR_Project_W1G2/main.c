// 311-315 - CORE
#include "main.h"
#include <intrinsics.h>

#pragma vector = PCINT2_vect
__interrupt void SW0_Interrupt_Handler(void) {

  if (button_read_state(SW0) == 0) {
  
    PowerOn_LED(LED0);
      
  }
}

void interrupt_init(){
  
  PCMSK2 |= (1 << 6);
  PCICR |= (1 << 2);
  
  __enable_interrupt();
}

void main( void )
{
  BUTTON_Init();
  led_init(LED0);
  interrupt_init();
  
  while(1){
    
    
  }
}
