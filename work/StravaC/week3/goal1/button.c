#ifndef BUTTON_C
#define BUTTON_C

#include "button.h"

/*
Debounce configuration:

task period = 10 ms
number of samples = 5
debounce time = 50 ms

Buttons are active-low:
released = 1
pressed  = 0
*/

#define BUTTON_SAMPLE_MASK                 (0x1FU)

#define BUTTON_ALL_PRESSED_SAMPLES         (0x00U)
#define BUTTON_ALL_RELEASED_SAMPLES        (0x1FU)

#define BUTTON_INITIAL_SAMPLE_BUFFER       \
    (BUTTON_ALL_RELEASED_SAMPLES)

#define BUTTON_SHIFT_POSITIONS             (1U)

static void button_update_stable_state(
    button_t *button_instance
);

void button_init(
    button_t *button_instance,
    volatile gpio_uint8_t *button_ddr_register,
    volatile gpio_uint8_t *button_port_register,
    volatile gpio_uint8_t *button_pin_register,
    button_uint8_t button_pin_number
)
{
    button_instance->button_pin_register =
        button_pin_register;

    button_instance->button_pin_number =
        button_pin_number;

    button_instance->button_sample_buffer =
        BUTTON_INITIAL_SAMPLE_BUFFER;

    button_instance->button_stable_state =
        BUTTON_NOT_PRESSED;

    button_instance->button_press_event =
        BUTTON_EVENT_NOT_DETECTED;

    gpio_set_direction(
        button_ddr_register,
        button_pin_number,
        GPIO_INPUT
    );

    /*
    Butoanele nu au pull-up extern.
    */

    gpio_activate_pullup(
        button_port_register,
        button_pin_number
    );
}

void button_debounce_task(
    button_t *button_instance
)
{
    button_uint8_t button_raw_sample;

    button_raw_sample = gpio_read_pin(
        button_instance->button_pin_register,
        button_instance->button_pin_number
    );

    /*
    Fereastra mobila de cinci esantioane.

    Exemplu la apasare:
    11111
    11110
    11100
    11000
    10000
    00000
    */

    button_instance->button_sample_buffer =
        (button_uint8_t)(
            (
                button_instance->button_sample_buffer
                << BUTTON_SHIFT_POSITIONS
            ) |
            button_raw_sample
        );

    button_instance->button_sample_buffer &=
        BUTTON_SAMPLE_MASK;

    button_update_stable_state(
        button_instance
    );
}

button_uint8_t button_is_pressed(
    const button_t *button_instance
)
{
    return button_instance->button_stable_state;
}

button_uint8_t button_was_pressed(
    button_t *button_instance
)
{
    button_uint8_t button_event_copy;

    button_event_copy =
        button_instance->button_press_event;

    button_instance->button_press_event =
        BUTTON_EVENT_NOT_DETECTED;

    return button_event_copy;
}

static void button_update_stable_state(
    button_t *button_instance
)
{
    if (
        button_instance->button_sample_buffer ==
        BUTTON_ALL_PRESSED_SAMPLES
    )
    {
        /*
        Genereaza eveniment o singura data,
        la tranzitia RELEASED -> PRESSED.
        */

        if (
            button_instance->button_stable_state ==
            BUTTON_NOT_PRESSED
        )
        {
            button_instance->button_stable_state =
                BUTTON_PRESSED;

            button_instance->button_press_event =
                BUTTON_EVENT_DETECTED;
        }
    }
    else if (
        button_instance->button_sample_buffer ==
        BUTTON_ALL_RELEASED_SAMPLES
    )
    {
        button_instance->button_stable_state =
            BUTTON_NOT_PRESSED;
    }
    else
    {
        /*
        Esantioane mixte:
        bouncing inca prezent.

        Starea stabila anterioara se pastreaza.
        */
    }
}

#endif