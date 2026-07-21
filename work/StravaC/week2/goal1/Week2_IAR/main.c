#include "iom324pb.h"
#include "intrinsics.h"

#include "gpio.h"
#include "led.h"
#include "tc0.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

LED0 este comutat la aproximativ o secunda
folosind TC0 in Normal Mode.

Nu se folosesc software delays.
*/

/* LED0: PC7, active-low */

#define APP_LED0_DDR_REGISTER         (&DDRC)
#define APP_LED0_PORT_REGISTER        (&PORTC)
#define APP_LED0_PIN_NUMBER           (7U)

/* Private functions */

static void app_init(void);

/* Main */

void main(void)
{
    app_init();

    /*
    Pornirea timerului este ultima operatie,
    dupa configurarea modulelor.
    */

    tc0_start();

    while (GPIO_TRUE)
    {
        if (
            tc0_is_period_elapsed() ==
            TC0_PERIOD_ELAPSED
        )
        {
            tc0_clear_period_status();

            led_toggle(
                APP_LED0_PORT_REGISTER,
                APP_LED0_PIN_NUMBER
            );
        }
    }
}

/* Application initialization */

static void app_init(void)
{
    gpio_init();

    led_init(
        APP_LED0_DDR_REGISTER,
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );

    tc0_init();

    __enable_interrupt();
}