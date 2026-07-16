#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define INPUT  0
#define OUTPUT 1

/** \brief  parameter type unsigned byte (8 bit) */
typedef     unsigned char   mod_uint8_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void set_pin(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Sets a specific pin on a selected port register to 1.  
*/
extern void set_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void reset_pin(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Resets a specific pin on a selected port register to 0.  
*/
extern void reset_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction)
    \brief  Configures the direction of a pin using the target register.  
*/
extern void set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction);

/** \fn     void toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Inverts the current logical state of a target pin.  
*/
extern void toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number);

#endif