#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.c"

















 

 




#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.h"













 

 



 




 




 




 




 




 

typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;

 

extern void gpio_set_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

extern void gpio_reset_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

extern void gpio_toggle_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

extern void gpio_set_direction(
    volatile gpio_uint8_t *ddr,
    gpio_uint8_t pin,
    gpio_uint8_t direction
);

extern void gpio_activate_pullup(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

extern gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *pin_register,
    gpio_uint8_t pin
);

extern gpio_uint8_t gpio_read_pin_debounced(
    volatile gpio_uint8_t *pin_register,
    gpio_uint8_t pin
);

#line 26 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.c"

 

static void gpio_debounce_delay(void);

 

void gpio_set_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    *port |= ((0x01U) << pin);
}

void gpio_reset_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    *port &= ~((0x01U) << pin);
}

void gpio_toggle_pin(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    *port ^= ((0x01U) << pin);
}

void gpio_set_direction(
    volatile gpio_uint8_t *ddr,
    gpio_uint8_t pin,
    gpio_uint8_t direction
)
{
    if (direction == ((0x01U)))
    {
        *ddr |= ((0x01U) << pin);
    }
    else
    {
        *ddr &= ~((0x01U) << pin);
    }
}

void gpio_activate_pullup(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    gpio_set_pin(port, pin);
}

gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *pin_register,
    gpio_uint8_t pin
)
{
    gpio_uint8_t pin_state;

    pin_state = (
        (*pin_register & ((0x01U) << pin)) != (0x00U)
    );

    return pin_state;
}

gpio_uint8_t gpio_read_pin_debounced(
    volatile gpio_uint8_t *pin_register,
    gpio_uint8_t pin
)
{
    gpio_uint8_t first_read;
    gpio_uint8_t second_read;

    first_read = gpio_read_pin(
        pin_register,
        pin
    );

    gpio_debounce_delay();

    second_read = gpio_read_pin(
        pin_register,
        pin
    );

    if (first_read == second_read)
    {
        return second_read;
    }

    


 
    return ((0x01U));
}

 

static void gpio_debounce_delay(void)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = (0UL);
        delay_counter < (20000UL);
        delay_counter++
    )
    {
        


 
    }
}

