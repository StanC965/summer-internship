#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\gpio.c"












 

#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\gpio.h"












 















typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;











 
extern void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);









 
extern void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);










 
extern void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction);

#line 16 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week1\\goal2\\Goal2_Project\\gpio.c"











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





