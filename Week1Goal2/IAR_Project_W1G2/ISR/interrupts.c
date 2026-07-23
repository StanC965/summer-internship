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

volatile unsigned long tc0_overflow_count = 0;

volatile unsigned char countdown_active = 0; 
volatile unsigned char seconds_left = 0;     

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

#pragma vector = ADC_vect
__interrupt void ADC_Interrupt_Handler(void) {
    unsigned char low_byte = ADCL;
    unsigned char high_byte = ADCH;
    
    adc_last_result = low_byte | (high_byte << 8);
}

#pragma vector = TIMER0_OVF_vect
__interrupt void TC0_Overflow_Interrupt_Handler(void) {
 
  /*
  tc0_overflow_count++; 
  if (tc0_overflow_count >= 61) {
    Toggle_LED(LED0);
    tc0_overflow_count = 0;
  }*/
  //Toggle_LED(LED0);
  if (countdown_active == 1) {
    tc0_overflow_count++;
    if (tc0_overflow_count >= 61) {
      tc0_overflow_count = 0;
      seconds_left--;
      
      switch(seconds_left) {
        case 4: 
            PowerOff_LED(LED4);
            break;
        case 3: 
            PowerOff_LED(LED3);
            break;
        case 2: 
            PowerOff_LED(LED2);
            break;
        case 1: 
            PowerOff_LED(LED1);
            break;
        case 0: 
            PowerOff_LED(LED0);
            countdown_active = 0;
            break;
      }
    }
  }
}

#endif