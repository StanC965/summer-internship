#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"
#include "panel.h"

#define GPIO_INPUT   0
#define GPIO_OUTPUT  1
#define PULLUP_ON    1
#define INTERRUPT_ENABLED  1

#define SW0_PIN      6   /* PC6 */
#define BUTTON1_PIN  1   /* PC1 */
#define BUTTON2_PIN  0   /* PA0 */
#define BUTTON3_PIN  1   /* PA1 */
#define LED1_PIN     5   /* PD5 */
#define LED2_PIN     4   /* PD4 */
#define LED3_PIN     3   /* PA3 */
#define LED0_PIN     7   /* PC7 */

#define LIGHT_SENSOR_ADC_CHANNEL  4
#define LIGHT_MIDPOINT       127
#define LIGHT_LEVEL1         64
#define LIGHT_LEVEL2         128
#define LIGHT_LEVEL3         192

static unsigned char led1_state = 0;
static unsigned char led2_state = 0;
static unsigned char led3_state = 0;
static unsigned char button1_prev = 0;
static unsigned char button2_prev = 0;
static unsigned char button3_prev = 0;
static volatile unsigned char panel_blocked = 0;

static void panel_light_update(void)
{
    unsigned char light = adc_get_result();

    if (light > LIGHT_MIDPOINT)
        led_on(&PORTC, LED0_PIN);
    else
        led_off(&PORTC, LED0_PIN);

    if (light < LIGHT_LEVEL1)
    {
        led_off(&PORTD, LED1_PIN);
        led_off(&PORTD, LED2_PIN);
        led_off(&PORTA, LED3_PIN);
    }
    else if (light < LIGHT_LEVEL2)
    {
        led_on(&PORTD, LED1_PIN);
        led_off(&PORTD, LED2_PIN);
        led_off(&PORTA, LED3_PIN);
    }
    else if (light < LIGHT_LEVEL3)
    {
        led_on(&PORTD, LED1_PIN);
        led_on(&PORTD, LED2_PIN);
        led_off(&PORTA, LED3_PIN);
    }
    else
    {
        led_on(&PORTD, LED1_PIN);
        led_on(&PORTD, LED2_PIN);
        led_on(&PORTA, LED3_PIN);
    }

    adc_start_conversion();
}

void panel_init(void)
{
    gpio_set_direction(&DDRC, SW0_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTC, SW0_PIN);
    PCMSK2_PCINT22 = INTERRUPT_ENABLED;
    PCICR_PCIE2 = INTERRUPT_ENABLED;

    gpio_set_direction(&DDRC, BUTTON1_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTC, BUTTON1_PIN);
    gpio_set_direction(&DDRA, BUTTON2_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTA, BUTTON2_PIN);
    gpio_set_direction(&DDRA, BUTTON3_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTA, BUTTON3_PIN);

    gpio_set_direction(&DDRD, LED1_PIN, GPIO_OUTPUT);
    gpio_set_direction(&DDRD, LED2_PIN, GPIO_OUTPUT);
    gpio_set_direction(&DDRA, LED3_PIN, GPIO_OUTPUT);
    gpio_set_direction(&DDRC, LED0_PIN, GPIO_OUTPUT);

    led_off(&PORTD, LED1_PIN);
    led_off(&PORTD, LED2_PIN);
    led_off(&PORTA, LED3_PIN);
    led_off(&PORTC, LED0_PIN);

    adc_init(LIGHT_SENSOR_ADC_CHANNEL);
    adc_start_conversion();
}

void panel_update(void)
{
    unsigned char b1_now = gpio_debounce(&PINC, BUTTON1_PIN);
    unsigned char b2_now = gpio_debounce(&PINA, BUTTON2_PIN);
    unsigned char b3_now = gpio_debounce(&PINA, BUTTON3_PIN);

    if (panel_blocked)
    {
        panel_light_update();
    }
    else
    {
        if (b1_now && !button1_prev)
        {
            led1_state = !led1_state;
            if (led1_state) led_on(&PORTD, LED1_PIN); else led_off(&PORTD, LED1_PIN);
        }
        if (b2_now && !button2_prev)
        {
            led2_state = !led2_state;
            if (led2_state) led_on(&PORTD, LED2_PIN); else led_off(&PORTD, LED2_PIN);
        }
        if (b3_now && !button3_prev)
        {
            led3_state = !led3_state;
            if (led3_state) led_on(&PORTA, LED3_PIN); else led_off(&PORTA, LED3_PIN);
        }
    }

    button1_prev = b1_now;
    button2_prev = b2_now;
    button3_prev = b3_now;
}

#pragma vector = PCINT2_vect
__interrupt void pcint2_isr(void)
{
    if (PINC_PINC6 == 0)
    {
        panel_blocked = !panel_blocked;

        if (!panel_blocked)
        {
            led_off(&PORTD, LED1_PIN);
            led_off(&PORTD, LED2_PIN);
            led_off(&PORTA, LED3_PIN);
            led_off(&PORTC, LED0_PIN);
            led1_state = 0;
            led2_state = 0;
            led3_state = 0;
        }
    }
}