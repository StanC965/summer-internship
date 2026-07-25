/* 355 - redesign: every module has an init function, and each driver exposes its
   atomic actions as dedicated functions. This main calls init for every module used. */

#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "button.h"
#include "sos.h"
#include "adc.h"

static volatile unsigned char light_value = 0;

#pragma vector=ADC_vect
__interrupt void adc_isr(void)
{
    light_value = adc_get_result();  
}

void main( void )
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);
    button_init(SW0_DDR, SW0_PORT, SW0_PIN);
    sos_init();
    adc_init(ADC_LIGHT_CHANNEL);

    led_power_off(LED0_PORT, LED0_PIN);
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
