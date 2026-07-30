#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h"

typedef unsigned char button_uint8_t;

#define BUTTON_EVENT_NOT_DETECTED    (0U)
#define BUTTON_EVENT_DETECTED        (1U)

#define BUTTON_NOT_PRESSED           (0U)
#define BUTTON_PRESSED               (1U)

typedef struct
{
    volatile gpio_uint8_t *pin_register;
    button_uint8_t pin_number;

    button_uint8_t sample_buffer;
    button_uint8_t stable_state;
    button_uint8_t press_event;
} button_t;

extern void button_init(
    button_t *button,
    volatile gpio_uint8_t *ddr_register,
    volatile gpio_uint8_t *port_register,
    volatile gpio_uint8_t *pin_register,
    button_uint8_t pin_number
);

extern void button_debounce_task(
    button_t *button
);

extern button_uint8_t button_was_pressed(
    button_t *button
);

#endif