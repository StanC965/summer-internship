#ifndef ADC_C
#define ADC_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       adc.h
 *  \brief      ADC Driver module interface.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "adc.h"

volatile unsigned char adc_last_result = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void adc_init(void) {

  // REFS0 = 1 : Set Voltage Reference to AVCC (3.3V).
  // ADLAR = 1 : Left-adjust the 10-bit result (allows reading just ADCH for 8-bit).
  // MUX   = 4 : Select ADC4 channel (connected to PA4 / light sensor).
  ADMUX = (1 << REFS0) | (1 << ADLAR) | 4;

  // ADEN = 1 : Enable the ADC hardware (Power ON).
  // ADIE = 1 : Enable ADC Interrupts (triggers ADC_vect when conversion is done).
  // Note     : No prescaler and no Auto-Trigger used (Single Conversion mode).  
  ADCSRA = (1 << ADEN) | (1 << ADIE);
}

void adc_start_conversion(void) {
    ADCSRA |= (1 << ADSC);
}

unsigned char adc_get_result(void) {
    return adc_last_result;
}

#endif