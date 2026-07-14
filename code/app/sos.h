#ifndef SOS_H
#define SOS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Step configuration structure */
typedef struct
{
  uint8_t led_state;
  uint8_t duration_units;
} step_t;

/** \brief  Module specific constant number one */
#define TIME_UNIT (SECOND / 2U)
/** \brief  Module specific constant number one */
#define SOS_TOTAL_STEPS (sizeof(sos_sequence) / sizeof(step_t))

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void sos_update(led_id_t led_id)

    \brief      [ Updates the SOS signal for the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function updates the SOS signal by turning the LED
                 on and off according to the predefined sequence of steps. 
                 Each step specifies whether the LED should be on or off 
                 and for how long. ]
*/
extern void sos_update(led_id_t led_id);

/** \fn     void sos_play(led_id_t led_id)

    \brief      [ Plays the SOS signal for the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function plays the SOS signal by turning the LED
                 on and off in the pattern of three short flashes, three
                 long flashes, and three short flashes. ]
*/
extern void sos_play(led_id_t led_id);

#endif /* SOS_H */