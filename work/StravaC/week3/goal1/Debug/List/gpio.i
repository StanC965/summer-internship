#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\gpio.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\gpio.h"



typedef unsigned char gpio_uint8_t;







extern void gpio_init(void);

extern void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr_register,
    gpio_uint8_t gpio_pin_number,
    gpio_uint8_t gpio_direction
);

extern void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
);

extern void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
);

extern gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin_number
);

#line 2 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\gpio.c"



void gpio_init(void)
{
}

void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr_register,
    gpio_uint8_t gpio_pin_number,
    gpio_uint8_t gpio_direction
)
{
    if (gpio_direction == (1U))
    {
        *gpio_ddr_register |= (gpio_uint8_t)(
            (1U) << gpio_pin_number
        );
    }
    else
    {
        *gpio_ddr_register &= (gpio_uint8_t)(
            ~((1U) << gpio_pin_number)
        );
    }
}

void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
)
{
    *gpio_port_register |= (gpio_uint8_t)(
        (1U) << gpio_pin_number
    );
}

void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
)
{
    *gpio_port_register &= (gpio_uint8_t)(
        ~((1U) << gpio_pin_number)
    );
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin_number
)
{
    return (gpio_uint8_t)(
        (
            *gpio_pin_register >>
            gpio_pin_number
        ) &
        (1U)
    );
}
