/**
 * @file gpio.h
 * @brief General Purpose Input/Output (GPIO) abstraction layer header file.
 * @details Provides portable bitwise manipulation primitives and direction constants for MCU registers.
 */

#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** @brief Logical direction value representing an input pin */
#define GPIO_INPUT  0

/** @brief Logical direction value representing an output pin */
#define GPIO_OUTPUT 1

/** @brief Alias type definition for an 8-bit unsigned byte */
typedef unsigned char mod_uint8_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * @brief Initializes the low-level GPIO peripheral module.
 */
void gpio_init(void);

/**
 * @brief Drives a specific register pin HIGH (1).
 * @param port_reg Pointer to the target output register (e.g., &PORTA).
 * @param pin_number Index of the pin to set (0–7).
 */
extern void gpio_set_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Drives a specific register pin LOW (0).
 * @param port_reg Pointer to the target output register (e.g., &PORTA).
 * @param pin_number Index of the pin to clear (0–7).
 */
extern void gpio_reset_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Sets a pin's hardware state to either input or output.
 * @param port_reg Pointer to the target Data Direction Register (e.g., &DDRA).
 * @param pin_number Index of the pin to configure (0–7).
 * @param direction Mode selector (\ref GPIO_INPUT or \ref GPIO_OUTPUT).
 */
extern void gpio_set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction);

/**
 * @brief Inverts the bit state of a specific port register pin.
 * @param port_reg Pointer to the target output register (e.g., &PORTA).
 * @param pin_number Index of the pin to invert (0–7).
 */
extern void gpio_toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/**
 * @brief Reads the voltage input status from an input register.
 * @param pin_reg Pointer to the target PIN register (e.g., &PINA).
 * @param pin_number Index of the pin to read (0–7).
 * @return 1 if the input voltage state is HIGH, 0 if LOW.
 */
extern unsigned char gpio_read_pin(volatile unsigned char *pin_reg, unsigned char pin_number);

#endif