#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"
#include "tc1.h"
#include "scheduler.h"
#include <intrinsics.h>

#define LIGHT_SENSOR_ADC_CHANNEL  4
#define LED0_PIN  7
#define LED1_PIN  5
#define LED2_PIN  4
#define LED3_PIN  3

void main(void)
{
    gpio_set_direction(&DDRC, LED0_PIN, 1);
    gpio_set_direction(&DDRD, LED1_PIN, 1);
    gpio_set_direction(&DDRD, LED2_PIN, 1);
    gpio_set_direction(&DDRA, LED3_PIN, 1);

    led_off(&PORTC, LED0_PIN);
    led_off(&PORTD, LED1_PIN);
    led_off(&PORTD, LED2_PIN);
    led_off(&PORTA, LED3_PIN);

    adc_init(LIGHT_SENSOR_ADC_CHANNEL);

    tc1_systick_init();
    __enable_interrupt();

    schedule_tasks_dispatcher();
}