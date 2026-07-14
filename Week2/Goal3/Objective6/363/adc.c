#ifndef ADC_C
#define ADC_C

#include "adc.h"

void adc_init(unsigned char adc_channel_pin)
{
    ADMUX = (1 << ADC_REFS_AVCC) | (1 << ADC_LEFT_ADJUST);
    
    ADMUX |= (adc_channel_pin & 0x1F);
        
    ADCSRA |= (1 << ADC_INT_ENABLE);
    
    DIDR0 |= (1 << ADC_DIGITAL_INPUT_DISABLE);
    
    ADCSRA |= (1 << ADC_ENABLE);
}

void adc_start_conversion(void)
{
    ADCSRA |= (1 << ADC_ENABLE);
  
    ADCSRA |= (1 << ADC_START);
}

unsigned char adc_get_result(void)
{
    return ADCH;
}

void adc_power_down(void)
{
    ADCSRA &= ~(1 << ADC_ENABLE);
}

#endif