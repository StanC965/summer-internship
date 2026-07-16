#ifndef LED_H
#define LED_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific constant number zero */
#define LED_ONBOARD_PIN             7

/** \brief  Module specific constant number one */
#define LED_OLED1_1_PIN             5

/** \brief  Module specific constant number four */
#define LED_OLED1_2_PIN             4

/** \brief  Module specific constant number five */
#define LED_OLED1_3_PIN             3

/** \brief  Module specific constant number six */
#define LED_IO1_PIN                 3

/** \brief  LED configuration structure */
typedef struct
{
    volatile uint8_t *ddr_register;
    volatile uint8_t *port_register;
    uint8_t pin;
} led_config_t;

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
    \details    [ This function initializes the LED module by setting 
                 the pins in the port registers and configuring
                 the corresponding data direction registers as outputs. ]
*/
extern void led_init(void);

/** \fn     void led_power_on(led_id_t led_id)

    \brief      [ Turns on the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function powers on the LED by setting 
                 the corresponding bit in the port register. ]
*/
extern void led_power_on(led_id_t led_id);

/** \fn     void led_power_off(led_id_t led_id)

    \brief      [ Turns off the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function powers off the LED by clearing 
                 the corresponding bit in the port register. ]
*/
extern void led_power_off(led_id_t led_id);

/** \fn     void led_toggle(led_id_t led_id)

    \brief      [ Toggles the state of the specified LED. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function toggles the state of the LED by 
                 flipping the corresponding bit in the port register. ]
*/
extern void led_toggle(led_id_t led_id);

/** \fn     void led_blink_fast(led_id_t led_id)

    \brief      [ Blinks the specified LED quickly. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function turns the LED on and off repetitively
                 with 6-ons and 6-offs per second. ]
*/
extern void led_blink_fast(led_id_t led_id);

/** \fn     void led_blink_slow(led_id_t led_id)

    \brief      [ Blinks the specified LED slowly. ]
    \param[in]  led_id [ the LED identifier ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function turns the LED on and off repetitively
                 with 2-ons and 2-offs per second.]
*/
extern void led_blink_slow(led_id_t led_id);

/** \fn     void led_blink_custom(led_id_t led_id, uint8_t count, uint32_t on_time, uint32_t off_time)

    \brief      [ Blinks the specified LED with custom timing. ]
    \param[in]  led_id [ the LED identifier ]
    \param[in]  count [ the number of blinks ]
    \param[in]  on_time [ the duration the LED is on (in milliseconds) ]
    \param[in]  off_time [ the duration the LED is off (in milliseconds) ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ This function turns the LED on and off repetitively with custom timing. ]
*/
extern void led_blink_custom(led_id_t led_id, uint8_t count, uint32_t on_time, uint32_t off_time);

#endif /* LED_H */