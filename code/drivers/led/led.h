#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  LED identifier type */
typedef enum {
    // ATmega328P onboard LED
    LED_ONBOARD = 0,

    // OLED1 LEDs
    LED_OLED1_1,
    LED_OLED1_2,
    LED_OLED1_3,

    // IO1 LED
    LED_IO1,

    LED_COUNT // Total number of LEDs
}led_id_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \fn     void led_init(void)

    \brief      [ Initializes the LED module. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
*/
extern void led_init(void);

/** \fn     void led_power_on(led_id_t led_id)

    \brief      [ Turns on the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
*/
extern void led_power_on(led_id_t led_id);

/** \fn     void led_power_off(led_id_t led_id)

    \brief      [ Turns off the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
*/
extern void led_power_off(led_id_t led_id);

/** \fn     void led_toggle(led_id_t led_id)

    \brief      [ Toggles the state of the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
*/
extern void led_toggle(led_id_t led_id);

#endif /* LED_H */