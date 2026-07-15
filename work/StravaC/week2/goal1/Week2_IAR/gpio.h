#ifndef GPIO_H
#define GPIO_H

// Exported types and values

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului gpio.

Aici sunt declarate tipurile, constantele si functiile publice
care pot fi folosite de alte module.
*/

/* General pointer value */

#define GPIO_NULL              ((void *)0x00U)

/* General numeric values */

#define GPIO_ZERO              (0x00U)
#define GPIO_ONE               (0x01U)

/* Boolean values */

#define GPIO_FALSE             (GPIO_ZERO)
#define GPIO_TRUE              (GPIO_ONE)

/* Function result values */

#define GPIO_NOTOK             (GPIO_FALSE)
#define GPIO_OK                (GPIO_TRUE)

/* Pin direction values */

#define GPIO_INPUT             (GPIO_ZERO)
#define GPIO_OUTPUT            (GPIO_ONE)

/* Pin logic levels */

#define GPIO_LOW               (GPIO_ZERO)
#define GPIO_HIGH              (GPIO_ONE)

/* Exported types */

typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;

/* Public functions */

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

#endif