#include "sos.h"
#include "button.h"
#include "intrinsics.h"

#define ADLAR_LEFT_ADJUST       5   
#define REFS0_AVCC              6 
#define MUX_ADC4                2
#define ADIE_INT_ENABLE         3 
#define ADEN_ENABLE             7
#define ADSC_START_CONVERSION   6

volatile unsigned char adc_latest_result = 0;

#pragma vector = ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_latest_result = ADCH;
    
}

void adc_init_sensor()
{
    ADMUX = (1 << REFS0_AVCC) | (1 << ADLAR_LEFT_ADJUST);
    
    ADMUX |= (1 << MUX_ADC4); 
        
    ADCSRA |= (1 << ADIE_INT_ENABLE);
    
    ADCSRA |= (1 << ADEN_ENABLE);
    
    __enable_interrupt();
}

void adc_start_measurement(void)
{
    ADCSRA |= (1 << ADSC_START_CONVERSION);
}

void main()
{
    adc_init_sensor();
  
    adc_start_measurement();
    
    while (1)
    {
        
    }
}
