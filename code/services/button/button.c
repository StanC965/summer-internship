#ifndef BUTTON_C
#define BUTTON_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "button.h"
#include <iom324pb.h>
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static volatile uint8_t button_sample_buffer[BUTTON_COUNT] = {0};
static volatile uint8_t button_stable_state[BUTTON_COUNT] = {0};
static volatile uint8_t button_press_event[BUTTON_COUNT] = {0};

static const button_config_t button_table[BUTTON_COUNT] = {
    // ATmega328P onboard button
    {&DDRC, &PORTC, &PINC, BUTTON_ONBOARD_PIN},

    // OLED1 buttons
    {&DDRC, &PORTC, &PINC, BUTTON_OLED1_1_PIN},
    {&DDRA, &PORTA, &PINA, BUTTON_OLED1_2_PIN},
    {&DDRA, &PORTA, &PINA, BUTTON_OLED1_3_PIN},
};

static const button_int_config_t button_int_table[BUTTON_COUNT] = {
    // ATmega328P onboard button
    {&PCICR, BUTTON_ONBOARD_PCIE, &PCMSK2, BUTTON_ONBOARD_PCINT_PIN},

    // OLED1 buttons
    {&PCICR, BUTTON_OLED1_1_PCIE, &PCMSK2, BUTTON_OLED1_1_PCINT_PIN},
    {&PCICR, BUTTON_OLED1_2_PCIE, &PCMSK0, BUTTON_OLED1_2_PCINT_PIN},
    {&PCICR, BUTTON_OLED1_3_PCIE, &PCMSK0, BUTTON_OLED1_3_PCINT_PIN},
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void button_init(void)
{
    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        gpio_set_direction(button_table[i].ddr_register, GPIO_INPUT, button_table[i].pin);
        gpio_set_pin(button_table[i].port_register, button_table[i].pin);
    }
}

uint8_t button_read(button_id_t button_id)
{
    if (button_id < BUTTON_COUNT)
    {
        return gpio_read_pin(button_table[button_id].pin_register, button_table[button_id].pin);
    }

    return -1;
}

void button_init_interrupt(void)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        gpio_set_pin(button_int_table[i].pcint_register, button_int_table[i].pcint_enable_bit);
        gpio_set_pin(button_int_table[i].pcmsk_register, button_int_table[i].pcint_pin);
    }
}

static uint8_t button_read_raw(button_id_t btn)
{
    if (btn >= BUTTON_COUNT)
    {
        return 0;
    }
    
    return (gpio_read_pin(button_table[btn].pin_register, button_table[btn].pin) == 0);
}

void button_debounce_update(void)
{
    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        uint8_t raw_sample = button_read_raw((button_id_t)i);

        button_sample_buffer[i] = ((button_sample_buffer[i] << 1) | raw_sample) & BUTTON_DEBOUNCE_MASK;

        if ((button_sample_buffer[i] == BUTTON_DEBOUNCE_PRESSED) && (button_stable_state[i] == 0))
        {
            button_stable_state[i] = 1;
            button_press_event[i] = 1;
        }
        else if ((button_sample_buffer[i] == BUTTON_DEBOUNCE_RELEASED) && (button_stable_state[i] == 1))
        {
            button_stable_state[i] = 0;
        }
    }
}

uint8_t button_was_pressed(button_id_t button_id)
{
    uint8_t event = 0;

    if (button_id < BUTTON_COUNT)
    {
        event = button_press_event[button_id];
        button_press_event[button_id] = 0;
    }

    return event;
}

uint8_t button_is_pressed(button_id_t button_id)
{
    return (button_id < BUTTON_COUNT) ? button_stable_state[button_id] : 0;
}

#endif /* BUTTON_C */