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
    volatile gpio_uint8_t *button_pin_register;
    button_uint8_t button_pin_number;
    button_uint8_t button_sample_buffer;
    button_uint8_t button_stable_state;
    button_uint8_t button_press_event;
} button_t;

extern void button_init(button_t *button_instance, volatile gpio_uint8_t *button_ddr_register, volatile gpio_uint8_t *button_port_register, volatile gpio_uint8_t *button_pin_register, button_uint8_t button_pin_number);
extern void button_debounce_task(button_t *button_instance);
extern button_uint8_t button_was_pressed(button_t *button_instance);

#endif
