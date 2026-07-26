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

volatile unsigned int adc_last_result = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void adc_init(void) {

  // REFS0 = 1 : Set Voltage Reference to AVCC (3.3V).
  // ADLAR = 1 : Left-adjust the 10-bit result (allows reading just ADCH for 8-bit).
  // MUX   = 4 : Select ADC4 channel (connected to PA4 / light sensor).
  //ADMUX = (1 << REFS0) | (1 << ADLAR) | 4;
  
  // ADMUX: Removed (1 << ADLAR). Right-alignment is the default state (0).
  // REFS0 = 1 sets VREF to AVCC (3.3V). MUX = 4 selects PA4.
  ADMUX = (1 << REFS0) | 4;

  // ADEN = 1 : Enable the ADC hardware (Power ON).
  // ADIE = 1 : Enable ADC Interrupts (triggers ADC_vect when conversion is done).
  // Note     : No prescaler and no Auto-Trigger used (Single Conversion mode).  
  //ADCSRA = (1 << ADEN) | (1 << ADIE);
  
  // ADCSRA: Set the prescaler to 128 by enabling all 3 ADPS bits.
  // System Clock (16 MHz) / 128 = 125 kHz ADC Clock (optimal for 10-bit).
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void adc_start_conversion(void) {
    ADCSRA |= (1 << ADSC);
}

unsigned int adc_get_result(void) {
    return adc_last_result;
}

#endif