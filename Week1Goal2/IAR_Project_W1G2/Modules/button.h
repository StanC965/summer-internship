#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       button.h
 *  \brief      BUTTON module interface.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>
#include "gpio.h"
#include "Utils/utils.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief parameter type unsigned byte (8 bit) */
typedef unsigned char button_uint8_t;

/** \brief SW0 identifier */
#define SW0    (0U)

/** \brief BUTTON1 identifier */
#define BUTTON1    (1U)

/** \brief BUTTON2 identifier */
#define BUTTON2    (2U)

/** \brief BUTTON3 identifier */
#define BUTTON3    (3U)
                
/** \brief button pins */
#define SW0_PIN     (6U)
#define BUTTON1_PIN     (1U)
#define BUTTON2_PIN     (0U)
#define BUTTON3_PIN     (1U)

#define PCIE0 0
#define PCIE1 1
#define PCIE2 2
#define PCIE3 3
#define PCIE4 4

/** \brief Total number of buttons */
#define NUMBER_OF_BUTTONS  (4U)

/** \brief Button states */
#define BUTTON_PRESSED          (0U)
#define BUTTON_NOT_PRESSED      (1U)

/** \brief Debounce */
#define PRESSED_CONFIDENCE_LEVEL_TARGET        (500)
#define RELEASED_CONFIDENCE_LEVEL_TARGET       (500)

/** \brief  Button configuration structure */
typedef struct {
  
  volatile gpio_uint8_t *port;
  gpio_uint8_t pin;
  volatile gpio_uint8_t *pin_register;
  volatile gpio_uint8_t *ddr;
  
} button_config_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void BUTTON_Init(void)

    \brief      Initializes all BUTTONs.
    \param[in]  None.
    \param[out] None.
    \return     None.
    \details    Configures the GPIO pins connected to the BUTTONs as
                inputs.
*/
extern void BUTTON_Init(void);

/** \fn     void button_init(button_uint8_t button)

    \brief      Initializes a specific BUTTON.
    \param[in]  button BUTTON identifier (SW0...BUTTON3).
    \param[out] None.
    \return     None.
    \details    Configures the GPIO pins connected to the BUTTON as
                inputs.
*/
extern void button_init(button_uint8_t button);

/** \fn     void button_interrupt_init(button_uint8_t button)

    \brief      Enables the interrupt for a specific BUTTON.
    \param[in]  button BUTTON identifier (SW0...BUTTON3).
    \param[out] None.
    \return     None.
    \details    Configures the corresponding PCMSK and PCICR registers based
                on the button's port to trigger Pin Change Interrupts (PCINT),
                and enables global interrupts.
*/
extern void button_interrupt_init(button_uint8_t button);

/** \fn     void button_enable_pullup(button_uint8_t button)

    \brief      Enable pullup resistor.
    \param[in]  button BUTTON identifier (SW0...BUTTON3).
    \param[out] None.
    \return     None.
    \details    Enable pullup resistor.
*/
extern void button_enable_pullup(button_uint8_t button);


/** \fn     unsigned char button_read_state(button_uint8_t button)

    \brief      Read the state of the button
    \param[in]  button BUTTON identifier (SW0...BUTTON3).
    \param[out] None.
    \return     return value of 0 or 1
    \details    Read the value of a button from the pin connected to the button
*/
extern unsigned char button_read_state(button_uint8_t button);

#endif