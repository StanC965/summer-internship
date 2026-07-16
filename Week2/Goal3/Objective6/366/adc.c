#ifndef ADC_C
#define ADC_C

#include "adc.h"

void adc_init(unsigned char adc_channel_pin)
{
    ADMUX = (1 << ADC_REFS_AVCC);
    
    #if defined(ADC_RESOLUTION_8_BIT)
        // Left-adjust result
        ADMUX |= (1 << ADC_LEFT_ADJUST);
    #elif defined(ADC_RESOLUTION_10_BIT)
        // Right-adjust result
        ADMUX &= ~(1 << ADC_LEFT_ADJUST);
    #endif
    
    ADMUX |= (adc_channel_pin & 0x1F);
    
    ADCSRA |= (ADC_PRESCALE_DIV_128  & 0x07);
        
    ADCSRA |= (1 << ADC_INT_ENABLE);
    
    DIDR0 |= (1 << ADC_DIGITAL_INPUT_DISABLE);
    
    ADCSRA |= (1 << ADC_ENABLE);
}

void adc_start_conversion(void)
{
    ADCSRA |= (1 << ADC_ENABLE);
  
    ADCSRA |= (1 << ADC_START);
}

void adc_power_down(void)
{
    ADCSRA &= ~(1 << ADC_ENABLE);
}

adc_result_t adc_get_result(void)
{
    #if defined(ADC_RESOLUTION_8_BIT)
        return ADCH; 
    #elif defined(ADC_RESOLUTION_10_BIT)
        return ADC; 
    #endif
}

#endif