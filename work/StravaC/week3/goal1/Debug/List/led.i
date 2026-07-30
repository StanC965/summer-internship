#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\led.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\led.h"



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

#line 5 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\led.h"






 

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

#line 2 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\led.c"

void led_init(
    volatile gpio_uint8_t *led_ddr_register,
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
)
{
    gpio_set_direction(
        led_ddr_register,
        led_pin_number,
        (1U)
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
    


 

    gpio_set_pin(
        led_port_register,
        led_pin_number
    );
}
