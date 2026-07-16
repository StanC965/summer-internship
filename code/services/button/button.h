#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
// BUTTON ONBOARD
/** \brief  Module specific constant number zero */
#define BUTTON_ONBOARD_PIN             6

/** \brief  Module specific constant number one */
#define BUTTON_ONBOARD_PCIE            2

/** \brief  Module specific constant number two */
#define BUTTON_ONBOARD_PCINT_PIN       6

// BUTTON OLED1
/** \brief  Module specific constant number three */
#define BUTTON_OLED1_1_PIN             1

/** \brief  Module specific constant number four */
#define BUTTON_OLED1_1_PCIE            2

/** \brief  Module specific constant number five */
#define BUTTON_OLED1_1_PCINT_PIN       1

// BUTTON OLED2
/** \brief  Module specific constant number six */
#define BUTTON_OLED1_2_PIN             0

/** \brief  Module specific constant number seven */
#define BUTTON_OLED1_2_PCIE            0

/** \brief  Module specific constant number eight */
#define BUTTON_OLED1_2_PCINT_PIN       0

// BUTTON OLED3
/** \brief  Module specific constant number nine */
#define BUTTON_OLED1_3_PIN             1

/** \brief  Module specific constant number ten */
#define BUTTON_OLED1_3_PCIE            0

/** \brief  Module specific constant number eleven */
#define BUTTON_OLED1_3_PCINT_PIN       1

/** \brief  Button configuration structure */
typedef struct
{
    volatile uint8_t *ddr_register;
    volatile uint8_t *port_register;
    volatile uint8_t *pin_register;
    uint8_t pin;
} button_config_t;

/** \brief  Button identifier type */
typedef enum
{
    // ATmega328P onboard button
    BUTTON_ONBOARD = 0,

    // OLED1 buttons
    BUTTON_OLED1_1,
    BUTTON_OLED1_2,
    BUTTON_OLED1_3,

    BUTTON_COUNT // Total number of buttons
} button_id_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void button_init(void)

    \brief      [ Initializes the button module. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function configures the data direction registers
                 for all buttons, setting them as inputs. ]
*/
extern void button_init(void);

/** \fn     void button_enable_pullup(button_id_t button_id)

    \brief      [ Enables the pull-up resistor for the specified button. ]
    \param[in]  button_id [ the button identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function enables the pull-up resistor for the 
                 specified button by setting the corresponding bit in 
                 the port register. ]
*/
extern void button_enable_pullup(button_id_t button_id);

/** \fn     uint8_t button_read(button_id_t button_id)

    \brief      [ Reads the state of the specified button. ]
    \param[in]  button_id [ the button identifier ]
    \param[out] [ None ]
    \return     [ The state of the button (1 for pressed, 0 for not pressed) ]
    \details    [ This function reads the state of the specified button
                 by checking the corresponding bit in the pin register. ]
*/
extern uint8_t button_read(button_id_t button_id);

/** \fn     void button_onboard_init_interrupt(void)

    \brief      [ Initializes the interrupt for the onboard button. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function initializes the interrupt for the onboard button
                  by setting the appropriate bits in the interrupt control registers. ]
*/
extern void button_onboard_init_interrupt(void);

/** \fn     void button_oled1_1_init_interrupt(void)

    \brief      [ Initializes the interrupt for the OLED1 button 1. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function initializes the interrupt for the OLED1 button 1
                  by setting the appropriate bits in the interrupt control registers. ]
*/
extern void button_oled1_1_init_interrupt(void);

/** \fn     void button_oled1_2_init_interrupt(void)

    \brief      [ Initializes the interrupt for the OLED button 2. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function initializes the interrupt for the OLED1 button 2
                  by setting the appropriate bits in the interrupt control registers. ]
*/
extern void button_oled1_2_init_interrupt(void);

/** \fn     void button_oled1_3_init_interrupt(void)

    \brief      [ Initializes the interrupt for the OLED1 button 3. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function initializes the interrupt for the OLED1 button 3
                  by setting the appropriate bits in the interrupt control registers. ]
*/
extern void button_oled1_3_init_interrupt(void);

#endif /* BUTTON_H */