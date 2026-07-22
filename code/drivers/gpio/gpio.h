#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific constant number zero */
#define GPIO_INPUT               (0x00U)

/** \brief  Module specific constant number one */
#define GPIO_OUTPUT              (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void gpio_init(void)

    \brief      [ Initializes the GPIO module. ]
    \param[in]  [ None ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Initializes the GPIO module by clearing the PORT registers and DDR registers. ]
*/
extern void gpio_set_pin(volatile uint8_t *port_register, uint8_t pin);

/** \fn     void gpio_set_pin(volatile uint8_t *port_register, uint8_t pin)

    \brief      [ Sets the specified pin of the given port. ]
    \param[in]  port_register [ pointer to the port register (e.g., PORTA, PORTB, etc.) ]
    \param[in]  pin [ the pin number, valid range: [ 0 .. 7 ] ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Uses a bitwise OR assignment operator to set the target
                 bit position to 1, without afffecting the state of the
                 remaining pins in the port. ]
*/
extern void gpio_set_pin(volatile uint8_t *port_register, uint8_t pin);

/** \fn     void gpio_reset_pin(volatile uint8_t *port_register, uint8_t pin)

    \brief      [ Resets the specified pin of the given port. ]
    \param[in]  port_register [ pointer to the port register (e.g., PORTA, PORTB, etc.) ]
    \param[in]  pin [ the pin number, valid range: [ 0 .. 7 ] ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Uses a bitwise AND assignment operator with a negated
                 mask to clear the target bit position to 0, without
                 affecting the state of the remaining pins in the port. ]
*/
extern void gpio_reset_pin(volatile uint8_t *port_register, uint8_t pin);

/** \fn     void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin)

    \brief      [ Sets the direction of the specified pin of the given port. ]
    \param[in]  ddr_register [ pointer to the data direction register (e.g., DDRA, DDRB, etc.) ]
    \param[in]  direction [ the desired direction (GPIO_INPUT or GPIO_OUTPUT) ]
    \param[in]  pin [ the pin number, valid range: [ 0 .. 7 ] ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Sets the corresponding bit in the data direction register
                 to configure the pin as an input (clears the bit) or output
                 (sets the bit). ]
*/
extern void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin);

/** \fn     void gpio_toggle_pin(volatile uint8_t *port_register, uint8_t pin)

    \brief      [ Toggles the specified pin of the given port. ]

    \param[in]  port_register [ pointer to the port register (e.g., PORTA, PORTB, etc.) ]
    \param[in]  pin [ the pin number, valid range: [ 0 .. 7 ] ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Uses a bitwise XOR assignment operator to toggle the
                  target bit position (flip its state), without affecting
                  the state of the remaining pins in the port. ]
*/
extern void gpio_toggle_pin(volatile uint8_t *port_register, uint8_t pin);

/** \fn     uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin)

    \brief      [ Reads the state of the specified pin of the given port. ]
    \param[in]  pin_register [ pointer to the pin register (e.g., PINA, PINB, etc.) ]
    \param[in]  pin [ the pin number, valid range: [ 0 .. 7 ] ]
    \param[out] [ None ]
    \return     [ The normalized state of the pin (0 or 1). ]
    \details    [ Reads the corresponding bit in the pin register by
                  applying a mask and checking if the result is non-zero. ]
*/
extern uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin);

extern void gpio_switch_set_pin(volatile uint8_t *port_register, uint8_t pin);

extern void gpio_switch_reset_pin(volatile uint8_t *port_register, uint8_t pin);

#endif /* GPIO_H */