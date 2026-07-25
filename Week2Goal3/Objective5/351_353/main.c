/* 351-353 - configure the ADC for the light sensor */

#include "iom324pb.h"
#include <intrinsics.h>
#include "adc.h"

static volatile unsigned char light_value = 0;

#pragma vector=ADC_vect
__interrupt void adc_isr(void)
{
    light_value = adc_get_result();  
}

void main( void )
{
    adc_init(ADC_LIGHT_CHANNEL);
    __enable_interrupt();

    while(1)
    {
        adc_start_conversion();
        
        {
            volatile unsigned int i;
            for (i = 0; i < 2000U; i++) { }
        }
    }
}
