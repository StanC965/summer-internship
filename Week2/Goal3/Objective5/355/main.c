#include "adc.h"
#include "intrinsics.h"

#define ADLAR_LEFT_ADJUST       5   
#define REFS_AVCC               6 
#define REFS_1V                 7
#define MUX_ADC4                2
#define ADIE_INT_ENABLE         3 
#define ADEN_ENABLE             7
#define ADSC_START_CONVERSION   6

volatile unsigned char adc_latest_result = 0;

#pragma vector = ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_latest_result = adc_get_result();
}

void main()
{
    __enable_interrupt();
    
    adc_init(ADC_LIGHT_SENSOR_CHANNEL);
    
    adc_start_conversion();
    
    while (1)
    {
        
    }
}
