#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  LED0 is connected to pin PC7 */
#define LED0_PIN            (7U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void led_init(void)
    \brief      Initialize the LED pin as output
    \return     void
*/
extern void led_init(void);

/** \fn     void led_power_on(void)
    \brief      Turn LED0 ON (active low: writes 0 via the gpio module)
    \return     void
*/
extern void led_power_on(void);

/** \fn     void led_power_off(void)
    \brief      Turn LED0 OFF (active low: writes 1 via the gpio module)
    \return     void
*/
extern void led_power_off(void);

#endif
