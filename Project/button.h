/**
 * @file button.h
 * @brief Header file for button interface and pin mapping.
 * @details Provides definitions, configuration macros, and function prototypes
 *          for reading and debouncing system pushbuttons.
 */

#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** @name Button Hardware Pin Definitions */
/**@{*/
#define BUTTON_SW0_DDR             (&DDRC)
#define BUTTON_SW0_PORT            (&PORTC)
#define BUTTON_SW0_PINR            (&PINC)
#define BUTTON_SW0_PIN             6

#define BUTTON_OLED_1_DDR          (&DDRC)
#define BUTTON_OLED_1_PORT         (&PORTC)
#define BUTTON_OLED_1_PINR         (&PINC)
#define BUTTON_OLED_1_PIN          1       

#define BUTTON_OLED_2_3_DDR        (&DDRA)
#define BUTTON_OLED_2_3_PORT       (&PORTA)
#define BUTTON_OLED_2_3_PINR       (&PINA)
#define BUTTON_OLED_2_PIN          0            
#define BUTTON_OLED_3_PIN          1
/**@}*/

/** @name Pin Change Interrupt Mapping */
/**@{*/
#define PCINT22_SW0                6
#define PCINT17_SW1                1   
#define PCINT0_SW2                 0   
#define PCINT1_SW3                 1   

#define PCIE0_PORT_A               0   
#define PCIE2_PORT_C               2     
/**@}*/

/** @brief Threshold value used for debouncing calculation timing */
#define BUTTON_DEBOUNCE_THRESHOLD 500

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * @brief Initializes the button module by setting up input configurations, 
 *        enabling pull-ups, and configuring pin change interrupts.
 */
void button_init(void);

/**
 * @brief Configures a single target pin as an input and enables its pull-up resistor.
 * @param ddr_reg Pointer to the Data Direction Register (e.g., &DDRC).
 * @param port_reg Pointer to the PORT Register for pull-up configuration (e.g., &PORTC).
 * @param pin_number Target pin index on the port (0-7).
 */
void button_configure_pin(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Reads a targeted pin status instantly without any debounce handling.
 * @param pin_reg Pointer to the PIN Register (e.g., &PINC).
 * @param pin_number Target pin index on the port (0-7).
 * @return 1 if the button is currently pressed (active LOW), 0 if released (HIGH).
 */
unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number);

/**
 * @brief Calculates 5-sample moving bitwise history windows for all four panel buttons.
 * @details Must be executed periodically inside a scheduled task slot (e.g., 50ms).
 */
void button_debounce_update(void);

/* Public Getter Interfaces */

/**
 * @brief Gets the debounced state of switch SW0.
 * @return 1 if pressed, 0 if released.
 */
unsigned char button_get_sw0_state(void);

/**
 * @brief Gets the debounced state of OLED button 1.
 * @return 1 if pressed, 0 if released.
 */
unsigned char button_get_oled1_state(void);

/**
 * @brief Gets the debounced state of OLED button 2.
 * @return 1 if pressed, 0 if released.
 */
unsigned char button_get_oled2_state(void);

/**
 * @brief Gets the debounced state of OLED button 3.
 * @return 1 if pressed, 0 if released.
 */
unsigned char button_get_oled3_state(void);

#endif