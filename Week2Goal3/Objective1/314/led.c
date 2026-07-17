#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values (private timing constants)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define LED_ONE_SECOND      (30000UL)
#define LED_FAST_DELAY      (LED_ONE_SECOND / 12U)   /* 6 cycles/s -> 12 phases/s */
#define LED_SLOW_DELAY      (LED_ONE_SECOND / 4U)    /* 2 cycles/s -> 4 phases/s  */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects and functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* private software delay, used only inside the led module */
static void led_delay(unsigned long count)
{
    volatile unsigned long i;
    for (i = 0; i < count; i++) { }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void led_init(void)
{
    gpio_set_direction(LED0_PIN, GPIO_OUTPUT);
}

void led_power_on(void)
{
    gpio_reset_pin(LED0_PIN);    /* active low: ON = 0 */
}

void led_power_off(void)
{
    gpio_set_pin(LED0_PIN);      /* active low: OFF = 1 */
}

void led_blink_fast(void)
{
    led_power_on();
    led_delay(LED_FAST_DELAY);
    led_power_off();
    led_delay(LED_FAST_DELAY);
}

void led_blink_slow(void)
{
    led_power_on();
    led_delay(LED_SLOW_DELAY);
    led_power_off();
    led_delay(LED_SLOW_DELAY);
}

#endif
