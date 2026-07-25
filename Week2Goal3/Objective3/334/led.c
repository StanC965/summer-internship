#ifndef LED_C
#define LED_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define LED_ONE_SECOND      (30000UL)
#define LED_FAST_DELAY      (LED_ONE_SECOND / 12U)   /* 6 cycles/s -> 12 phases/s */
#define LED_SLOW_DELAY      (LED_ONE_SECOND / 4U)    /* 2 cycles/s -> 4 phases/s  */

static void led_delay(unsigned long count)
{
    volatile unsigned long i;
    for (i = 0; i < count; i++) { }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void led_init(gpio_reg_t ddr, unsigned char pin)
{
    gpio_set_direction(ddr, pin, GPIO_OUTPUT);
}

void led_power_on(gpio_reg_t port, unsigned char pin)
{
    gpio_reset_pin(port, pin);      /* active low: ON = 0 */
}

void led_power_off(gpio_reg_t port, unsigned char pin)
{
    gpio_set_pin(port, pin);        /* active low: OFF = 1 */
}

void led_toggle(gpio_reg_t port, unsigned char pin)
{
    gpio_toggle_pin(port, pin);
}

void led_blink_fast(gpio_reg_t port, unsigned char pin)
{
    led_power_on(port, pin);
    led_delay(LED_FAST_DELAY);
    led_power_off(port, pin);
    led_delay(LED_FAST_DELAY);
}

void led_blink_slow(gpio_reg_t port, unsigned char pin)
{
    led_power_on(port, pin);
    led_delay(LED_SLOW_DELAY);
    led_power_off(port, pin);
    led_delay(LED_SLOW_DELAY);
}

#endif
