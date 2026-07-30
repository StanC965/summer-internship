#include "gpio.h"

#define GPIO_ONE    (1U)

void gpio_init(void)
{
}

void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr,
    gpio_uint8_t gpio_pin,
    gpio_uint8_t gpio_direction
)
{
    if (gpio_direction == GPIO_OUTPUT)
    {
        *gpio_ddr |= (gpio_uint8_t)(
            GPIO_ONE << gpio_pin
        );
    }
    else
    {
        *gpio_ddr &= (gpio_uint8_t)(
            ~(GPIO_ONE << gpio_pin)
        );
    }
}

void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port |= (gpio_uint8_t)(
        GPIO_ONE << gpio_pin
    );
}

void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port &= (gpio_uint8_t)(
        ~(GPIO_ONE << gpio_pin)
    );
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
)
{
    return (gpio_uint8_t)(
        (
            *gpio_pin_register >>
            gpio_pin
        ) &
        GPIO_ONE
    );
}