#include "adc.h"
#include "led.h"
#include "intrinsics.h"

#define THRESHOLD_SEMI_DARK      256   
#define THRESHOLD_SEMI_LIGHT     512  
#define THRESHOLD_FULL_LIGHT     768

volatile unsigned int adc_latest_result = 0;

#pragma vector = ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_latest_result = 1023 - adc_get_result();
    
    adc_power_down();
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
        if (adc_latest_result >= THRESHOLD_FULL_LIGHT)
        {
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
            led_power_on(LED_OLED_3_PORT, LED_OLED_3_PIN);
        }
        else if (adc_latest_result >= THRESHOLD_SEMI_LIGHT)
        {
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
            led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
        }
        else if (adc_latest_result >= THRESHOLD_SEMI_DARK)
        {
            led_power_on(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
            led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
            led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
        }
        else
        {
            led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
            led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
            led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
        }
        
        adc_start_conversion();
    }
}
