#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.c"








 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.h"








 













typedef unsigned char gpio_uint8_t;

extern void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
);

extern void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
);

extern void gpio_toggle_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
);

extern void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr,
    gpio_uint8_t gpio_pin,
    gpio_uint8_t gpio_direction
);

extern void gpio_activate_pullup(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
);

extern gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
);

#line 12 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.c"

void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port |= ((1U) << gpio_pin);
}

void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port &= ~((1U) << gpio_pin);
}

void gpio_toggle_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    *gpio_port ^= ((1U) << gpio_pin);
}

void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr,
    gpio_uint8_t gpio_pin,
    gpio_uint8_t gpio_direction
)
{
    if (gpio_direction == ((1U)))
    {
        *gpio_ddr |= ((1U) << gpio_pin);
    }
    else
    {
        *gpio_ddr &= ~((1U) << gpio_pin);
    }
}

void gpio_activate_pullup(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
)
{
    gpio_set_pin(
        gpio_port,
        gpio_pin
    );
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
)
{
    gpio_uint8_t gpio_pin_state;

    gpio_pin_state = (
        (*gpio_pin_register & ((1U) << gpio_pin)) != (0U)
    );

    return gpio_pin_state;
}

