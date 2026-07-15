// 316 - CORE
#include "main.h"
#include <intrinsics.h>

static unsigned char previous_state =1;

#pragma vector = PCINT2_vect
__interrupt void SW0_Interrupt_Handler(void) {

  if (button_read_state(SW0) == 0) {
  
    previous_state = !previous_state;
      
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
  interrupt_init();
  
  while(1){

    SOS_play(LED0, &previous_state);
    
  }
}
