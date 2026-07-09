#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\gpio.c"















 

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

#line 19 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\gpio.c"



static void gpio_debounce_delay(void);



void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    *port |= ((0x01U) << pin);
}

void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    *port &= ~((0x01U) << pin);
}

void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    *port ^= ((0x01U) << pin);
}

void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction)
{
    direction ? (*ddr |= ((0x01U) << pin)) : (*ddr &= ~((0x01U) << pin));
}

void gpio_activate_pullup(volatile gpio_uint8_t *port, gpio_uint8_t pin)
{
    gpio_set_pin(port, pin);
}

gpio_uint8_t gpio_read_pin(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin)
{
    return ((*pin_register & ((0x01U) << pin)) != (0x00U));
}

gpio_uint8_t gpio_read_pin_debounced(volatile gpio_uint8_t *pin_register, gpio_uint8_t pin)
{
    gpio_uint8_t first_read;
    gpio_uint8_t second_read;

    first_read = gpio_read_pin(pin_register, pin);

    gpio_debounce_delay();

    second_read = gpio_read_pin(pin_register, pin);

    if (first_read == second_read)
    {
        return second_read;
    }

    return ((0x01U));
}



static void gpio_debounce_delay(void)
{
    volatile unsigned long i;

    for (i = 0; i < 5000UL; i++)
    {

    }
}

