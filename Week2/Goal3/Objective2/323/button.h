#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define BUTTON_SW0_DDR     (&DDRC)
#define BUTTON_SW0_PORT    (&PORTC)
#define BUTTON_SW0_PINR    (&PINC)
#define BUTTON_SW0_PIN     6

#define BUTTON_DEBOUNCE_THRESHOLD 500

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void button_init(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Initializes a target hardware pin as an input and enables its internal pull-up resistor.
*/
void button_init(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf)
    \brief  Reads a targeted pin status dynamically using distinct tracking confidence thresholds.
    \return 1 if a stable press condition is verified, 0 otherwise.
*/
unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf);

#endif