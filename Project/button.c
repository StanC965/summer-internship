/**
 * @file button.c
 * @brief Implementation of the button handling and debouncing logic.
 */

#ifndef BUTTON_C
#define BUTTON_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "button.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Encapsulated File-Local Variables
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** @brief Shift register bit history for SW0 debounce window */
static volatile unsigned char buffer_sw0   = 0xFF;
/** @brief Debounced status flag for SW0 (1 = Pressed, 0 = Released) */
static volatile unsigned char state_sw0    = 0;

/** @brief Shift register bit history for OLED1 debounce window */
static volatile unsigned char buffer_oled1 = 0xFF;
/** @brief Debounced status flag for OLED1 (1 = Pressed, 0 = Released) */
static volatile unsigned char state_oled1  = 0;

/** @brief Shift register bit history for OLED2 debounce window */
static volatile unsigned char buffer_oled2 = 0xFF;
/** @brief Debounced status flag for OLED2 (1 = Pressed, 0 = Released) */
static volatile unsigned char state_oled2  = 0;

/** @brief Shift register bit history for OLED3 debounce window */
static volatile unsigned char buffer_oled3 = 0xFF;
/** @brief Debounced status flag for OLED3 (1 = Pressed, 0 = Released) */
static volatile unsigned char state_oled3  = 0;

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
    // SW0 
    buffer_sw0 <<= 1;
    buffer_sw0 |= (button_is_pressed(BUTTON_SW0_PINR, BUTTON_SW0_PIN) ? 0 : 1);
    if ((buffer_sw0 & 0x1F) == 0x00)       state_sw0 = 1;
    else if ((buffer_sw0 & 0x1F) == 0x1F)  state_sw0 = 0;

    // OLED 1 
    buffer_oled1 <<= 1;
    buffer_oled1 |= (button_is_pressed(BUTTON_OLED_1_PINR, BUTTON_OLED_1_PIN) ? 0 : 1);
    if ((buffer_oled1 & 0x1F) == 0x00)      state_oled1 = 1;
    else if ((buffer_oled1 & 0x1F) == 0x1F) state_oled1 = 0;

    // Process OLED 2 
    buffer_oled2 <<= 1;
    buffer_oled2 |= (button_is_pressed(BUTTON_OLED_2_3_PINR, BUTTON_OLED_2_PIN) ? 0 : 1);
    if ((buffer_oled2 & 0x1F) == 0x00)      state_oled2 = 1;
    else if ((buffer_oled2 & 0x1F) == 0x1F) state_oled2 = 0;

    // Process OLED 3 
    buffer_oled3 <<= 1;
    buffer_oled3 |= (button_is_pressed(BUTTON_OLED_2_3_PINR, BUTTON_OLED_3_PIN) ? 0 : 1);
    if ((buffer_oled3 & 0x1F) == 0x00)      state_oled3 = 1;
    else if ((buffer_oled3 & 0x1F) == 0x1F) state_oled3 = 0;
}

unsigned char button_get_sw0_state(void)   { return state_sw0; }
unsigned char button_get_oled1_state(void) { return state_oled1; }
unsigned char button_get_oled2_state(void) { return state_oled2; }
unsigned char button_get_oled3_state(void) { return state_oled3; }

#endif