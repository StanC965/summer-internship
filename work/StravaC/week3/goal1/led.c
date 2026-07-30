#include "led.h"

void led_init(
    volatile gpio_uint8_t *led_ddr_register,
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    gpio_set_direction(
        led_ddr_register,
        led_pin_number,
        GPIO_OUTPUT
    );

    led_power_off(
        led_port_register,
        led_pin_number
    );
}

void led_power_on(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    /*
    Active-low LED:
    LOW turns the LED ON.
    */

    gpio_reset_pin(
        led_port_register,
        led_pin_number
    );
}

void led_power_off(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    /*
    Active-low LED:
    HIGH turns the LED OFF.
    */

    gpio_set_pin(
        led_port_register,
        led_pin_number
    );
}