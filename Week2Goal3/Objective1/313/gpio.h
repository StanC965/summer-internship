#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Pin direction: input */
#define GPIO_INPUT          (0x00U)

/** \brief  Pin direction: output */
#define GPIO_OUTPUT         (0x01U)

/** \brief  Pin logical levels */
#define GPIO_LOW            (0x00U)
#define GPIO_HIGH           (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Set (write 1 to) a PORTC pin, other pins unchanged
    \param[in]  pin  pin number, valid range: [0 .. 7]
*/
extern void gpio_set_pin(unsigned char pin);

/** \brief  Reset (write 0 to) a PORTC pin, other pins unchanged
    \param[in]  pin  pin number, valid range: [0 .. 7]
*/
extern void gpio_reset_pin(unsigned char pin);

/** \brief  Toggle (invert) a PORTC pin, other pins unchanged
    \param[in]  pin  pin number, valid range: [0 .. 7]
*/
extern void gpio_toggle_pin(unsigned char pin);

/** \brief  Set the direction of a PORTC pin
    \param[in]  pin        pin number, valid range: [0 .. 7]
    \param[in]  direction  GPIO_INPUT (0) or GPIO_OUTPUT (1)
*/
extern void gpio_set_direction(unsigned char pin, unsigned char direction);

/** \brief  Enable the internal pull-up resistor of a PORTC pin
    \param[in]  pin  pin number, valid range: [0 .. 7]
    \details    The pin must be configured as input first.
*/
extern void gpio_enable_pullup(unsigned char pin);

/** \brief  Read the actual level of a PORTC pin (reads the PINC register)
    \param[in]  pin  pin number, valid range: [0 .. 7]
    \return     GPIO_HIGH (1) or GPIO_LOW (0)
*/
extern unsigned char gpio_read_pin(unsigned char pin);

#endif
