#include <iom324pb.h>
#include "button.h"
#include "led.h"
#include "delay.h"
#include "timer.h"

volatile uint8_t button_event_detected[BUTTON_COUNT] = {0};
volatile uint8_t light_sensor_value;
volatile uint32_t timer0_overflow_count = 0;

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

#pragma vector = TIMER0_OVF_vect
__interrupt void timer0_overflow_routine(void)
{
    TCNT0 = TIMER0_PRELOAD_VALUE;

    static uint8_t overflow_count = 0;
    overflow_count++;

    if (overflow_count >= OVERFLOWS_PER_SECOND)
    {
        overflow_count = 0;
        led_toggle(LED_ONBOARD);
    }
}