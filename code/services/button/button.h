#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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

#endif /* BUTTON_H */