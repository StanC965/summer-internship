#ifndef SOS_H
#define SOS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void Play_Point(void)
    \brief  Abstract behavior representing a Morse code 'dot' (. )
*/
extern void Play_Point(void);

/** \fn     void Play_Line(void)
    \brief  Abstract behavior representing a Morse code 'dash' (- )
*/
extern void Play_Line(void);

/** \fn     void Play_SOS(void)
    \brief  Top-level abstract behavior executing a complete SOS sequence
*/
extern void Play_SOS(void);

/** \fn     void Play_Letter_S(void)
    \brief  Plays the letter 'S' (3 points) with internal element gaps.
*/
extern void Play_Letter_S(void);

/** \fn     void Play_Letter_O(void)
    \brief  Plays the letter 'O' (3 lines) with internal element gaps.
*/
extern void Play_Letter_O(void);

#endif