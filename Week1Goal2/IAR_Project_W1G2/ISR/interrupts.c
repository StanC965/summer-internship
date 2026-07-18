#ifndef INTERRUPTS_C
#define INTERRUPTS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       interrupts.c
 *  \brief      interrupts module implementation.
 *  \author     Chirila Viorel
 *  \date       18.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "Modules/led.h"
#include "Modules/button.h"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#pragma vector = PCINT0_vect
__interrupt void PortA_Interrupt_Handler(void) {
    
  if (button_read_state(BUTTON2) == BUTTON_PRESSED) {
    PowerOn_LED(LED2);
  }
  else{
    PowerOff_LED(LED2);
  }

  if (button_read_state(BUTTON3) == BUTTON_PRESSED) {
    PowerOn_LED(LED3);
  }else{
    PowerOff_LED(LED3);
  }
}


#pragma vector = PCINT2_vect
__interrupt void PortC_Interrupt_Handler(void) {
    
  if (button_read_state(SW0) == BUTTON_PRESSED) {
    PowerOn_LED(LED0);
  }
  else{
    PowerOff_LED(LED0);
  }

  if (button_read_state(BUTTON1) == BUTTON_PRESSED) {
    PowerOn_LED(LED1);
  }else{
    PowerOff_LED(LED1);
  }
}

#endif