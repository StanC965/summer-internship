#include "button.h"

/* 5 samples x 10 ms = 50 ms debounce. Buttons are active-low. */
#define BUTTON_SAMPLE_MASK                 (0x1FU)
#define BUTTON_ALL_PRESSED_SAMPLES         (0x00U)
#define BUTTON_ALL_RELEASED_SAMPLES        (0x1FU)

void button_init(button_t *button_instance, volatile gpio_uint8_t *button_ddr_register, volatile gpio_uint8_t *button_port_register, volatile gpio_uint8_t *button_pin_register, button_uint8_t button_pin_number)
{
    button_instance->button_pin_register = button_pin_register;
    button_instance->button_pin_number = button_pin_number;
    button_instance->button_sample_buffer = BUTTON_ALL_RELEASED_SAMPLES;
    button_instance->button_stable_state = BUTTON_NOT_PRESSED;
    button_instance->button_press_event = BUTTON_EVENT_NOT_DETECTED;

    gpio_set_direction(button_ddr_register, button_pin_number, GPIO_INPUT);
    gpio_set_pin(button_port_register, button_pin_number);
}

void button_debounce_task(button_t *button_instance)
{
    button_uint8_t raw_sample;

    raw_sample = gpio_read_pin(button_instance->button_pin_register, button_instance->button_pin_number);
    button_instance->button_sample_buffer = (button_uint8_t)((button_instance->button_sample_buffer << 1U) | raw_sample);
    button_instance->button_sample_buffer &= BUTTON_SAMPLE_MASK;

    if (button_instance->button_sample_buffer == BUTTON_ALL_PRESSED_SAMPLES)
    {
        if (button_instance->button_stable_state == BUTTON_NOT_PRESSED)
        {
            button_instance->button_stable_state = BUTTON_PRESSED;
            button_instance->button_press_event = BUTTON_EVENT_DETECTED;
        }
    }
    else if (button_instance->button_sample_buffer == BUTTON_ALL_RELEASED_SAMPLES)
    {
        button_instance->button_stable_state = BUTTON_NOT_PRESSED;
    }
    else
    {
    }
}

button_uint8_t button_was_pressed(button_t *button_instance)
{
    button_uint8_t event_copy = button_instance->button_press_event;
    button_instance->button_press_event = BUTTON_EVENT_NOT_DETECTED;
    return event_copy;
}
