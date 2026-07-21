/**
 * @file led.h
 * @brief Header file for LED hardware control and status indicators.
 * @details Contains pin declarations, timing constants, and function prototypes
 *          for active-low LED driving operations.
 */

#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** @name Onboard LED Pin Mapping */
/**@{*/
#define LED_LED0_PORT       (&PORTC)
#define LED_LED0_DDR        (&DDRC)
#define LED_LED0_PIN        7
/**@}*/

/** @name Software Delay Constants */
/**@{*/
#define LED_TIME_BLINK_FAST      60000UL
#define LED_TIME_BLINK_SLOW      175000UL
/**@}*/

/** @name OLED Display LED Pin Mapping */
/**@{*/
#define LED_OLED_1_2_DDR        (&DDRD)
#define LED_OLED_1_2_PORT       (&PORTD)
#define LED_OLED_1_PIN          5       
#define LED_OLED_2_PIN          4             

#define LED_OLED_3_DDR          (&DDRA)
#define LED_OLED_3_PORT         (&PORTA)
#define LED_OLED_3_PIN          3      
/**@}*/

/** @name Expansion I/O LED Pin Mapping */
/**@{*/
#define LED_IO_LED_DDR          (&DDRB)
#define LED_IO_LED_PORT         (&PORTB)
#define LED_IO_LED_PIN          3
/**@}*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * @brief Initializes all system LEDs as output pins and turns them OFF by default.
 */
void led_init(void);

/**
 * @brief Configures a single target MCU pin as an output for an LED.
 * @param ddr_reg Pointer to the Data Direction Register (e.g., &DDRC).
 * @param pin_number Target pin index on the register (0–7).
 */
void led_configure_pin(volatile unsigned char *ddr_reg, unsigned char pin_number);

/**
 * @brief Turns an active-low LED ON by driving its pin LOW (0).
 * @param port_reg Pointer to the target PORT register (e.g., &PORTC).
 * @param pin_number Target pin index on the register (0–7).
 */
extern void led_power_on(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Turns an active-low LED OFF by driving its pin HIGH (1).
 * @param port_reg Pointer to the target PORT register (e.g., &PORTC).
 * @param pin_number Target pin index on the register (0–7).
 */
extern void led_power_off(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Inverts the logical output state of a targeted LED pin.
 * @param port_reg Pointer to the target PORT register (e.g., &PORTC).
 * @param pin_number Target pin index on the register (0–7).
 */
extern void led_toggle(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Toggles an LED and executes a fast blocking delay loop.
 * @param port_reg Pointer to the target PORT register (e.g., &PORTC).
 * @param pin_number Target pin index on the register (0–7).
 */
extern void led_blink_fast(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Toggles an LED and executes a slow blocking delay loop.
 * @param port_reg Pointer to the target PORT register (e.g., &PORTC).
 * @param pin_number Target pin index on the register (0–7).
 */
extern void led_blink_slow(volatile unsigned char *port_reg, unsigned char pin_number);

#endif