#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

#include "iom324pb.h"

#include "gpio.h"
#include "led.h"
#include "scheduler_cfg.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Configuratia taskurilor schedulerului.

Acest modul contine functionalitatea concreta
executata pentru fiecare perioada.

Schedulerul generic nu trebuie modificat atunci cand
functionalitatea taskurilor este schimbata.
*/

/* ========================================================= */
/* LED0                                                      */
/* ========================================================= */

/*
Main board LED0:
PC7, active-low.
*/

#define SCHEDULER_CFG_LED0_DDR_REGISTER      (&DDRC)
#define SCHEDULER_CFG_LED0_PORT_REGISTER     (&PORTC)
#define SCHEDULER_CFG_LED0_PIN_NUMBER        (7U)

/* ========================================================= */
/* TASKS INITIALIZATION                                      */
/* ========================================================= */

/*
Aceasta functie este specifica aplicatiei.
Poate fi declarata separat daca dorim sa initializam
perifericele folosite de taskuri.
*/

void scheduler_cfg_init(void)
{
    gpio_init();

    led_init(
        SCHEDULER_CFG_LED0_DDR_REGISTER,
        SCHEDULER_CFG_LED0_PORT_REGISTER,
        SCHEDULER_CFG_LED0_PIN_NUMBER
    );
}

/* ========================================================= */
/* REQUIRED INTERFACES                                       */
/* ========================================================= */

void scheduler_task_10ms(void)
{
    /*
    Functionalitate viitoare:
    procesare rapida sau citire intrari.
    */
}

void scheduler_task_50ms(void)
{
    /*
    Functionalitate viitoare:
    button polling si debounce.
    */
}

void scheduler_task_100ms(void)
{
    /*
    Functionalitate viitoare:
    citire ADC sau senzori.
    */
}

void scheduler_task_500ms(void)
{
    /*
    Functionalitatea concreta atasata taskului:
    LED0 toggle la fiecare 500 ms.
    */

    led_toggle(
        SCHEDULER_CFG_LED0_PORT_REGISTER,
        SCHEDULER_CFG_LED0_PIN_NUMBER
    );
}

void scheduler_task_1000ms(void)
{
    /*
    Functionalitate viitoare:
    actualizare periodica la fiecare secunda.
    */
}

#endif