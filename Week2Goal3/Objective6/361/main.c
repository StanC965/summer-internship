/* 361 - Ambient Light Application: read the light sensor with the ADC (ISR) and
   turn ON LED0 when the reading is above the midpoint of the range (dark ambient). */

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
    }
}
