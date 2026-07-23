/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       tc0.c
 *  \brief      Modular Timer/Counter 0 (TC0) Driver Implementation
 *  \author     Chirila Viorel
 *  \date       22.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define ENABLE_BIT_DEFINITIONS
#include <iom324pb.h>
#include "tc0.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void tc0_init(const tc0_config_t *config) {
  
  // Temporary variables to hold register values before writing them to hardware
  unsigned char tccr0a_temp = 0;
  unsigned char tccr0b_temp = 0;
  unsigned char timsk0_temp = 0;

  switch(config->mode) {
      case TC0_MODE_NORMAL:
          // All WGM bits are 0 by default. Nothing to set.
          break;
          
      case TC0_MODE_CTC:
          tccr0a_temp |= (1 << WGM01); // WGM02=0, WGM01=1, WGM00=0
          break;
          
      case TC0_MODE_FAST_PWM:
          tccr0a_temp |= (1 << WGM01) | (1 << WGM00); // WGM02=0, WGM01=1, WGM00=1
          break;
          
      default:
          break; 
  }

  if (config->interrupt_overflow == 1) {
      timsk0_temp |= (1 << TOIE0);
  }
  if (config->interrupt_compare_a == 1) {
      timsk0_temp |= (1 << OCIE0A);
  }
  if (config->interrupt_compare_b == 1) {
      timsk0_temp |= (1 << OCIE0B);
  }


  // PRESCALER CONFIGURATION (CS Bits)
  tccr0b_temp |= (unsigned char)config->prescaler; 
  
  // Stop the timer before applying new settings
  TCCR0B = 0x00; 
  
  // Write registers
  TCCR0A = tccr0a_temp;
  TIMSK0 = timsk0_temp;
  
  OCR0A  = config->ocr0a_value;
  
  // Write TCCR0B last
  TCCR0B = tccr0b_temp; 
}