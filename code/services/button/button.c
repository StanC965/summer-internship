#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "button.h"
#include <iom324pb.h>
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static const button_config_t button_table[BUTTON_COUNT] = {
    // ATmega328P onboard button
    {&DDRC, &PORTC, &PINC, BUTTON_ONBOARD_PIN},

    // OLED1 buttons
    {&DDRC, &PORTC, &PINC, BUTTON_OLED1_1_PIN},
    {&DDRA, &PORTA, &PINA, BUTTON_OLED1_2_PIN},
    {&DDRA, &PORTA, &PINA, BUTTON_OLED1_3_PIN},
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void button_init(void)
{
    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        gpio_set_direction(button_table[i].ddr_register, GPIO_INPUT, button_table[i].pin);
    }
}

void button_enable_pullup(button_id_t button_id)
{
    if (button_id < BUTTON_COUNT)
    {
        gpio_set_pin(button_table[button_id].port_register, button_table[button_id].pin);
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

void button_onboard_init_interrupt(void)
{
    gpio_set_pin(&PCICR, BUTTON_ONBOARD_PCIE);
    gpio_set_pin(&PCMSK2, BUTTON_ONBOARD_PCINT_PIN);
}

void button_oled1_1_init_interrupt(void)
{
    gpio_set_pin(&PCICR, BUTTON_OLED1_1_PCIE);
    gpio_set_pin(&PCMSK2, BUTTON_OLED1_1_PCINT_PIN);
}

void button_oled1_2_init_interrupt(void)
{
    gpio_set_pin(&PCICR, BUTTON_OLED1_2_PCIE);
    gpio_set_pin(&PCMSK2, BUTTON_OLED1_2_PCINT_PIN);
}

void button_oled1_3_init_interrupt(void)
{
    gpio_set_pin(&PCICR, BUTTON_OLED1_3_PCIE);
    gpio_set_pin(&PCMSK2, BUTTON_OLED1_3_PCINT_PIN);
}

#endif /* BUTTON_C */