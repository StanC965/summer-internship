#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Pin direction: input */
#define GPIO_INPUT          (0x00U)

/** \brief  Pin direction: output */
#define GPIO_OUTPUT         (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void gpio_set_pin(unsigned char pin)

    \brief      Set (write 1 to) a pin of PORTC
    \param[in]  pin - pin number, valid range: [0 .. 7]
    \return     void
    \details    Sets the given PORTC pin without affecting the other pins.
*/
extern void gpio_set_pin(unsigned char pin);

/** \fn     void gpio_reset_pin(unsigned char pin)

    \brief      Reset (write 0 to) a pin of PORTC
    \param[in]  pin - pin number, valid range: [0 .. 7]
    \return     void
    \details    Resets the given PORTC pin without affecting the other pins.
*/
extern void gpio_reset_pin(unsigned char pin);

/** \fn     void gpio_toggle_pin(unsigned char pin)

    \brief      Toggle (invert) a pin of PORTC
    \param[in]  pin - pin number, valid range: [0 .. 7]
    \return     void
    \details    Inverts the given PORTC pin without affecting the other pins.
*/
extern void gpio_toggle_pin(unsigned char pin);

/** \fn     void gpio_set_direction(unsigned char pin, unsigned char direction)

    \brief      Set the direction of a PORTC pin
    \param[in]  pin - pin number, valid range: [0 .. 7]
    \param[in]  direction - GPIO_INPUT (0) or GPIO_OUTPUT (1)
    \return     void
    \details    Configures the given PORTC pin as input or output via DDRC.
*/
extern void gpio_set_direction(unsigned char pin, unsigned char direction);

#endif
