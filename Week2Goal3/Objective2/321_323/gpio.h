#ifndef GPIO_H
#define GPIO_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Pin direction */
#define GPIO_INPUT          (0x00U)
#define GPIO_OUTPUT         (0x01U)

/** \brief  Pin logical levels */
#define GPIO_LOW            (0x00U)
#define GPIO_HIGH           (0x01U)

/** \brief  Type used to point to any port register (PORTx, DDRx, PINx) */
typedef volatile unsigned char * gpio_reg_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Set (write 1 to) a pin of any port
    \param[in]  port  pointer to the PORTx register (e.g. &PORTC)
    \param[in]  pin   pin number, valid range: [0 .. 7]
*/
extern void gpio_set_pin(gpio_reg_t port, unsigned char pin);

/** \brief  Reset (write 0 to) a pin of any port
    \param[in]  port  pointer to the PORTx register
    \param[in]  pin   pin number, valid range: [0 .. 7]
*/
extern void gpio_reset_pin(gpio_reg_t port, unsigned char pin);

/** \brief  Toggle (invert) a pin of any port
    \param[in]  port  pointer to the PORTx register
    \param[in]  pin   pin number, valid range: [0 .. 7]
*/
extern void gpio_toggle_pin(gpio_reg_t port, unsigned char pin);

/** \brief  Set the direction of a pin of any port
    \param[in]  ddr        pointer to the DDRx register (e.g. &DDRC)
    \param[in]  pin        pin number, valid range: [0 .. 7]
    \param[in]  direction  GPIO_INPUT (0) or GPIO_OUTPUT (1)
*/
extern void gpio_set_direction(gpio_reg_t ddr, unsigned char pin, unsigned char direction);

/** \brief  Enable the internal pull-up of a pin (the pin must be an input first)
    \param[in]  port  pointer to the PORTx register
    \param[in]  pin   pin number, valid range: [0 .. 7]
*/
extern void gpio_enable_pullup(gpio_reg_t port, unsigned char pin);

/** \brief  Read the actual level of a pin
    \param[in]  pinx  pointer to the PINx register (e.g. &PINC)
    \param[in]  pin   pin number, valid range: [0 .. 7]
    \return     GPIO_HIGH (1) or GPIO_LOW (0)
*/
extern unsigned char gpio_read_pin(gpio_reg_t pinx, unsigned char pin);

#endif
