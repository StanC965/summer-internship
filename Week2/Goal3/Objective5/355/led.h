#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define LED_LED0_PORT       (&PORTC)
#define LED_LED0_DDR        (&DDRC)
#define LED_LED0_PIN        7

#define LED_TIME_BLINK_FAST      60000UL
#define LED_TIME_BLINK_SLOW      175000UL

#define LED_OLED_1_2_DDR        (&DDRD)
#define LED_OLED_1_2_PORT       (&PORTD)
#define LED_OLED_1_PIN          5       
#define LED_OLED_2_PIN          4             

#define LED_OLED_3_DDR          (&DDRA)
#define LED_OLED_3_PORT         (&PORTA)
#define LED_OLED_3_PIN          3       

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void led_init(void)
    \brief  Initializes the LED module by configuring pin directions and forcing all outputs to default OFF.
*/
void led_init(void);

/** \fn     void led_configure_pin(volatile unsigned char *ddr_reg, unsigned char pin_number)
    \brief  Configures a single target MCU pin to function as an LED output.
*/
void led_configure_pin(volatile unsigned char *ddr_reg, unsigned char pin_number);

/** \fn     void led_power_on(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Turns an active-low LED ON by driving its pin to 0.
*/
extern void led_power_on(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void led_power_off(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Turns an active-low LED OFF by driving its pin to 1.
*/
extern void led_power_off(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void led_toggle(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Inverts the current logical state of a targeted LED pin.
*/
extern void led_toggle(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void led_blink_fast(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Blinks the LED repetitively with 6-ons and 6-offs per second.
*/
extern void led_blink_fast(volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     void led_blink_slow(volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Blinks the LED repetitively with 2-ons and 2-offs per second.
*/
extern void led_blink_slow(volatile unsigned char *port_reg, unsigned char pin_number);

#endif
