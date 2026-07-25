#ifndef TASKS_C
#define TASKS_C

#include "iom324pb.h"

#include "gpio.h"
#include "led.h"
#include "tasks.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea taskurilor generice ale aplicatiei.

Taskurile trebuie:
- sa fie scurte;
- sa nu contina software delays;
- sa nu contina bucle infinite;
- sa returneze controlul catre scheduler.
*/

/* ========================================================= */
/* LED0                                                      */
/* ========================================================= */

/*
Main board LED0:
PC7, active-low.
*/

#define TASKS_LED0_DDR_REGISTER         (&DDRC)
#define TASKS_LED0_PORT_REGISTER        (&PORTC)
#define TASKS_LED0_PIN_NUMBER           (7U)

/* ========================================================= */
/* MODULE INITIALIZATION                                     */
/* ========================================================= */

void tasks_init(void)
{
    gpio_init();

    led_init(
        TASKS_LED0_DDR_REGISTER,
        TASKS_LED0_PORT_REGISTER,
        TASKS_LED0_PIN_NUMBER
    );
}

/* ========================================================= */
/* 10 MS TASK                                                */
/* ========================================================= */

void task_10ms(void)
{
    /*
    Functionalitati potrivite pentru acest task:
    - procesare rapida;
    - citire intrari;
    - actualizare contoare software.
    */
}

/* ========================================================= */
/* 50 MS TASK                                                */
/* ========================================================= */

void task_50ms(void)
{
    /*
    Functionalitate concreta posibila:
    - citire si debounce pentru SW0.
    */
}

/* ========================================================= */
/* 100 MS TASK                                               */
/* ========================================================= */

void task_100ms(void)
{
    /*
    Functionalitate concreta posibila:
    - pornirea unei conversii ADC;
    - citirea periodica a unui senzor.
    */
}

/* ========================================================= */
/* 500 MS TASK                                               */
/* ========================================================= */

void task_500ms(void)
{
    /*
    Functia concreta este relocata in interiorul
    taskului generic.

    Pentru demonstratie, LED0 este comutat
    la fiecare 500 ms.
    */

    led_toggle(
        TASKS_LED0_PORT_REGISTER,
        TASKS_LED0_PIN_NUMBER
    );
}

/* ========================================================= */
/* 1000 MS TASK                                              */
/* ========================================================= */

void task_1000ms(void)
{
    /*
    Functionalitate concreta posibila:
    - actualizare stare o data pe secunda;
    - monitorizare;
    - transmitere periodica de informatii.
    */
}

#endif