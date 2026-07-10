#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.c"




















 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.h"
















 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\gpio.h"












 


















typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;



extern void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction);

extern void gpio_activate_pullup(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern gpio_uint8_t gpio_read_pin(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin);

extern gpio_uint8_t gpio_read_pin_debounced(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin);

#line 20 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.h"



extern void sos_play(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern gpio_uint8_t sos_play_interruptible(volatile gpio_uint8_t *led_port,
                                           gpio_uint8_t led_pin,
                                           volatile gpio_uint8_t *button_pin_register,
                                           gpio_uint8_t button_pin);

#line 24 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\led.h"
















 













 
extern void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_blink_fast(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_blink_slow(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#line 25 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.c"



static void sos_point(volatile gpio_uint8_t *port, gpio_uint8_t pin);
static void sos_line(volatile gpio_uint8_t *port, gpio_uint8_t pin);

static gpio_uint8_t sos_button_is_pressed(volatile gpio_uint8_t *button_pin_register,
                                          gpio_uint8_t button_pin);

static void sos_wait_button_release(volatile gpio_uint8_t *button_pin_register,
                                    gpio_uint8_t button_pin);

static void sos_delay_point(void);
static void sos_delay_line(void);
static void sos_delay_pause(void);



void sos_play(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    sos_point(port, pin);
    sos_point(port, pin);
    sos_point(port, pin);

    sos_line(port, pin);
    sos_line(port, pin);
    sos_line(port, pin);

    sos_point(port, pin);
    sos_point(port, pin);
    sos_point(port, pin);
}

gpio_uint8_t sos_play_interruptible(volatile gpio_uint8_t *led_port,
                                    gpio_uint8_t led_pin,
                                    volatile gpio_uint8_t *button_pin_register,
                                    gpio_uint8_t button_pin)
{
    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_line(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_line(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_line(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    sos_point(led_port, led_pin);

    if (sos_button_is_pressed(button_pin_register, button_pin) == ((0x01U)))
    {
        led_power_off(led_port, led_pin);
        sos_wait_button_release(button_pin_register, button_pin);
        return ((0x00U));
    }

    return ((0x01U));
}



static void sos_point(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_point();

    led_power_off(port, pin);
    sos_delay_pause();
}

static void sos_line(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_line();

    led_power_off(port, pin);
    sos_delay_pause();
}

static gpio_uint8_t sos_button_is_pressed(volatile gpio_uint8_t *button_pin_register,
                                          gpio_uint8_t button_pin)
{
    if (gpio_read_pin_debounced(button_pin_register, button_pin) == ((0x00U)))
    {
        return ((0x01U));
    }

    return ((0x00U));
}

static void sos_wait_button_release(volatile gpio_uint8_t *button_pin_register,
                                    gpio_uint8_t button_pin)
{
    while (gpio_read_pin_debounced(button_pin_register, button_pin) == ((0x00U)))
    {

    }
}

static void sos_delay_point(void)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {

    }
}

static void sos_delay_line(void)
{
    volatile unsigned long i;

    for (i = 0; i < 120000UL; i++)
    {

    }
}

static void sos_delay_pause(void)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {

    }
}

