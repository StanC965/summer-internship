#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define LED0_PORT       (&PORTC)
#define LED0_DDR        (&DDRC)
#define LED0_PIN        7

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void Init_LED(volatile unsigned char *ddr_reg, unsigned char pin_number)
    \brief  Initializes an LED pin by setting its direction to OUTPUT.
*/
extern void Init_LED(volatile unsigned char *ddr_reg, unsigned char pin_number);

/** \fn     void PowerOn_LED(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Turns an active-low LED ON by driving its pin to 0.
*/
extern void PowerOn_LED(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void PowerOff_LED(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Turns an active-low LED OFF by driving its pin to 1.
*/
extern void PowerOff_LED(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void Toggle_LED(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Inverts the current logical state of a targeted LED pin.
*/
extern void Toggle_LED(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void BlinkFast_LED(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Blinks the LED repetitively with 6-ons and 6-offs per second.
*/
extern void BlinkFast_LED(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void BlinkSlow_LED(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Blinks the LED repetitively with 2-ons and 2-offs per second.
*/
extern void BlinkSlow_LED(volatile unsigned char *port_reg, unsigned char pin_number);

#endif