#include "iom324pb.h"

#include "gpio.h"
#include "led.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine punctul principal al aplicatiei.

OLED1 Xplained Pro este conectat la header-ul EXT1.

Comportamentul aplicatiei:
- BUTTON1 apasat  -> LED1 aprins
- BUTTON1 eliberat -> LED1 stins
- BUTTON2 apasat  -> LED2 aprins
- BUTTON2 eliberat -> LED2 stins
- BUTTON3 apasat  -> LED3 aprins
- BUTTON3 eliberat -> LED3 stins

Butoanele si LED-urile de pe extensie sunt active-low.
*/

/* BUTTON1: EXT1 pin 9 -> PC1 */

#define APP_BUTTON1_PIN_REGISTER       (&PINC)
#define APP_BUTTON1_PORT_REGISTER      (&PORTC)
#define APP_BUTTON1_DDR_REGISTER       (&DDRC)
#define APP_BUTTON1_PIN_NUMBER         (1U)

/* BUTTON2: EXT1 pin 3 -> PA0 */

#define APP_BUTTON2_PIN_REGISTER       (&PINA)
#define APP_BUTTON2_PORT_REGISTER      (&PORTA)
#define APP_BUTTON2_DDR_REGISTER       (&DDRA)
#define APP_BUTTON2_PIN_NUMBER         (0U)

/* BUTTON3: EXT1 pin 4 -> PA1 */

#define APP_BUTTON3_PIN_REGISTER       (&PINA)
#define APP_BUTTON3_PORT_REGISTER      (&PORTA)
#define APP_BUTTON3_DDR_REGISTER       (&DDRA)
#define APP_BUTTON3_PIN_NUMBER         (1U)

/* LED1: EXT1 pin 7 -> PD5 */

#define APP_LED1_PORT_REGISTER         (&PORTD)
#define APP_LED1_DDR_REGISTER          (&DDRD)
#define APP_LED1_PIN_NUMBER            (5U)

/* LED2: EXT1 pin 8 -> PD4 */

#define APP_LED2_PORT_REGISTER         (&PORTD)
#define APP_LED2_DDR_REGISTER          (&DDRD)
#define APP_LED2_PIN_NUMBER            (4U)

/* LED3: EXT1 pin 6 -> PA3 */

#define APP_LED3_PORT_REGISTER         (&PORTA)
#define APP_LED3_DDR_REGISTER          (&DDRA)
#define APP_LED3_PIN_NUMBER            (3U)

/* Button logic */

#define APP_BUTTON_PRESSED_LEVEL       (GPIO_LOW)

/* Static private functions declaration */

static void app_initialize_hardware(void);

static void app_update_led_from_button(
    volatile gpio_uint8_t *app_button_pin_register,
    gpio_uint8_t app_button_pin_number,
    volatile gpio_uint8_t *app_led_port_register,
    gpio_uint8_t app_led_pin_number
);

/* Main function */

void main(void)
{
    app_initialize_hardware();

    while (GPIO_TRUE)
    {
        app_update_led_from_button(
            APP_BUTTON1_PIN_REGISTER,
            APP_BUTTON1_PIN_NUMBER,
            APP_LED1_PORT_REGISTER,
            APP_LED1_PIN_NUMBER
        );

        app_update_led_from_button(
            APP_BUTTON2_PIN_REGISTER,
            APP_BUTTON2_PIN_NUMBER,
            APP_LED2_PORT_REGISTER,
            APP_LED2_PIN_NUMBER
        );

        app_update_led_from_button(
            APP_BUTTON3_PIN_REGISTER,
            APP_BUTTON3_PIN_NUMBER,
            APP_LED3_PORT_REGISTER,
            APP_LED3_PIN_NUMBER
        );
    }
}

/* Static private functions implementation */

static void app_initialize_hardware(void)
{
    /*
    Configureaza cele trei butoane ca intrari.
    */

    gpio_set_direction(
        APP_BUTTON1_DDR_REGISTER,
        APP_BUTTON1_PIN_NUMBER,
        GPIO_INPUT
    );

    gpio_set_direction(
        APP_BUTTON2_DDR_REGISTER,
        APP_BUTTON2_PIN_NUMBER,
        GPIO_INPUT
    );

    gpio_set_direction(
        APP_BUTTON3_DDR_REGISTER,
        APP_BUTTON3_PIN_NUMBER,
        GPIO_INPUT
    );

    /*
    Extensia OLED1 nu contine rezistente pull-up externe.
    Sunt activate rezistentele pull-up interne.
    */

    gpio_activate_pullup(
        APP_BUTTON1_PORT_REGISTER,
        APP_BUTTON1_PIN_NUMBER
    );

    gpio_activate_pullup(
        APP_BUTTON2_PORT_REGISTER,
        APP_BUTTON2_PIN_NUMBER
    );

    gpio_activate_pullup(
        APP_BUTTON3_PORT_REGISTER,
        APP_BUTTON3_PIN_NUMBER
    );

    /*
    Configureaza cele trei LED-uri ca iesiri.
    */

    gpio_set_direction(
        APP_LED1_DDR_REGISTER,
        APP_LED1_PIN_NUMBER,
        GPIO_OUTPUT
    );

    gpio_set_direction(
        APP_LED2_DDR_REGISTER,
        APP_LED2_PIN_NUMBER,
        GPIO_OUTPUT
    );

    gpio_set_direction(
        APP_LED3_DDR_REGISTER,
        APP_LED3_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /*
    LED-urile sunt active-low.
    Initial sunt stinse.
    */

    led_power_off(
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    led_power_off(
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    led_power_off(
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );
}

static void app_update_led_from_button(
    volatile gpio_uint8_t *app_button_pin_register,
    gpio_uint8_t app_button_pin_number,
    volatile gpio_uint8_t *app_led_port_register,
    gpio_uint8_t app_led_pin_number
)
{
    gpio_uint8_t app_button_state;

    app_button_state = gpio_read_pin(
        app_button_pin_register,
        app_button_pin_number
    );

    if (app_button_state == APP_BUTTON_PRESSED_LEVEL)
    {
        led_power_on(
            app_led_port_register,
            app_led_pin_number
        );
    }
    else
    {
        led_power_off(
            app_led_port_register,
            app_led_pin_number
        );
    }
}