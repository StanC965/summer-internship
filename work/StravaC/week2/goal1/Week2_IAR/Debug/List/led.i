#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.c"












 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.h"









 

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

#line 13 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.h"

extern void led_power_on(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
);

#line 16 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.c"

void led_power_on(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    gpio_reset_pin(
        led_port,
        led_pin
    );
}

void led_power_off(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin
)
{
    gpio_set_pin(
        led_port,
        led_pin
    );
}

