#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"

#define SW0_PIN      6
#define BUTTON1_PIN  1
#define BUTTON2_PIN  0
#define BUTTON3_PIN  1
#define LED1_PIN     5
#define LED2_PIN     4
#define LED3_PIN     3
#define LED0_PIN     7

#define LIGHT_MIDPOINT  127
#define LIGHT_LEVEL1    64
#define LIGHT_LEVEL2    128
#define LIGHT_LEVEL3    192

static unsigned char sw0_buf = 0,     sw0_stable = 0,     sw0_prev = 0;
static unsigned char b1_buf = 0,      b1_stable = 0,      b1_prev = 0;
static unsigned char b2_buf = 0,      b2_stable = 0,      b2_prev = 0;
static unsigned char b3_buf = 0,      b3_stable = 0,      b3_prev = 0;

static unsigned char led1_state = 0, led2_state = 0, led3_state = 0;
static volatile unsigned char panel_blocked = 0;

void task_10ms(void)
{
    sw0_stable = gpio_debounce_5sample(&sw0_buf, &PINC, SW0_PIN, sw0_stable);
    b1_stable  = gpio_debounce_5sample(&b1_buf,  &PINC, BUTTON1_PIN, b1_stable);
    b2_stable  = gpio_debounce_5sample(&b2_buf,  &PINA, BUTTON2_PIN, b2_stable);
    b3_stable  = gpio_debounce_5sample(&b3_buf,  &PINA, BUTTON3_PIN, b3_stable);

    if (sw0_stable && !sw0_prev)  
    {
        panel_blocked = !panel_blocked;
        if (!panel_blocked)
        {
            led_off(&PORTD, LED1_PIN); led_off(&PORTD, LED2_PIN); led_off(&PORTA, LED3_PIN);
            led_off(&PORTC, LED0_PIN);
            led1_state = 0; led2_state = 0; led3_state = 0;
        }
    }

    if (!panel_blocked)
    {
        if (b1_stable && !b1_prev)
        {
            led1_state = !led1_state;
            if (led1_state) led_on(&PORTD, LED1_PIN); else led_off(&PORTD, LED1_PIN);
        }
        if (b2_stable && !b2_prev)
        {
            led2_state = !led2_state;
            if (led2_state) led_on(&PORTD, LED2_PIN); else led_off(&PORTD, LED2_PIN);
        }
        if (b3_stable && !b3_prev)
        {
            led3_state = !led3_state;
            if (led3_state) led_on(&PORTA, LED3_PIN); else led_off(&PORTA, LED3_PIN);
        }
    }

    sw0_prev = sw0_stable;
    b1_prev  = b1_stable;
    b2_prev  = b2_stable;
    b3_prev  = b3_stable;
}

void task_50ms(void)
{
    if (panel_blocked) adc_start_conversion();
}

void task_100ms(void)
{
    if (!panel_blocked) return;

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