#ifndef LED_H
#define LED_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  LED0 on the main board: PC7 */
#define LED0_DDR            (&DDRC)
#define LED0_PORT           (&PORTC)
#define LED0_PIN            (7U)

/** \brief  LED1 on OLED1 (EXT1): PD5 */
#define LED1_DDR            (&DDRD)
#define LED1_PORT           (&PORTD)
#define LED1_PIN            (5U)

/** \brief  LED2 on OLED1 (EXT1): PD4 */
#define LED2_DDR            (&DDRD)
#define LED2_PORT           (&PORTD)
#define LED2_PIN            (4U)

/** \brief  LED3 on OLED1 (EXT1): PA3 */
#define LED3_DDR            (&DDRA)
#define LED3_PORT           (&PORTA)
#define LED3_PIN            (3U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Initialize a LED pin as output
    \param[in]  ddr  pointer to the DDRx register of the LED
    \param[in]  pin  pin number of the LED
*/
extern void led_init(gpio_reg_t ddr, unsigned char pin);

/** \brief  Turn a LED ON (all the LEDs are active low)
    \param[in]  port  pointer to the PORTx register of the LED
    \param[in]  pin   pin number of the LED
*/
extern void led_power_on(gpio_reg_t port, unsigned char pin);

/** \brief  Turn a LED OFF
    \param[in]  port  pointer to the PORTx register of the LED
    \param[in]  pin   pin number of the LED
*/
extern void led_power_off(gpio_reg_t port, unsigned char pin);

/** \brief  Toggle a LED */
extern void led_toggle(gpio_reg_t port, unsigned char pin);

/** \brief  Blink a LED fast: 6 on-and-off cycles per second */
extern void led_blink_fast(gpio_reg_t port, unsigned char pin);

/** \brief  Blink a LED slow: 2 on-and-off cycles per second */
extern void led_blink_slow(gpio_reg_t port, unsigned char pin);

#endif
