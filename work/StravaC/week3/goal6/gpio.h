#ifndef GPIO_H
#define GPIO_H

typedef unsigned char gpio_uint8_t;

#define GPIO_LOW       (0U)
#define GPIO_HIGH      (1U)

#define GPIO_INPUT     (0U)
#define GPIO_OUTPUT    (1U)

extern void gpio_init(void);

extern void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr,
    gpio_uint8_t gpio_pin,
    gpio_uint8_t gpio_direction
);

extern void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
);

extern void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port,
    gpio_uint8_t gpio_pin
);

extern gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin
);

#endif