#include <iom324pb.h>
#include "button.h"
#include "led.h"
#include "delay.h"

volatile uint8_t button_event_detected[BUTTON_COUNT] = {0};
volatile uint8_t light_sensor_value;

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
    (void)ADCL;
    light_sensor_value = ADCH;
}