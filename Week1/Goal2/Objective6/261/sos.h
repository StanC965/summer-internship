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

#endif