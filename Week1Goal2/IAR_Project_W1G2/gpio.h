#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief parameter type unsigned byte (8 bit) */
typedef unsigned char gpio_uint8_t;

/** \brief GPIO direction */
#define GPIO_INPUT     (0U)
#define GPIO_OUTPUT    (1U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Sets the selected GPIO pin to logic HIGH.
    \param[in]  port Pointer to the GPIO PORT register.
    \param[in]  pin Pin number (0...7).
    \param[out] None.
    \return     None.
    \details    Sets the selected bit in the specified PORT register
                without affecting the remaining bits.
*/
extern void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn     void gpio_reset_pin(volatile unsigned char *port, gpio_uint8_t pin)

    \brief      Resets the selected GPIO pin to logic LOW.
    \param[in]  port Pointer to the GPIO PORT register.
    \param[in]  pin Pin number (0...7).
    \param[out] None.
    \return     None.
    \details    Clears the selected bit in the specified PORT register
                without affecting the remaining bits.
*/
extern void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn     void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Toggles the selected GPIO pin.
    \param[in]  port Pointer to the GPIO PORT register.
    \param[in]  pin Pin number (0...7).
    \param[out] None.
    \return     None.
    \details    Changes the selected pin from HIGH to LOW or from LOW
                to HIGH without affecting the other pins.
*/
extern void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn     void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction)

    \brief      Configures the direction of a GPIO pin.
    \param[in]  ddr Pointer to the DDR register.
    \param[in]  pin Pin number (0...7).
    \param[in]  direction GPIO_INPUT or GPIO_OUTPUT.
    \param[out] None.
    \return     None.
    \details    Configures the selected pin as an input or an output
                without affecting the direction of the remaining pins.
*/
extern void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction);

#endif