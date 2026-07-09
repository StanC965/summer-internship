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

#line 17 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.h"



extern void sos_play(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#line 21 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\led.h"
















 













 
extern void led_power_on(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_power_off(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_blink_fast(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void led_blink_slow(volatile gpio_uint8_t *port, gpio_uint8_t pin);

#line 22 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\sos.c"



static void sos_point(volatile gpio_uint8_t *port, gpio_uint8_t pin);
static void sos_line(volatile gpio_uint8_t *port, gpio_uint8_t pin);
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

static void sos_delay_point(void)
{
    volatile unsigned long i;

    for (i = 0; i < 25000UL; i++)
    {

    }
}

static void sos_delay_line(void)
{
    volatile unsigned long i;

    for (i = 0; i < 75000UL; i++)
    {

    }
}

static void sos_delay_pause(void)
{
    volatile unsigned long i;

    for (i = 0; i < 25000UL; i++)
    {

    }
}

