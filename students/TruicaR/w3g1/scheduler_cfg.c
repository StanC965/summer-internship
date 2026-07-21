#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"

#define LED0_PIN  7
#define LED1_PIN  5
#define LED2_PIN  4
#define LED3_PIN  3

#define LIGHT_MIDPOINT  127
#define LIGHT_LEVEL1    64
#define LIGHT_LEVEL2    128
#define LIGHT_LEVEL3    192
#define SW0_PIN  6

static unsigned char sw0_debounce_buffer = 0;
static unsigned char sw0_stable = 0;

void task_10ms(void)
{
    sw0_stable = gpio_debounce_5sample(&sw0_debounce_buffer, &PINC, SW0_PIN, sw0_stable);
}

void task_50ms(void)
{
    adc_start_conversion();  
}

void task_100ms(void)
{
    unsigned char light = adc_get_data();  

    if (light > LIGHT_MIDPOINT) led_on(&PORTC, LED0_PIN); else led_off(&PORTC, LED0_PIN);

    if (light < LIGHT_LEVEL1)
    {
        led_off(&PORTD, LED1_PIN); led_off(&PORTD, LED2_PIN); led_off(&PORTA, LED3_PIN);
    }
    else if (light < LIGHT_LEVEL2)
    {
        led_on(&PORTD, LED1_PIN); led_off(&PORTD, LED2_PIN); led_off(&PORTA, LED3_PIN);
    }
    else if (light < LIGHT_LEVEL3)
    {
        led_on(&PORTD, LED1_PIN); led_on(&PORTD, LED2_PIN); led_off(&PORTA, LED3_PIN);
    }
    else
    {
        led_on(&PORTD, LED1_PIN); led_on(&PORTD, LED2_PIN); led_on(&PORTA, LED3_PIN);
    }
}

void task_500ms(void)  { }
void task_1000ms(void) { }