#ifndef GPIO_H
#define GPIO_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului GPIO.

Modulul GPIO este un driver software pentru porturile digitale.
Actiunile atomice sunt:
- configurarea directiei;
- setarea unui pin;
- resetarea unui pin;
- comutarea unui pin;
- citirea unui pin.
*/

/* General values */

#define GPIO_ZERO                  (0U)
#define GPIO_ONE                   (1U)

#define GPIO_FALSE                 (GPIO_ZERO)
#define GPIO_TRUE                  (GPIO_ONE)

/* Pin directions */

#define GPIO_INPUT                 (GPIO_ZERO)
#define GPIO_OUTPUT                (GPIO_ONE)

/* Logic levels */

#define GPIO_LOW                   (GPIO_ZERO)
#define GPIO_HIGH                  (GPIO_ONE)

/* Exported types */

typedef unsigned char gpio_uint8_t;

/* Module initialization */

extern void gpio_init(void);

/* Atomic GPIO actions */

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

extern void gpio_toggle_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
);

extern gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin_number
);

#endif