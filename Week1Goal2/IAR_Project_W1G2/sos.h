#ifndef SOS_H
#define SOS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       sos.h
 *  \brief      sos app interface.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "Utils/utils.h"
#include "Modules/led.h"
#include "Modules/button.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void SOS_play(led_uint8_t led, unsigned char *state)

    \brief      Play SOS signal.
    \param[in]  led LED identifier (LED0...LED3), state of te button.
    \param[out] None.
    \return     None.
    \details    Turn on and off LED in SOS pattern turning 
                on and off the signal by button
*/
extern void SOS_play(led_uint8_t led, unsigned char *state);

#endif