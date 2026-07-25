#include "iom324pb.h"
#include "intrinsics.h"

#include "gpio.h"
#include "led.h"
#include "adc.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Aplicatie pentru afisarea intensitatii luminii ambientale
folosind cele trei LED-uri de pe OLED1 Xplained Pro.

Conexiuni:
- IO1 Xplained Pro este conectat la EXT4;
- senzorul TEMT6000 ajunge la PA4 / ADC4;
- OLED1 Xplained Pro este conectat la EXT1.

Domeniul ADC pe 8 biti este impartit in patru intervale:

1. Full dark:
   toate LED-urile sunt stinse.

2. Semi-dark:
   LED1 este aprins.

3. Semi-light:
   LED1 si LED2 sunt aprinse.

4. Full light:
   LED1, LED2 si LED3 sunt aprinse.
*/

/* ========================================================= */
/* OLED1 LED CONNECTIONS - EXT1                              */
/* ========================================================= */

/* LED1: EXT1 pin 7 -> PD5 */

#define APP_LED1_DDR_REGISTER             (&DDRD)
#define APP_LED1_PORT_REGISTER            (&PORTD)
#define APP_LED1_PIN_NUMBER               (5U)

/* LED2: EXT1 pin 8 -> PD4 */

#define APP_LED2_DDR_REGISTER             (&DDRD)
#define APP_LED2_PORT_REGISTER            (&PORTD)
#define APP_LED2_PIN_NUMBER               (4U)

/* LED3: EXT1 pin 6 -> PA3 */

#define APP_LED3_DDR_REGISTER             (&DDRA)
#define APP_LED3_PORT_REGISTER            (&PORTA)
#define APP_LED3_PIN_NUMBER               (3U)

/* ========================================================= */
/* ADC RANGE                                                 */
/* ========================================================= */

#define APP_ADC_MINIMUM_VALUE             (0U)
#define APP_ADC_MAXIMUM_VALUE             (255U)

/*
Cele patru intervale initiale sunt:

0 ... 63
64 ... 127
128 ... 191
192 ... 255
*/

#define APP_FULL_DARK_UPPER_LIMIT          (63U)
#define APP_SEMI_DARK_UPPER_LIMIT          (127U)
#define APP_SEMI_LIGHT_UPPER_LIMIT         (191U)

/* ========================================================= */
/* APPLICATION INITIAL VALUES                                */
/* ========================================================= */

#define APP_LIGHT_VALUE_INITIAL            (APP_ADC_MINIMUM_VALUE)

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void app_init(void);

static void app_process_light_value(
    adc_uint8_t app_light_value
);

static void app_set_full_dark_led_state(void);

static void app_set_semi_dark_led_state(void);

static void app_set_semi_light_led_state(void);

static void app_set_full_light_led_state(void);

/* ========================================================= */
/* MAIN FUNCTION                                             */
/* ========================================================= */

void main(void)
{
    adc_uint8_t app_light_value;

    app_light_value = APP_LIGHT_VALUE_INITIAL;

    app_init();

    /*
    Prima conversie este pornita doar dupa ce toate
    modulele au fost initializate.
    */

    adc_start_conversion();

    while (GPIO_TRUE)
    {
        if (adc_is_result_ready() == ADC_RESULT_READY)
        {
            app_light_value = adc_get_result();

            app_process_light_value(
                app_light_value
            );

            /*
            ADC-ul functioneaza in Single Conversion Mode.
            Urmatoarea conversie este pornita manual.
            */

            adc_start_conversion();
        }
    }
}

/* ========================================================= */
/* APPLICATION INITIALIZATION                                */
/* ========================================================= */

static void app_init(void)
{
    /*
    Modulele sunt initializate in ordinea dependentelor:
    GPIO -> LED -> ADC.
    */

    gpio_init();

    led_init(
        APP_LED1_DDR_REGISTER,
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    led_init(
        APP_LED2_DDR_REGISTER,
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    led_init(
        APP_LED3_DDR_REGISTER,
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );

    adc_init();

    /*
    Intreruperile globale sunt activate dupa configurarea
    completa a tuturor modulelor.
    */

    __enable_interrupt();
}

/* ========================================================= */
/* LIGHT LEVEL PROCESSING                                    */
/* ========================================================= */

static void app_process_light_value(
    adc_uint8_t app_light_value
)
{
    if (app_light_value <= APP_FULL_DARK_UPPER_LIMIT)
    {
        app_set_full_dark_led_state();
    }
    else if (app_light_value <= APP_SEMI_DARK_UPPER_LIMIT)
    {
        app_set_semi_dark_led_state();
    }
    else if (app_light_value <= APP_SEMI_LIGHT_UPPER_LIMIT)
    {
        app_set_semi_light_led_state();
    }
    else
    {
        app_set_full_light_led_state();
    }
}

/* ========================================================= */
/* LED STATE FUNCTIONS                                       */
/* ========================================================= */

static void app_set_full_dark_led_state(void)
{
    /*
    Intervalul 1:
    full dark -> toate LED-urile sunt stinse.
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

static void app_set_semi_dark_led_state(void)
{
    /*
    Intervalul 2:
    semi-dark -> doar LED1 este aprins.
    */

    led_power_on(
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

static void app_set_semi_light_led_state(void)
{
    /*
    Intervalul 3:
    semi-light -> LED1 si LED2 sunt aprinse.
    */

    led_power_on(
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    led_power_on(
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    led_power_off(
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );
}

static void app_set_full_light_led_state(void)
{
    /*
    Intervalul 4:
    full light -> toate LED-urile sunt aprinse.
    */

    led_power_on(
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    led_power_on(
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    led_power_on(
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );
}