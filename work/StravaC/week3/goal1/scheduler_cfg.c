#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

#include "iom324pb.h"

#include "adc.h"
#include "gpio.h"
#include "led.h"
#include "scheduler_cfg.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Configuratia taskurilor pentru Ambient Light Application.

Task 100 ms:
- porneste o conversie ADC.

Task 10 ms:
- verifica rezultatul ADC;
- citeste rezultatul prin adc_get_data();
- actualizeaza cele trei LED-uri.
*/

/* ========================================================= */
/* OLED1 LED CONNECTIONS                                     */
/* ========================================================= */

/* LED1: PD5 */

#define SCHEDULER_CFG_LED1_DDR_REGISTER       (&DDRD)
#define SCHEDULER_CFG_LED1_PORT_REGISTER      (&PORTD)
#define SCHEDULER_CFG_LED1_PIN_NUMBER         (5U)

/* LED2: PD4 */

#define SCHEDULER_CFG_LED2_DDR_REGISTER       (&DDRD)
#define SCHEDULER_CFG_LED2_PORT_REGISTER      (&PORTD)
#define SCHEDULER_CFG_LED2_PIN_NUMBER         (4U)

/* LED3: PA3 */

#define SCHEDULER_CFG_LED3_DDR_REGISTER       (&DDRA)
#define SCHEDULER_CFG_LED3_PORT_REGISTER      (&PORTA)
#define SCHEDULER_CFG_LED3_PIN_NUMBER         (3U)

/* ========================================================= */
/* AMBIENT LIGHT INTERVALS                                   */
/* ========================================================= */

/*
8-bit ADC range:

0 ... 63     -> full dark
64 ... 127   -> semi-dark
128 ... 191  -> semi-light
192 ... 255  -> full light
*/

#define SCHEDULER_CFG_FULL_DARK_UPPER_LIMIT   (63U)
#define SCHEDULER_CFG_SEMI_DARK_UPPER_LIMIT   (127U)
#define SCHEDULER_CFG_SEMI_LIGHT_UPPER_LIMIT  (191U)

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void scheduler_cfg_process_light_data(
    adc_uint8_t scheduler_cfg_light_data
);

static void scheduler_cfg_set_full_dark(void);

static void scheduler_cfg_set_semi_dark(void);

static void scheduler_cfg_set_semi_light(void);

static void scheduler_cfg_set_full_light(void);

/* ========================================================= */
/* MODULE INITIALIZATION                                     */
/* ========================================================= */

void scheduler_cfg_init(void)
{
    gpio_init();

    led_init(
        SCHEDULER_CFG_LED1_DDR_REGISTER,
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_init(
        SCHEDULER_CFG_LED2_DDR_REGISTER,
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_init(
        SCHEDULER_CFG_LED3_DDR_REGISTER,
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );

    adc_init();
}

/* ========================================================= */
/* 10 MS TASK                                                */
/* ========================================================= */

void scheduler_task_10ms(void)
{
    adc_uint8_t scheduler_cfg_light_data;

    /*
    The task does not directly access ADC module data.

    The result is obtained only through the public
    adc_get_data() interface.
    */

    if (
        adc_is_data_ready() ==
        ADC_DATA_READY
    )
    {
        scheduler_cfg_light_data =
            adc_get_data();

        scheduler_cfg_process_light_data(
            scheduler_cfg_light_data
        );
    }
}

/* ========================================================= */
/* 50 MS TASK                                                */
/* ========================================================= */

void scheduler_task_50ms(void)
{
    /*
    Not used by the current application.
    */
}

/* ========================================================= */
/* 100 MS TASK                                               */
/* ========================================================= */

void scheduler_task_100ms(void)
{
    /*
    Start one ambient light conversion every 100 ms.

    adc_start_conversion() also protects against starting
    another conversion while the ADC is busy.
    */

    adc_start_conversion();
}

/* ========================================================= */
/* 500 MS TASK                                               */
/* ========================================================= */

void scheduler_task_500ms(void)
{
    /*
    Not used by the current application.
    */
}

/* ========================================================= */
/* 1000 MS TASK                                              */
/* ========================================================= */

void scheduler_task_1000ms(void)
{
    /*
    Not used by the current application.
    */
}

/* ========================================================= */
/* LIGHT DATA PROCESSING                                     */
/* ========================================================= */

static void scheduler_cfg_process_light_data(
    adc_uint8_t scheduler_cfg_light_data
)
{
    if (
        scheduler_cfg_light_data <=
        SCHEDULER_CFG_FULL_DARK_UPPER_LIMIT
    )
    {
        scheduler_cfg_set_full_dark();
    }
    else if (
        scheduler_cfg_light_data <=
        SCHEDULER_CFG_SEMI_DARK_UPPER_LIMIT
    )
    {
        scheduler_cfg_set_semi_dark();
    }
    else if (
        scheduler_cfg_light_data <=
        SCHEDULER_CFG_SEMI_LIGHT_UPPER_LIMIT
    )
    {
        scheduler_cfg_set_semi_light();
    }
    else
    {
        scheduler_cfg_set_full_light();
    }
}

/* ========================================================= */
/* LED STATES                                                */
/* ========================================================= */

static void scheduler_cfg_set_full_dark(void)
{
    led_power_off(
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );
}

static void scheduler_cfg_set_semi_dark(void)
{
    led_power_on(
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );
}

static void scheduler_cfg_set_semi_light(void)
{
    led_power_on(
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_power_on(
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );
}

static void scheduler_cfg_set_full_light(void)
{
    led_power_on(
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_power_on(
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_power_on(
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );
}

#endif