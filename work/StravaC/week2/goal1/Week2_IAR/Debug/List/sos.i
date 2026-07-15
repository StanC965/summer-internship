#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\sos.c"























 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\sos.h"



















 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\gpio.h"












 


















typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;



extern void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction);

extern void gpio_activate_pullup(volatile gpio_uint8_t *port, gpio_uint8_t pin);

extern gpio_uint8_t gpio_read_pin(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin);

extern gpio_uint8_t gpio_read_pin_debounced(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin);

#line 23 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\sos.h"



extern void sos_play(volatile gpio_uint8_t *port,
                     gpio_uint8_t pin);

extern gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request);

#line 27 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\sos.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\led.h"
















 













 
extern void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_blink_fast(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_blink_slow(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#line 28 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week2\\Week2_IAR\\sos.c"



static void sos_point(volatile gpio_uint8_t *port,
                      gpio_uint8_t pin);

static void sos_line(volatile gpio_uint8_t *port,
                     gpio_uint8_t pin);

static gpio_uint8_t sos_stop_is_requested(
    volatile gpio_uint8_t *interrupt_request);

static void sos_delay_point(
    volatile gpio_uint8_t *interrupt_request);

static void sos_delay_line(
    volatile gpio_uint8_t *interrupt_request);

static void sos_delay_pause(
    volatile gpio_uint8_t *interrupt_request);



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

gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request)
{
    gpio_uint8_t symbol_index;

    

 
    for (symbol_index = 0U; symbol_index < 3U; symbol_index++)
    {
        led_power_on(led_port, led_pin);
        sos_delay_point(interrupt_request);
        led_power_off(led_port, led_pin);

        if (sos_stop_is_requested(interrupt_request) == ((0x01U)))
        {
            return ((0x00U));
        }

        sos_delay_pause(interrupt_request);

        if (sos_stop_is_requested(interrupt_request) == ((0x01U)))
        {
            return ((0x00U));
        }
    }

    

 
    for (symbol_index = 0U; symbol_index < 3U; symbol_index++)
    {
        led_power_on(led_port, led_pin);
        sos_delay_line(interrupt_request);
        led_power_off(led_port, led_pin);

        if (sos_stop_is_requested(interrupt_request) == ((0x01U)))
        {
            return ((0x00U));
        }

        sos_delay_pause(interrupt_request);

        if (sos_stop_is_requested(interrupt_request) == ((0x01U)))
        {
            return ((0x00U));
        }
    }

    

 
    for (symbol_index = 0U; symbol_index < 3U; symbol_index++)
    {
        led_power_on(led_port, led_pin);
        sos_delay_point(interrupt_request);
        led_power_off(led_port, led_pin);

        if (sos_stop_is_requested(interrupt_request) == ((0x01U)))
        {
            return ((0x00U));
        }

        sos_delay_pause(interrupt_request);

        if (sos_stop_is_requested(interrupt_request) == ((0x01U)))
        {
            return ((0x00U));
        }
    }

    return ((0x01U));
}



static void sos_point(volatile gpio_uint8_t *port,
                      gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_point(((void*)0x00U));

    led_power_off(port, pin);
    sos_delay_pause(((void*)0x00U));
}

static void sos_line(volatile gpio_uint8_t *port,
                     gpio_uint8_t pin)
{
    led_power_on(port, pin);
    sos_delay_line(((void*)0x00U));

    led_power_off(port, pin);
    sos_delay_pause(((void*)0x00U));
}

static gpio_uint8_t sos_stop_is_requested(
    volatile gpio_uint8_t *interrupt_request)
{
    if (interrupt_request == ((void*)0x00U))
    {
        return ((0x00U));
    }

    if (*interrupt_request == ((0x01U)))
    {
        


 
        *interrupt_request = ((0x00U));
        return ((0x01U));
    }

    return ((0x00U));
}

static void sos_delay_point(
    volatile gpio_uint8_t *interrupt_request)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {
        if ((interrupt_request != ((void*)0x00U)) &&
            (*interrupt_request == ((0x01U))))
        {
            break;
        }
    }
}

static void sos_delay_line(
    volatile gpio_uint8_t *interrupt_request)
{
    volatile unsigned long i;

    for (i = 0; i < 120000UL; i++)
    {
        if ((interrupt_request != ((void*)0x00U)) &&
            (*interrupt_request == ((0x01U))))
        {
            break;
        }
    }
}

static void sos_delay_pause(
    volatile gpio_uint8_t *interrupt_request)
{
    volatile unsigned long i;

    for (i = 0; i < 30000UL; i++)
    {
        if ((interrupt_request != ((void*)0x00U)) &&
            (*interrupt_request == ((0x01U))))
        {
            break;
        }
    }
}

