#include "button.h"

#define BUTTON_SAMPLE_MASK             (0x1FU)
#define BUTTON_ALL_PRESSED_SAMPLES     (0x00U)
#define BUTTON_ALL_RELEASED_SAMPLES    (0x1FU)

void button_init(
    button_t *button,
    volatile gpio_uint8_t *ddr_register,
    volatile gpio_uint8_t *port_register,
    volatile gpio_uint8_t *pin_register,
    button_uint8_t pin_number
)
{
    button->pin_register = pin_register;
    button->pin_number = pin_number;

    button->sample_buffer =
        BUTTON_ALL_RELEASED_SAMPLES;

    button->stable_state =
        BUTTON_NOT_PRESSED;

    button->press_event =
        BUTTON_EVENT_NOT_DETECTED;

    gpio_set_direction(
        ddr_register,
        pin_number,
        GPIO_INPUT
    );

    /*
    Activate internal pull-up.
    SW0 is active-low.
    */

    gpio_set_pin(
        port_register,
        pin_number
    );
}

void button_debounce_task(
    button_t *button
)
{
    button_uint8_t raw_sample;

    raw_sample = gpio_read_pin(
        button->pin_register,
        button->pin_number
    );

    button->sample_buffer =
        (button_uint8_t)(
            (
                button->sample_buffer << 1U
            ) |
            raw_sample
        );

    button->sample_buffer &=
        BUTTON_SAMPLE_MASK;

    if (
        button->sample_buffer ==
        BUTTON_ALL_PRESSED_SAMPLES
    )
    {
        if (
            button->stable_state ==
            BUTTON_NOT_PRESSED
        )
        {
            button->stable_state =
                BUTTON_PRESSED;

            button->press_event =
                BUTTON_EVENT_DETECTED;
        }
    }
    else if (
        button->sample_buffer ==
        BUTTON_ALL_RELEASED_SAMPLES
    )
    {
        button->stable_state =
            BUTTON_NOT_PRESSED;
    }
    else
    {
        /*
        Samples are mixed.
        Keep the previous stable state.
        */
    }
}

button_uint8_t button_was_pressed(
    button_t *button
)
{
    button_uint8_t event;

    event = button->press_event;

    button->press_event =
        BUTTON_EVENT_NOT_DETECTED;

    return event;
}