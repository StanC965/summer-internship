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

/** \brief  Initialize the LED pin as output */
extern void led_init(void);

/** \brief  Turn LED0 ON (active low) */
extern void led_power_on(void);

/** \brief  Turn LED0 OFF (active low) */
extern void led_power_off(void);

/** \brief  Blink LED0 fast: 6 on-and-off cycles per second */
extern void led_blink_fast(void);

/** \brief  Blink LED0 slow: 2 on-and-off cycles per second */
extern void led_blink_slow(void);

#endif
