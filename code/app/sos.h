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
#define TIME_UNIT                (SECOND / 2U)

/** \brief  Module specific constant number two */
#define LED_OFF                   0

/** \brief  Module specific constant number three */
#define LED_ON                    1

/** \brief  Module specific constant number four */
#define SOS_UNIT_DPOINT           1 // duration of a point

/** \brief  Module specific constant number five */
#define SOS_UNIT_DLINE            3 // duration of a line

/** \brief  Module specific constant number six */
#define SOS_GAP_INTRA_LETTER      1 // gap between parts of the same letter

/** \brief  Module specific constant number seven */
#define SOS_GAP_INTER_LETTER      2 // gap between letters

/** \brief  Module specific constant number eight */
#define SOS_GAP_INTER_WORD        7 // gap between words

/** \brief  Module specific constant number nine */
#define SOS_TOTAL_STEPS           (sizeof(sos_sequence) / sizeof(step_t))

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