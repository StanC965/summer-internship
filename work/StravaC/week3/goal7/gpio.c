#include "gpio.h"

#define GPIO_ONE    (1U)

void gpio_init(void)
{
}

void gpio_set_direction(volatile gpio_uint8_t *gpio_ddr_register, gpio_uint8_t gpio_pin_number, gpio_uint8_t gpio_direction)
{
    if (gpio_direction == GPIO_OUTPUT)
    {
        *gpio_ddr_register |= (gpio_uint8_t)(GPIO_ONE << gpio_pin_number);
    }
    else
    {
        *gpio_ddr_register &= (gpio_uint8_t)(~(GPIO_ONE << gpio_pin_number));
    }
}

void gpio_set_pin(volatile gpio_uint8_t *gpio_port_register, gpio_uint8_t gpio_pin_number)
{
    *gpio_port_register |= (gpio_uint8_t)(GPIO_ONE << gpio_pin_number);
}

void gpio_reset_pin(volatile gpio_uint8_t *gpio_port_register, gpio_uint8_t gpio_pin_number)
{
    *gpio_port_register &= (gpio_uint8_t)(~(GPIO_ONE << gpio_pin_number));
}

gpio_uint8_t gpio_read_pin(volatile gpio_uint8_t *gpio_pin_register, gpio_uint8_t gpio_pin_number)
{
    return (gpio_uint8_t)((*gpio_pin_register >> gpio_pin_number) & GPIO_ONE);
}
