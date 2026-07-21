#include "iom324pb.h"
#include "intrinsics.h"

#include "gpio.h"
#include "led.h"
#include "tc0.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Aplicatie TC0 CTC Mode pentru exercitiile 431-439.

System clock:
fCPU = 1 MHz

Pentru semnalele 433, 436, 437 si 438:
prescaler = 1024
OCR0A = 48

Compare interval:
(48 + 1) * 1024 / 1 MHz = 50,176 ms
*/

/* ========================================================= */
/* APPLICATION MODES                                         */
/* ========================================================= */

#define APP_SIGNAL_MODE_OCR127              (0U)
#define APP_SIGNAL_MODE_100_MS              (1U)
#define APP_SIGNAL_MODE_400_MS              (2U)
#define APP_SIGNAL_MODE_1000_MS             (3U)
#define APP_SIGNAL_MODE_1200_MS             (4U)

/*
Schimba doar aceasta linie pentru obiectivul demonstrat.
*/

#define APP_SIGNAL_MODE                     \
    APP_SIGNAL_MODE_400_MS

/* ========================================================= */
/* LED0                                                      */
/* ========================================================= */

/* Main board LED0: PC7, active-low */

#define APP_LED0_DDR_REGISTER               (&DDRC)
#define APP_LED0_PORT_REGISTER              (&PORTC)
#define APP_LED0_PIN_NUMBER                 (7U)

/* ========================================================= */
/* OC0A                                                      */
/* ========================================================= */

/* OC0A = PB3 */

#define APP_OC0A_DDR_REGISTER               (&DDRB)
#define APP_OC0A_PORT_REGISTER              (&PORTB)
#define APP_OC0A_PIN_NUMBER                 (3U)

/* ========================================================= */
/* TC0 SETTINGS                                              */
/* ========================================================= */

#define APP_OCR127_TOP_VALUE                 (127U)

#define APP_50_MS_TOP_VALUE                  (48U)

#define APP_OC0A_TOGGLE_DISABLED             (0U)
#define APP_OC0A_TOGGLE_ENABLED              (1U)

/* ========================================================= */
/* SIGNAL STEPS                                              */
/* ========================================================= */

/*
Un pas dureaza aproximativ 50,176 ms.
*/

/* 100 ms: 1 pas HIGH, 1 pas LOW */

#define APP_100_MS_TOTAL_STEPS               (2U)

/* 400 ms: 4 pasi HIGH, 4 pasi LOW */

#define APP_400_MS_HIGH_STEPS                (4U)
#define APP_400_MS_TOTAL_STEPS               (8U)

/* 1000 ms: 14 pasi HIGH, 6 pasi LOW */

#define APP_1000_MS_HIGH_STEPS               (14U)
#define APP_1000_MS_TOTAL_STEPS              (20U)

/* 1200 ms pattern */

#define APP_1200_FIRST_HIGH_END              (4U)
#define APP_1200_FIRST_LOW_END               (10U)
#define APP_1200_SECOND_HIGH_END             (20U)
#define APP_1200_TOTAL_STEPS                 (24U)

#define APP_STEP_INITIAL_VALUE               (0U)

/* ========================================================= */
/* PRIVATE VARIABLES                                         */
/* ========================================================= */

static volatile unsigned char app_signal_step;

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void app_init(void);

static void app_tc0_compare_match_callback(void);

static void app_process_100_ms_signal(void);

static void app_process_400_ms_signal(void);

static void app_process_1000_ms_signal(void);

static void app_process_1200_ms_signal(void);

/* ========================================================= */
/* MAIN                                                      */
/* ========================================================= */

void main(void)
{
    app_init();

    while (GPIO_TRUE)
    {
        /*
        Semnalele sunt administrate din TC0 ISR.
        Main loop nu foloseste software delays.
        */
    }
}

/* ========================================================= */
/* INITIALIZATION                                            */
/* ========================================================= */

