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
    {&DDRC, &PORTC, &PINC, 6},

    // OLED1 buttons
    {&DDRC, &PORTC, &PINC, 1},
    {&DDRA, &PORTA, &PINA, 0},
    {&DDRA, &PORTA, &PINA, 1},
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

#endif /* BUTTON_C */