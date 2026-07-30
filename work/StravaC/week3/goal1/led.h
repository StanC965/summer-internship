#ifndef LED_H
#define LED_H

#include "gpio.h"

/*
LED0 is active-low:

LOW  -> LED ON
HIGH -> LED OFF
*/

extern void led_init(
    volatile gpio_uint8_t *led_ddr_register,
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

extern void led_power_on(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

#endif