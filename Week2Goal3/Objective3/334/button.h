#ifndef BUTTON_H
#define BUTTON_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  SW0 on the main board: PC6 */
#define SW0_DDR             (&DDRC)
#define SW0_PORT            (&PORTC)
#define SW0_PIN_REG         (&PINC)
#define SW0_PIN             (6U)

/** \brief  BUTTON1 on OLED1 (EXT1): PC1 */
#define BUTTON1_DDR         (&DDRC)
#define BUTTON1_PORT        (&PORTC)
#define BUTTON1_PIN_REG     (&PINC)
#define BUTTON1_PIN         (1U)

/** \brief  BUTTON2 on OLED1 (EXT1): PA0 */
#define BUTTON2_DDR         (&DDRA)
#define BUTTON2_PORT        (&PORTA)
#define BUTTON2_PIN_REG     (&PINA)
#define BUTTON2_PIN         (0U)

/** \brief  BUTTON3 on OLED1 (EXT1): PA1 */
#define BUTTON3_DDR         (&DDRA)
#define BUTTON3_PORT        (&PORTA)
#define BUTTON3_PIN_REG     (&PINA)
#define BUTTON3_PIN         (1U)

/** \brief  Button states */
#define BUTTON_RELEASED     (0x00U)
#define BUTTON_PRESSED      (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Initialize a button pin as input with internal pull-up
    \param[in]  ddr   pointer to the DDRx register of the button
    \param[in]  port  pointer to the PORTx register of the button
    \param[in]  pin   pin number of the button
*/
extern void button_init(gpio_reg_t ddr, gpio_reg_t port, unsigned char pin);

/** \brief  Read a button state with debounce
    \param[in]  pinx  pointer to the PINx register of the button
    \param[in]  pin   pin number of the button
    \return     BUTTON_PRESSED (1) or BUTTON_RELEASED (0)
    \details    All the buttons are active low. The signal is read twice, with a short
                delay between the readings, to filter out the contact bouncing noise.
*/
extern unsigned char button_is_pressed(gpio_reg_t pinx, unsigned char pin);

#endif
