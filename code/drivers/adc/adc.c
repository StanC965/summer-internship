#ifndef ADC_C
#define ADC_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "adc.h"
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void adc_init(void)
{
    adc_select_internal_voltage();
    adc_select_input_channel(CHANNEL_4);
    adc_configure_control_settings();
    // adc_disable_digital_input(CHANNEL_4);
}

void adc_select_avcc_voltage(void)
{
    ADMUX &= ~(ADC_REFERENCE_MASK);
    ADMUX |= BIT_MASK(REFS0);
    ADMUX |= BIT_MASK(ADLAR);
}

void adc_select_internal_voltage(void)
{
    ADMUX &= ~(ADC_REFERENCE_MASK);
    ADMUX |= BIT_MASK(REFS0);
    ADMUX |= BIT_MASK(REFS1);
    ADMUX |= BIT_MASK(ADLAR);
}

void adc_select_input_channel(uint8_t channel)
{
    ADMUX &= ~(ADC_CHANNEL_MASK);
    ADMUX |= (channel & 0x0F);
}

void adc_configure_control_settings(void)
{
    adc_set_prescaler_64();
    adc_enable_interrupt();
    adc_enable();
}

void adc_set_prescaler_64(void)
{
    ADCSRA &= ~(ADC_PRESCALER_64_MASK);
    ADCSRA |= ADC_PRESCALER_64_DIVISON_MASK;
}

void adc_enable_interrupt(void)
{
    ADCSRA |= BIT_MASK(ADIE);
}

void adc_enable(void)
{
    ADCSRA |= BIT_MASK(ADEN);
}

void adc_disable_digital_input(uint8_t channel)
{
    DIDR0 |= (1 << channel);
}

void adc_start_conversion(void)
{
    ADCSRA |= BIT_MASK(ADSC);
}

uint8_t adc_get_conversion_result(void)
{
    return ADCH;
}

#endif /* ADC_C */
