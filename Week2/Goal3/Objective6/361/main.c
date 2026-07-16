#include "adc.h"
#include "led.h"
#include "intrinsics.h"

#define ADC_MIDPOINT_THRESHOLD   127

volatile unsigned char adc_latest_result = 0;

#pragma vector = ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_latest_result = adc_get_result();
}

void init_system(void)
{
    gpio_init();
    
    led_init();
    
    adc_init(ADC_LIGHT_SENSOR_CHANNEL);
    
    __enable_interrupt();
}

void main()
{
    init_system();
  
    adc_start_conversion();
    
    while (1)
    {
        if (adc_latest_result > ADC_MIDPOINT_THRESHOLD)
        {
            led_power_on(LED_LED0_PORT, LED_LED0_PIN);
        }
        else
        {
            led_power_off(LED_LED0_PORT, LED_LED0_PIN);
        }
        
        adc_start_conversion();
    }
}
