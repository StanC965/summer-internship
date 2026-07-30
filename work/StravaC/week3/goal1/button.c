#include "button.h"

/*
Debounce:

Scheduler task = 10 ms
Number of samples = 5

Debounce time:
5 * 10 ms = 50 ms

Buttons are active-low:

released = 1
pressed  = 0
*/

#define BUTTON_SAMPLE_MASK                 (0x1FU)
#define BUTTON_ALL_PRESSED_SAMPLES         (0x00U)
#define BUTTON_ALL_RELEASED_SAMPLES        (0x1FU)

#define BUTTON_SHIFT_POSITIONS             (1U)

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
        BUTTON_ALL_RELEASED_SAMPLES;

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
    Enable internal pull-up resistor.
    */

    gpio_set_pin(
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

    if (
        button_instance->button_sample_buffer ==
        BUTTON_ALL_PRESSED_SAMPLES
    )
    {
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
        Mixed samples indicate bouncing.

        Keep the previously validated stable state.
        */
    }
}

button_uint8_t button_was_pressed(
    button_t *button_instance
)
{
    button_uint8_t button_event;

    button_event =
        button_instance->button_press_event;

    button_instance->button_press_event =
        BUTTON_EVENT_NOT_DETECTED;

    return button_event;
}