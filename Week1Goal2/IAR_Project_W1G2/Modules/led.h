#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       led.h
 *  \brief      LED module interface.
 *  \author     Chirila Viorel
 *  \date       12.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief parameter type unsigned byte (8 bit) */
typedef unsigned char led_uint8_t;

/** \brief LED0 identifier */
#define LED0    (0U)

/** \brief LED1 identifier */
#define LED1    (1U)

/** \brief LED2 identifier */
#define LED2    (2U)

/** \brief LED3 identifier */
#define LED3    (3U)
                
/** \brief Total number of leds */
#define NUMBER_OF_LEDS  (4U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void LED_Init(void)

    \brief      Initializes all LEDs.
    \param[in]  None.
    \param[out] None.
    \return     None.
    \details    Configures the GPIO pins connected to the LEDs as
                outputs and turns all LEDs OFF.
*/
extern void LED_Init(void);

/** \fn     void PowerOn_LED(led_uint8_t led)

    \brief      Turns the selected LED ON.
    \param[in]  led LED identifier (LED0...LED3).
    \param[out] None.
    \return     None.
    \details    Activates the selected LED by controlling the
                corresponding GPIO pin. Since the LEDs are active LOW,
                the function clears the corresponding output pin.
*/
extern void PowerOn_LED(led_uint8_t led);

/** \fn     void PowerOff_LED(led_uint8_t led)

    \brief      Turns the selected LED OFF.
    \param[in]  led LED identifier (LED0...LED3).
    \param[out] None.
    \return     None.
    \details    Deactivates the selected LED by controlling the
                corresponding GPIO pin. Since the LEDs are active LOW,
                the function sets the corresponding output pin.
*/
extern void PowerOff_LED(led_uint8_t led);

/** \fn     void Toggle_LED(led_uint8_t led)

    \brief      Toggles the state of the selected LED.
    \param[in]  led LED identifier (LED0...LED3).
    \param[out] None.
    \return     None.
    \details    Changes the state of the selected LED from ON to OFF
                or from OFF to ON by toggling the corresponding GPIO pin.
*/
extern void Toggle_LED(led_uint8_t led);

#endif