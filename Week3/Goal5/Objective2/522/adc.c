#ifndef ADC_C
#define ADC_C

#include "adc.h"

static volatile adc_result_t adc_latest_result = 0;

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

adc_result_t adc_get_data(void)
{
    return adc_latest_result;
}

#pragma vector = ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_latest_result = ADC_MAX_VAL - adc_get_result();
    
    adc_power_down();
}

#endif