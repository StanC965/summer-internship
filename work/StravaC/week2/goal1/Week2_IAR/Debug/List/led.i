#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.c"



















 

 





#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.h"
















 

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

#line 20 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.h"

 











 
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

#line 29 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\goal1\\Week2_IAR\\led.c"

 

static void led_delay_fast(void);

static void led_delay_slow(void);

 

void led_power_on(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    gpio_reset_pin(
        port,
        pin
    );
}

void led_power_off(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    gpio_set_pin(
        port,
        pin
    );
}

void led_blink_fast(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    led_power_on(
        port,
        pin
    );

    led_delay_fast();

    led_power_off(
        port,
        pin
    );

    led_delay_fast();
}

void led_blink_slow(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    led_power_on(
        port,
        pin
    );

    led_delay_slow();

    led_power_off(
        port,
        pin
    );

    led_delay_slow();
}

 

static void led_delay_fast(void)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = (0UL);
        delay_counter < (15000UL);
        delay_counter++
    )
    {
        


 
    }
}

static void led_delay_slow(void)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = (0UL);
        delay_counter < (50000UL);
        delay_counter++
    )
    {
        


 
    }
}

