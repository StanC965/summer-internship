#ifndef GPIO_H
#define GPIO_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului GPIO.
*/

#define GPIO_ZERO              (0U)
#define GPIO_ONE               (1U)

#define GPIO_FALSE             (GPIO_ZERO)
#define GPIO_TRUE              (GPIO_ONE)

#define GPIO_INPUT             (GPIO_ZERO)
#define GPIO_OUTPUT            (GPIO_ONE)

#define GPIO_LOW               (GPIO_ZERO)
#define GPIO_HIGH              (GPIO_ONE)

typedef unsigned char gpio_uint8_t;

extern void gpio_init(void);

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

#endif