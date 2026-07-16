#ifndef SOS_H
#define SOS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define SOS_TIME_POINT_DURATION  150000UL 
#define SOS_TIME_LINE_DURATION   450000UL 
#define SOS_TIME_ELEMENT_GAP     150000UL
#define SOS_TIME_CHARACTER_GAP   700000UL

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void sos_play_point(void)
    \brief  Abstract behavior representing a Morse code 'dot' (. )
*/
extern void sos_play_point(void);

/** \fn     void sos_play_line(void)
    \brief  Abstract behavior representing a Morse code 'dash' (- )
*/
extern void sos_play_line(void);

/** \fn     void sos_play_sos(void)
    \brief  Top-level abstract behavior executing a complete SOS sequence
*/
extern void sos_play_sos(void);

/** \fn     void sos_play_letter_s(void)
    \brief  Plays the letter 'S' (3 points) with internal element gaps.
*/
extern void sos_play_letter_s(void);

/** \fn     void sos_play_letter_o(void)
    \brief  Plays the letter 'O' (3 lines) with internal element gaps.
*/
extern void sos_play_letter_o(void);

#endif