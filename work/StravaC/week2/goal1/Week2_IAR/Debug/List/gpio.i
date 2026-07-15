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

extern gpio_uint8_t gpio_read_pin_debounced(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
);

#line 17 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.c"

 

static void gpio_debounce_delay(void);

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

gpio_uint8_t gpio_read_pin_debounced(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
)
{
    gpio_uint8_t gpio_first_read;
    gpio_uint8_t gpio_second_read;

    gpio_first_read = gpio_read_pin(
        gpio_pin_register,
        gpio_pin
    );

    gpio_debounce_delay();

    gpio_second_read = gpio_read_pin(
        gpio_pin_register,
        gpio_pin
    );

    if (gpio_first_read == gpio_second_read)
    {
        return gpio_second_read;
    }

    


 

    return ((1U));
}

static void gpio_debounce_delay(void)
{
    volatile unsigned long gpio_delay_counter;

    for (
        gpio_delay_counter = (0UL);
        gpio_delay_counter < (20000UL);
        gpio_delay_counter++
    )
    {
        

 
    }
}

