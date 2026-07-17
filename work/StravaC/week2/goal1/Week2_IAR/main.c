#include "iom324pb.h"
#include "intrinsics.h"

#include "gpio.h"
#include "led.h"
#include "adc.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Aplicatie pentru citirea senzorului de lumina TEMT6000.

IO1 Xplained Pro este conectat la EXT4.
Semnalul senzorului ajunge la PA4 / ADC4.

ADC-ul realizeaza conversii pe 8 biti folosind intreruperi.
Valoarea obtinuta este folosita pentru controlul LED0.
*/

/* ========================================================= */
/* LED0 CONNECTION                                           */
/* ========================================================= */

#define APP_LED0_DDR_REGISTER             (&DDRC)
#define APP_LED0_PORT_REGISTER            (&PORTC)
#define APP_LED0_PIN_NUMBER               (7U)

/* ========================================================= */
/* LIGHT CONTROL CONFIGURATION                               */
/* ========================================================= */

/*
Prag initial pentru rezultatul ADC pe 8 biti.

Valoarea poate fi ajustata experimental dupa observarea
rezultatelor obtinute in lumina si intuneric.
*/

#define APP_LIGHT_THRESHOLD               (128U)

/* ========================================================= */
/* APPLICATION INITIAL VALUES                                */
/* ========================================================= */

#define APP_LIGHT_VALUE_INITIAL           (0U)

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void app_init(void);

static void app_process_light_value(
    adc_uint8_t app_light_value
);

/* ========================================================= */
/* MAIN                                                      */
/* ========================================================= */

void main(void)
{
    adc_uint8_t app_light_value;

    app_light_value = APP_LIGHT_VALUE_INITIAL;

    app_init();

    /*
    Pornirea primei conversii este ultima operatie,
    dupa configurarea completa a modulelor.
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
            Porneste urmatoarea conversie.
            ADC-ul ramane in Single Conversion Mode.
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
    Initializeaza modulele in ordinea dependentelor:
    GPIO -> LED -> ADC.
    */

    gpio_init();

    led_init(
        APP_LED0_DDR_REGISTER,
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );

    adc_init();

    /*
    Intreruperile globale sunt activate dupa ce toate
    modulele sunt configurate.
    */

    __enable_interrupt();
}

/* ========================================================= */
/* APPLICATION BEHAVIOR                                      */
/* ========================================================= */

static void app_process_light_value(
    adc_uint8_t app_light_value
)
{
    if (app_light_value >= APP_LIGHT_THRESHOLD)
    {
        led_power_on(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
    else
    {
        led_power_off(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
}