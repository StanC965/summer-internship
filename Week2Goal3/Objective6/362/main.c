/* 362 */

#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "adc.h"
#include "ambient.h"

static volatile unsigned char light_value = 0;

#pragma vector=ADC_vect
__interrupt void adc_isr(void)
{
    light_value = adc_get_result();   
}

void main( void )
{
    gpio_init();
    ambient_init();
    adc_init(ADC_LIGHT_CHANNEL);

    __enable_interrupt();

    while(1)
    {
        adc_start_conversion();

        {
            volatile unsigned int i;
            for (i = 0; i < 2000U; i++) { }
        }

        ambient_indicate_threshold(light_value);   
        ambient_indicate_level(light_value);        
    }
}
