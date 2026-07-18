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

#include "interrupts.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Pubplic objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

volatile button_events_t button_events = {0, 0, 0, 0};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#pragma vector = PCINT0_vect
__interrupt void PortA_Interrupt_Handler(void) {
    
  if (button_read_state(BUTTON2) == BUTTON_PRESSED) {
    button_events.btn2_pressed = 1;
  }

  if (button_read_state(BUTTON3) == BUTTON_PRESSED) {
    button_events.btn3_pressed = 1;
  }
}


#pragma vector = PCINT2_vect
__interrupt void PortC_Interrupt_Handler(void) {
    
  if (button_read_state(SW0) == BUTTON_PRESSED) {
    button_events.sw0_pressed = 1;
  }

  if (button_read_state(BUTTON1) == BUTTON_PRESSED) {
    button_events.btn1_pressed = 1;
  }
}

#endif