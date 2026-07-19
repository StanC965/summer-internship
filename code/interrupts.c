#include <iom324pb.h>
#include "button.h"
#include "led.h"
#include "delay.h"
#include "adc.h"

volatile uint8_t button_event_detected[BUTTON_COUNT] = {0};
#ifdef ADC_RESOLUTION_10_BIT
volatile uint16_t light_sensor_value = 0;
#else
volatile uint8_t light_sensor_value = 0;
#endif

#pragma vector = PCINT0_vect
__interrupt void button_porta_routine(void)
{
    button_event_detected[BUTTON_OLED1_2] = 1;
    button_event_detected[BUTTON_OLED1_3] = 1;
}

#pragma vector = PCINT2_vect
__interrupt void button_portc_routine(void)
{
    button_event_detected[BUTTON_ONBOARD] = 1;
    button_event_detected[BUTTON_OLED1_1] = 1;
}

#pragma vector = ADC_vect
__interrupt void adc_routine(void)
{
    light_sensor_value = adc_get_conversion_result();
}