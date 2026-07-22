#ifndef AMBIENT_H
#define AMBIENT_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Initialize the ambient light application: LED0..LED3 as outputs,
            all turned off (initial state) */
extern void ambient_init(void);

/** \brief  Turn LED0 on when the light reading is above the midpoint of the range.
    \param[in]  light  last 8-bit ADC reading (0 .. 255)
    \details    On this board the value is inverted (high value = dark) -> LED0 acts as a night light.
*/
extern void ambient_indicate_threshold(unsigned char light);

/** \brief  Show the light level as a bar-graph on LED1, LED2, LED3.
    \param[in]  light  last 8-bit ADC reading (0 .. 255)
    \details    The range is split in 4 intervals: full light -> 3 LEDs on,
                full dark -> all off. Value is inverted on this board (low = bright),
                so a lower reading lights up more LEDs.
*/
extern void ambient_indicate_level(unsigned char light);

#endif
