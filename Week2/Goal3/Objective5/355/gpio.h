#ifndef GPIO_H
#define GPIO_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

/** \brief  parameter type unsigned byte (8 bit) */
typedef     unsigned char   mod_uint8_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void gpio_init(void)
    \brief  Initializes the general-purpose input/output peripheral module.
*/
void gpio_init(void);

/** \fn     void gpio_set_pin(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Sets a specific pin on a selected port register to 1.  
*/
extern void gpio_set_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void gpio_reset_pin(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Resets a specific pin on a selected port register to 0.  
*/
extern void gpio_reset_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void gpio_set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction)
    \brief  Configures the direction of a pin using the target register.  
*/
extern void gpio_set_direction(volatile unsigned char *port_reg, unsigned char pin_number, unsigned char direction);

/** \fn     void gpio_toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Inverts the current logical state of a target pin.  
*/
extern void gpio_toggle_pin(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     unsigned char gpio_read_pin(volatile unsigned char *pin_reg, unsigned char pin_number)
    \brief  Reads the logical value of a specific pin from a PINx register.
    \return 1 if the pin is HIGH, 0 if the pin is LOW.
*/
extern unsigned char gpio_read_pin(volatile unsigned char *pin_reg, unsigned char pin_number);

#endif