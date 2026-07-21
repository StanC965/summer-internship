#ifndef BUTTON_C
#define BUTTON_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "button.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Encapsulated File-Local Variables
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static volatile unsigned char button_history_buffer = 0xFF;
static volatile unsigned char button_debounced_state = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void button_init(void)
{
    button_configure_pin(BUTTON_SW0_DDR, BUTTON_SW0_PORT, BUTTON_SW0_PIN);
    button_configure_pin(BUTTON_OLED_1_DDR, BUTTON_OLED_1_PORT, BUTTON_OLED_1_PIN);
    button_configure_pin(BUTTON_OLED_2_3_DDR, BUTTON_OLED_2_3_PORT, BUTTON_OLED_2_PIN);
    button_configure_pin(BUTTON_OLED_2_3_DDR, BUTTON_OLED_2_3_PORT, BUTTON_OLED_3_PIN);
    
    PCMSK2 |= (1 << PCINT22_SW0) | (1 << PCINT17_SW1);
    PCMSK0 |= (1 << PCINT0_SW2) | (1 << PCINT1_SW3); 

    PCICR |= (1 << PCIE0_PORT_A) | (1 << PCIE2_PORT_C);
}

void button_configure_pin(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number)
{
    gpio_set_direction(ddr_reg, pin_number, GPIO_INPUT);    
    gpio_set_pin(port_reg, pin_number);
}

unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number)
{
    return (gpio_read_pin(pin_reg, pin_number) == 0) ? 1 : 0;
}

void button_debounce_update(void)
{
    unsigned char raw_sample;
    
    if (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN))
    {
        raw_sample = 0; 
    }
    else
    {
        raw_sample = 1;
    }
    
    button_history_buffer <<= 1;
    
    button_history_buffer |= (raw_sample & 0x01);
    
    if ((button_history_buffer & 0x1F) == 0x00)
    {
        button_debounced_state = 1;
    }
    else if ((button_history_buffer & 0x1F) == 0x1F)
    {
        button_debounced_state = 0;
    }
}

unsigned char button_get_debounced_state(void)
{
    return button_debounced_state;
}

#endif