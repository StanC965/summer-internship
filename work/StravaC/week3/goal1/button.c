#ifndef BUTTON_C
#define BUTTON_C

#include "gpio.h"
#include "button.h"

/*
Debounce:
- task period = 10 ms;
- samples = 5;
- debounce time = 50 ms;
- button is active-low.
*/

#define BUTTON_SAMPLE_COUNT                 (5U)

#define BUTTON_SAMPLE_MASK                  (0x1FU)
#define BUTTON_ALL_PRESSED_SAMPLES          (0x00U)
#define BUTTON_ALL_RELEASED_SAMPLES         (0x1FU)

#define BUTTON_SAMPLE_INITIAL_VALUE         \
    (BUTTON_ALL_RELEASED_SAMPLES)

#define BUTTON_SHIFT_ONE_POSITION           (1U)

#define BUTTON_INPUT_DIRECTION              (GPIO_INPUT)
#define BUTTON_PULL_UP_ENABLE               (GPIO_HIGH)

#define BUTTON_ACTIVE_LEVEL                 (GPIO_LOW)

static volatile unsigned char *button_pin_register_address;
static button_uint8_t button_pin_number_value;

static button_uint8_t button_sample_buffer;
static button_uint8_t button_stable_state;

void button_init(
    volatile unsigned char *button_ddr_register,
    volatile unsigned char *button_port_register,
    volatile unsigned char *button_pin_register,
    button_uint8_t button_pin_number
)
{
    button_pin_register_address =
        button_pin_register;

    button_pin_number_value =
        button_pin_number;

    button_sample_buffer =
        BUTTON_SAMPLE_INITIAL_VALUE;

    button_stable_state =
        BUTTON_NOT_PRESSED;

    gpio_set_direction(
        button_ddr_register,
        button_pin_number,
        BUTTON_INPUT_DIRECTION
    );

    /*
    Enable the internal pull-up resistor.
    */

    gpio_set_pin(
        button_port_register,
        button_pin_number
    );
}

void button_debounce_task(void)
{
    button_uint8_t button_raw_sample;

    button_raw_sample = gpio_read_pin(
        button_pin_register_address,
        button_pin_number_value
    );

    /*
    Moving five-sample window:

    old samples are shifted left;
    the newest sample is inserted into bit 0;
    only the last five bits are preserved.
    */

    button_sample_buffer = (button_uint8_t)(
        (
            button_sample_buffer <<
            BUTTON_SHIFT_ONE_POSITION
        ) |
        button_raw_sample
    );

    button_sample_buffer &= BUTTON_SAMPLE_MASK;

    /*
    Majority condition requested by the exercise:
    all five samples must have the same value.
    */

    if (
        button_sample_buffer ==
        BUTTON_ALL_PRESSED_SAMPLES
    )
    {
        button_stable_state =
            BUTTON_PRESSED;
    }
    else if (
        button_sample_buffer ==
        BUTTON_ALL_RELEASED_SAMPLES
    )
    {
        button_stable_state =
            BUTTON_NOT_PRESSED;
    }
    else
    {
        /*
        Mixed samples mean bouncing is still present.
        Keep the previously validated stable state.
        */
    }
}

button_uint8_t button_is_pressed(void)
{
    return button_stable_state;
}

#endif