static void app_init(void)
{
    gpio_init();

    led_init(
        APP_LED0_DDR_REGISTER,
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );

    app_signal_step = APP_STEP_INITIAL_VALUE;

#if APP_SIGNAL_MODE == APP_SIGNAL_MODE_OCR127

    /*
    OC0A trebuie configurat ca iesire.

    Nivelul initial este HIGH pentru sincronizare cu
    LED0 active-low, care este initial oprit.
    */

    gpio_set_direction(
        APP_OC0A_DDR_REGISTER,
        APP_OC0A_PIN_NUMBER,
        GPIO_OUTPUT
    );

    gpio_set_pin(
        APP_OC0A_PORT_REGISTER,
        APP_OC0A_PIN_NUMBER
    );

    tc0_init(
        APP_OCR127_TOP_VALUE,
        APP_OC0A_TOGGLE_ENABLED,
        app_tc0_compare_match_callback
    );

#else

    /*
    Pentru semnalele 100, 400, 1000 si 1200 ms,
    semnalul este aplicat pe LED0.
    */

    tc0_init(
        APP_50_MS_TOP_VALUE,
        APP_OC0A_TOGGLE_DISABLED,
        app_tc0_compare_match_callback
    );

#endif

    __enable_interrupt();

#if APP_SIGNAL_MODE == APP_SIGNAL_MODE_OCR127

    /*
    OCR0A = 127 si prescaler 1024:
    match la fiecare 131,072 ms.
    */

    tc0_start_prescaler_1024();

#else

    /*
    OCR0A = 48 si prescaler 1024:
    match la fiecare 50,176 ms.
    */

    tc0_start_prescaler_1024();

#endif
}

/* ========================================================= */
/* TIMER CALLBACK                                            */
/* ========================================================= */

static void app_tc0_compare_match_callback(void)
{
#if APP_SIGNAL_MODE == APP_SIGNAL_MODE_OCR127

    /*
    PB3 / OC0A este comutat automat de hardware.

    LED0 este comutat din ISR.
    Initializarea ambelor iesiri cu HIGH le face
    sincronizate vizual.
    */

    led_toggle(
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );

#elif APP_SIGNAL_MODE == APP_SIGNAL_MODE_100_MS

    app_process_100_ms_signal();

#elif APP_SIGNAL_MODE == APP_SIGNAL_MODE_400_MS

    app_process_400_ms_signal();

#elif APP_SIGNAL_MODE == APP_SIGNAL_MODE_1000_MS

    app_process_1000_ms_signal();

#elif APP_SIGNAL_MODE == APP_SIGNAL_MODE_1200_MS

    app_process_1200_ms_signal();

#endif
}

/* ========================================================= */
/* 100 MS SIGNAL                                             */
/* ========================================================= */

static void app_process_100_ms_signal(void)
{
    led_toggle(
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );
}

/* ========================================================= */
/* 400 MS SIGNAL - 50% HIGH, 50% LOW                         */
/* ========================================================= */

static void app_process_400_ms_signal(void)
{
    app_signal_step++;

    if (app_signal_step == APP_400_MS_HIGH_STEPS)
    {
        led_power_off(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
    else if (
        app_signal_step >= APP_400_MS_TOTAL_STEPS
    )
    {
        app_signal_step = APP_STEP_INITIAL_VALUE;

        led_power_on(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
}

/* ========================================================= */
/* 1000 MS SIGNAL - 70% HIGH, 30% LOW                        */
/* ========================================================= */

static void app_process_1000_ms_signal(void)
{
    app_signal_step++;

    if (app_signal_step == APP_1000_MS_HIGH_STEPS)
    {
        led_power_off(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
    else if (
        app_signal_step >= APP_1000_MS_TOTAL_STEPS
    )
    {
        app_signal_step = APP_STEP_INITIAL_VALUE;

        led_power_on(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
}

/* ========================================================= */
/* 1200 MS CUSTOM SIGNAL                                     */
/* ========================================================= */

static void app_process_1200_ms_signal(void)
{
    app_signal_step++;

    if (
        app_signal_step ==
        APP_1200_FIRST_HIGH_END
    )
    {
        /*
        Dupa aproximativ 200 ms:
        HIGH -> LOW.
        */

        led_power_off(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
    else if (
        app_signal_step ==
        APP_1200_FIRST_LOW_END
    )
    {
        /*
        Dupa alte aproximativ 300 ms:
        LOW -> HIGH.
        */

        led_power_on(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
    else if (
        app_signal_step ==
        APP_1200_SECOND_HIGH_END
    )
    {
        /*
        Dupa alte aproximativ 500 ms:
        HIGH -> LOW.
        */

        led_power_off(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
    else if (
        app_signal_step >=
        APP_1200_TOTAL_STEPS
    )
    {
        /*
        Dupa ultimele aproximativ 200 ms,
        ciclul este reluat.
        */

        app_signal_step = APP_STEP_INITIAL_VALUE;

        led_power_on(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );
    }
}