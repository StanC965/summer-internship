#ifndef TASKS_C
#define TASKS_C

#include "iom324pb.h"

#include "gpio.h"
#include "led.h"
#include "tasks.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea taskurilor periodice.

Taskul de 500 ms comuta LED0 pentru verificarea
vizuala a schedulerului cooperativ.
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
/* INITIALIZATION                                            */
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

void tasks_10ms_execute(void)
{
    /*
    Aici poate fi introdusa ulterior o functie care
    trebuie executata la fiecare 10 ms.
    */
}

/* ========================================================= */
/* 50 MS TASK                                                */
/* ========================================================= */

void tasks_50ms_execute(void)
{
    /*
    Exemplu ulterior:
    citirea si debouncing-ul unui buton.
    */
}

/* ========================================================= */
/* 100 MS TASK                                               */
/* ========================================================= */

void tasks_100ms_execute(void)
{
    /*
    Exemplu ulterior:
    pornirea unei conversii ADC sau citirea unui senzor.
    */
}

/* ========================================================= */
/* 500 MS TASK                                               */
/* ========================================================= */

void tasks_500ms_execute(void)
{
    /*
    Demonstratie vizuala:
    LED0 este comutat la fiecare 500 ms.
    */

    led_toggle(
        TASKS_LED0_PORT_REGISTER,
        TASKS_LED0_PIN_NUMBER
    );
}

/* ========================================================= */
/* 1000 MS TASK                                              */
/* ========================================================= */

void tasks_1000ms_execute(void)
{
    /*
    Aici poate fi introdusa ulterior o functie care
    trebuie executata la fiecare secunda.
    */
}

#endif