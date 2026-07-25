#ifndef SOS_H
#define SOS_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Signal one Morse point on the given LED (short light) */
extern void sos_point(gpio_reg_t port, unsigned char pin);

/** \brief  Signal one Morse line on the given LED (long light, 3x a point) */
extern void sos_line(gpio_reg_t port, unsigned char pin);

/** \brief  Signal the complete SOS sequence: 3 points, 3 lines, 3 points */
extern void sos_signal(gpio_reg_t port, unsigned char pin);

/** \brief  Pause of 1 second between two SOS sequences */
extern void sos_pause(void);

#endif
