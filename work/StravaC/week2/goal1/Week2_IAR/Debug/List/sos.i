#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.c"
























 

 




 






#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.h"



















 

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

#line 23 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.h"

 

extern void sos_play(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

extern gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request
);

#line 40 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.h"
















 



 











 
extern void led_power_on(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);











 
extern void led_power_off(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);









 
extern void led_blink_fast(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);









 
extern void led_blink_slow(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

#line 41 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\sos.c"

 

static void sos_point(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

static void sos_line(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

static gpio_uint8_t sos_point_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
);

static gpio_uint8_t sos_line_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
);

static gpio_uint8_t sos_interrupt_is_requested(
    volatile gpio_uint8_t *interrupt_request
);

static gpio_uint8_t sos_delay_interruptible(
    unsigned long delay_count,
    volatile gpio_uint8_t *interrupt_request
);

static void sos_delay_point(void);

static void sos_delay_line(void);

static void sos_delay_pause(void);

static void sos_delay(
    unsigned long delay_count
);

 

void sos_play(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    gpio_uint8_t symbol_index;

    


 
    for (
        symbol_index = (0U);
        symbol_index < (3U);
        symbol_index++
    )
    {
        sos_point(
            port,
            pin
        );
    }

    


 
    for (
        symbol_index = (0U);
        symbol_index < (3U);
        symbol_index++
    )
    {
        sos_line(
            port,
            pin
        );
    }

    


 
    for (
        symbol_index = (0U);
        symbol_index < (3U);
        symbol_index++
    )
    {
        sos_point(
            port,
            pin
        );
    }
}

gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request
)
{
    gpio_uint8_t symbol_index;

    


 
    if (sos_interrupt_is_requested(interrupt_request) == ((0x01U)))
    {
        led_power_off(
            led_port,
            led_pin
        );

        return ((0x00U));
    }

    


 
    for (
        symbol_index = (0U);
        symbol_index < (3U);
        symbol_index++
    )
    {
        if (
            sos_point_interruptible(
                led_port,
                led_pin,
                interrupt_request
            ) == ((0x00U))
        )
        {
            led_power_off(
                led_port,
                led_pin
            );

            return ((0x00U));
        }
    }

    


 
    for (
        symbol_index = (0U);
        symbol_index < (3U);
        symbol_index++
    )
    {
        if (
            sos_line_interruptible(
                led_port,
                led_pin,
                interrupt_request
            ) == ((0x00U))
        )
        {
            led_power_off(
                led_port,
                led_pin
            );

            return ((0x00U));
        }
    }

    


 
    for (
        symbol_index = (0U);
        symbol_index < (3U);
        symbol_index++
    )
    {
        if (
            sos_point_interruptible(
                led_port,
                led_pin,
                interrupt_request
            ) == ((0x00U))
        )
        {
            led_power_off(
                led_port,
                led_pin
            );

            return ((0x00U));
        }
    }

    return ((0x01U));
}

 

static void sos_point(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    led_power_on(
        port,
        pin
    );

    sos_delay_point();

    led_power_off(
        port,
        pin
    );

    sos_delay_pause();
}

static void sos_line(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    led_power_on(
        port,
        pin
    );

    sos_delay_line();

    led_power_off(
        port,
        pin
    );

    sos_delay_pause();
}

static gpio_uint8_t sos_point_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
)
{
    led_power_on(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            (30000UL),
            interrupt_request
        ) == ((0x00U))
    )
    {
        led_power_off(
            port,
            pin
        );

        return ((0x00U));
    }

    led_power_off(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            (30000UL),
            interrupt_request
        ) == ((0x00U))
    )
    {
        return ((0x00U));
    }

    return ((0x01U));
}

static gpio_uint8_t sos_line_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
)
{
    led_power_on(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            (120000UL),
            interrupt_request
        ) == ((0x00U))
    )
    {
        led_power_off(
            port,
            pin
        );

        return ((0x00U));
    }

    led_power_off(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            (30000UL),
            interrupt_request
        ) == ((0x00U))
    )
    {
        return ((0x00U));
    }

    return ((0x01U));
}

static gpio_uint8_t sos_interrupt_is_requested(
    volatile gpio_uint8_t *interrupt_request
)
{
    if (interrupt_request == ((void *)0x00U))
    {
        return ((0x00U));
    }

    if (*interrupt_request == ((0x01U)))
    {
        return ((0x01U));
    }

    return ((0x00U));
}

static gpio_uint8_t sos_delay_interruptible(
    unsigned long delay_count,
    volatile gpio_uint8_t *interrupt_request
)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = (0UL);
        delay_counter < delay_count;
        delay_counter++
    )
    {
        if (
            sos_interrupt_is_requested(
                interrupt_request
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
    unsigned long delay_count
)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = (0UL);
        delay_counter < delay_count;
        delay_counter++
    )
    {
        


 
    }
}

