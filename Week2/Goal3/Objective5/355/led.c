#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void led_init(void)
{
    led_configure_pin(LED_LED0_DDR, LED_LED0_PIN);
    led_configure_pin(LED_OLED_1_2_DDR, LED_OLED_1_PIN);
    led_configure_pin(LED_OLED_1_2_DDR, LED_OLED_2_PIN);
    led_configure_pin(LED_OLED_3_DDR, LED_OLED_3_PIN);

    led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_1_PIN);
    led_power_off(LED_OLED_1_2_PORT, LED_OLED_2_PIN);
    led_power_off(LED_OLED_3_PORT, LED_OLED_3_PIN);
}

void led_configure_pin(volatile unsigned char *ddr_reg, unsigned char pin_number)
{
    gpio_set_direction(ddr_reg, pin_number, GPIO_OUTPUT);
}

void led_power_on(volatile unsigned char *port_reg, unsigned char pin_number)
{
    gpio_reset_pin(port_reg, pin_number);
}

void led_power_off(volatile unsigned char *port_reg, unsigned char pin_number)
{
    gpio_set_pin(port_reg, pin_number);
}

void led_toggle(volatile unsigned char *port_reg, unsigned char pin_number)
{
    gpio_toggle_pin(port_reg, pin_number);
}
    
void led_blink_fast(volatile unsigned char *port_reg, unsigned char pin_number)
{
    led_toggle(port_reg, pin_number);
    for (unsigned long i = 0; i < LED_TIME_BLINK_FAST; i++);
}

void led_blink_slow(volatile unsigned char *port_reg, unsigned char pin_number)
{
    led_toggle(port_reg, pin_number);
    for (unsigned long i = 0; i < LED_TIME_BLINK_SLOW; i++);
}

#endif