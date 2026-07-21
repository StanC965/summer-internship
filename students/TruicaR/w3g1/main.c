#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"
#include "tc1.h"
#include "scheduler.h"
#include <intrinsics.h>

#define LIGHT_SENSOR_ADC_CHANNEL  4

#define LED0_PIN     7
#define LED1_PIN     5
#define LED2_PIN     4
#define LED3_PIN     3

#define SW0_PIN      6
#define BUTTON1_PIN  1
#define BUTTON2_PIN  0
#define BUTTON3_PIN  1

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


    gpio_set_direction(&DDRC, SW0_PIN, 0);
    gpio_set_pin(&PORTC, SW0_PIN);

    gpio_set_direction(&DDRC, BUTTON1_PIN, 0);
    gpio_set_pin(&PORTC, BUTTON1_PIN);

    gpio_set_direction(&DDRA, BUTTON2_PIN, 0);
    gpio_set_pin(&PORTA, BUTTON2_PIN);

    gpio_set_direction(&DDRA, BUTTON3_PIN, 0);
    gpio_set_pin(&PORTA, BUTTON3_PIN);

    adc_init(LIGHT_SENSOR_ADC_CHANNEL);

    tc1_systick_init();
    __enable_interrupt();

    schedule_tasks_dispatcher();
}