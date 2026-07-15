#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.c"

























 

 




 






#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.h"




















 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\gpio.h"















 

 



 




 




 




 




 




 

typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;

 

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

#line 24 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.h"

 

extern void sos_play(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
);

extern gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
);

#line 41 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.h"

















 



 

extern void led_power_on(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_blink_fast(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_blink_slow(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

#line 42 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.c"

 

static void sos_point(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
);

static void sos_line(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
);

static gpio_uint8_t sos_point_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
);

static gpio_uint8_t sos_line_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
);

static gpio_uint8_t sos_interrupt_is_requested(
    volatile gpio_uint8_t *sos_interrupt_request
);

static gpio_uint8_t sos_delay_interruptible(
    unsigned long sos_delay_count,
    volatile gpio_uint8_t *sos_interrupt_request
);

static void sos_delay_point(void);

static void sos_delay_line(void);

static void sos_delay_pause(void);

static void sos_delay(
    unsigned long sos_delay_count
);

 

void sos_play(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
)
{
    gpio_uint8_t sos_symbol_index;

    


 
    for (
        sos_symbol_index = (0U);
        sos_symbol_index < (3U);
        sos_symbol_index++
    )
    {
        sos_point(
            sos_led_port,
            sos_led_pin
        );
    }

    


 
    for (
        sos_symbol_index = (0U);
        sos_symbol_index < (3U);
        sos_symbol_index++
    )
    {
        sos_line(
            sos_led_port,
            sos_led_pin
        );
    }

    


 
    for (
        sos_symbol_index = (0U);
        sos_symbol_index < (3U);
        sos_symbol_index++
    )
    {
        sos_point(
            sos_led_port,
            sos_led_pin
        );
    }
}

gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
)
{
    gpio_uint8_t sos_symbol_index;

    


 
    if (
        sos_interrupt_is_requested(
            sos_interrupt_request
        ) == ((0x01U))
    )
    {
        led_power_off(
            sos_led_port,
            sos_led_pin
        );

        return ((0x00U));
    }

    


 
    for (
        sos_symbol_index = (0U);
        sos_symbol_index < (3U);
        sos_symbol_index++
    )
    {
        if (
            sos_point_interruptible(
                sos_led_port,
                sos_led_pin,
                sos_interrupt_request
            ) == ((0x00U))
        )
        {
            led_power_off(
                sos_led_port,
                sos_led_pin
            );

            return ((0x00U));
        }
    }

    


 
    for (
        sos_symbol_index = (0U);
        sos_symbol_index < (3U);
        sos_symbol_index++
    )
    {
        if (
            sos_line_interruptible(
                sos_led_port,
                sos_led_pin,
                sos_interrupt_request
            ) == ((0x00U))
        )
        {
            led_power_off(
                sos_led_port,
                sos_led_pin
            );

            return ((0x00U));
        }
    }

    


 
    for (
        sos_symbol_index = (0U);
        sos_symbol_index < (3U);
        sos_symbol_index++
    )
    {
        if (
            sos_point_interruptible(
                sos_led_port,
                sos_led_pin,
                sos_interrupt_request
            ) == ((0x00U))
        )
        {
            led_power_off(
                sos_led_port,
                sos_led_pin
            );

            return ((0x00U));
        }
    }

    return ((0x01U));
}

 

static void sos_point(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
)
{
    led_power_on(
        sos_led_port,
        sos_led_pin
    );

    sos_delay_point();

    led_power_off(
        sos_led_port,
        sos_led_pin
    );

    sos_delay_pause();
}

static void sos_line(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin
)
{
    led_power_on(
        sos_led_port,
        sos_led_pin
    );

    sos_delay_line();

    led_power_off(
        sos_led_port,
        sos_led_pin
    );

    sos_delay_pause();
}

static gpio_uint8_t sos_point_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
)
{
    led_power_on(
        sos_led_port,
        sos_led_pin
    );

    if (
        sos_delay_interruptible(
            (30000UL),
            sos_interrupt_request
        ) == ((0x00U))
    )
    {
        led_power_off(
            sos_led_port,
            sos_led_pin
        );

        return ((0x00U));
    }

    led_power_off(
        sos_led_port,
        sos_led_pin
    );

    if (
        sos_delay_interruptible(
            (30000UL),
            sos_interrupt_request
        ) == ((0x00U))
    )
    {
        return ((0x00U));
    }

    return ((0x01U));
}

static gpio_uint8_t sos_line_interruptible(
    volatile gpio_uint8_t *sos_led_port,
    gpio_uint8_t sos_led_pin,
    volatile gpio_uint8_t *sos_interrupt_request
)
{
    led_power_on(
        sos_led_port,
        sos_led_pin
    );

    if (
        sos_delay_interruptible(
            (120000UL),
            sos_interrupt_request
        ) == ((0x00U))
    )
    {
        led_power_off(
            sos_led_port,
            sos_led_pin
        );

        return ((0x00U));
    }

    led_power_off(
        sos_led_port,
        sos_led_pin
    );

    if (
        sos_delay_interruptible(
            (30000UL),
            sos_interrupt_request
        ) == ((0x00U))
    )
    {
        return ((0x00U));
    }

    return ((0x01U));
}

static gpio_uint8_t sos_interrupt_is_requested(
    volatile gpio_uint8_t *sos_interrupt_request
)
{
    if (sos_interrupt_request == ((void *)0x00U))
    {
        return ((0x00U));
    }

    if (*sos_interrupt_request == ((0x01U)))
    {
        return ((0x01U));
    }

    return ((0x00U));
}

static gpio_uint8_t sos_delay_interruptible(
    unsigned long sos_delay_count,
    volatile gpio_uint8_t *sos_interrupt_request
)
{
    volatile unsigned long sos_delay_counter;

    for (
        sos_delay_counter = (0UL);
        sos_delay_counter < sos_delay_count;
        sos_delay_counter++
    )
    {
        if (
            sos_interrupt_is_requested(
                sos_interrupt_request
            ) == ((0x01U))
        )
        {
            return ((0x00U));
        }
    }

    return ((0x01U));
}

static void sos_delay_point(void)
{
    sos_delay(
        (30000UL)
    );
}

static void sos_delay_line(void)
{
    sos_delay(
        (120000UL)
    );
}

static void sos_delay_pause(void)
{
    sos_delay(
        (30000UL)
    );
}

static void sos_delay(
    unsigned long sos_delay_count
)
{
    volatile unsigned long sos_delay_counter;

    for (
        sos_delay_counter = (0UL);
        sos_delay_counter < sos_delay_count;
        sos_delay_counter++
    )
    {
        


 
    }
}

