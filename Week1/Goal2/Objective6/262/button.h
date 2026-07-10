#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define SW0_DDR     (&DDRC)
#define SW0_PORT    (&PORTC)
#define SW0_PINR    (&PINC)
#define SW0_PIN     6

#define DEBOUNCE_THRESHOLD 500

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void Init_Button(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Initializes a target hardware pin as an input and enables its internal pull-up resistor.
*/
void Init_Button(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     unsigned char Is_Button_Pressed(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf)
    \brief  Reads a targeted pin status dynamically using distinct tracking confidence thresholds.
    \return 1 if a stable press condition is verified, 0 otherwise.
*/
unsigned char Is_Button_Pressed(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf);

#endif