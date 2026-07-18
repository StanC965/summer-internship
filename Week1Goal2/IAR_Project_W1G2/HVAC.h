#ifndef HVAC_H
#define HVAC_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       HVAC.h
 *  \brief      HVAC Control Panel Prototype module interface.
 *  \author     Chirila Viorel
 *  \date       18.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Utils/utils.h"
#include "Modules/led.h"
#include "Modules/button.h"
#include "ISR/interrupts.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void Handle_MasterControl_Event(void)

    \brief      Handles the SW0 master control button events.
    \param[in]  None.
    \param[out] None.
    \return     None.
    \details    Checks if the SW0 event flag is set. If pressed, it toggles 
                the state of the HVAC control panel between NORMAL and BLOCKED.
                When entering the BLOCKED state, it forces all vent LEDs OFF 
                and turns LED0 ON.
*/
extern void Handle_MasterControl_Event(void);

/** \fn     void Handle_VentControl_Event(button_uint8_t button_id, unsigned char led_id, volatile unsigned char *event_flag)

    \brief      Handles the vent control button events (Left, Central, Right).
    \param[in]  button_id BUTTON identifier (BUTTON1, BUTTON2, BUTTON3).
    \param[in]  led_id LED identifier corresponding to the vent (LED1, LED2, LED3).
    \param[in]  event_flag Pointer to the volatile flag set by the ISR.
    \param[out] event_flag The flag is reset to 0 after processing.
    \return     None.
    \details    Checks the specific event flag. If the button was pressed:
                - If the panel is BLOCKED, it triggers a fast blink warning on LED0.
                - If the panel is NORMAL, it toggles the state of the associated vent LED.
                Automatically handles the debounce and clears the event flag.
*/
extern void Handle_VentControl_Event(button_uint8_t button_id, unsigned char led_id, volatile unsigned char *event_flag);

#endif /* HVAC_H */