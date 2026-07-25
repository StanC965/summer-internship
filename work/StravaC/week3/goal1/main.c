#include "iom324pb.h"
#include "intrinsics.h"

#include "scheduler.h"
#include "tasks.h"
#include "tc1.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Scheduler cooperativ bazat pe system tick de 10 ms.

Componente:
- TC1 genereaza system tick-ul;
- schedulerul administreaza flagurile;
- dispatcherul verifica flagurile;
- taskurile sunt executate in main.

Taskurile nu se intrerup intre ele.
Fiecare task trebuie sa se termine si sa returneze
controlul catre dispatcher.
*/

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void app_init(void);

static void app_tasks_dispatcher(void);

/* ========================================================= */
/* MAIN                                                      */
/* ========================================================= */

void main(void)
{
    app_init();

    while (SCHEDULER_TRUE)
    {
        app_tasks_dispatcher();
    }
}

/* ========================================================= */
/* APPLICATION INITIALIZATION                                */
/* ========================================================= */

static void app_init(void)
{
    /*
    Ordinea initializarii:

    1. taskurile si perifericele utilizate de ele;
    2. schedulerul si flagurile;
    3. TC1 pentru system tick;
    4. intreruperile globale;
    5. pornirea timerului.
    */

    tasks_init();

    scheduler_init();

    tc1_init();

    __enable_interrupt();

    tc1_start();
}

/* ========================================================= */
/* TASKS DISPATCHER                                          */
/* ========================================================= */

static void app_tasks_dispatcher(void)
{
    /*
    Fiecare flag este verificat.

    Flagul este resetat inainte de apelarea taskului,
    pentru a evita executia repetata in aceeasi
    fereastra de timp.
    */

    if (
        scheduler_is_10ms_flag_active() ==
        SCHEDULER_FLAG_ACTIVE
    )
    {
        scheduler_clear_10ms_flag();

        tasks_10ms_execute();
    }

    if (
        scheduler_is_50ms_flag_active() ==
        SCHEDULER_FLAG_ACTIVE
    )
    {
        scheduler_clear_50ms_flag();

        tasks_50ms_execute();
    }

    if (
        scheduler_is_100ms_flag_active() ==
        SCHEDULER_FLAG_ACTIVE
    )
    {
        scheduler_clear_100ms_flag();

        tasks_100ms_execute();
    }

    if (
        scheduler_is_500ms_flag_active() ==
        SCHEDULER_FLAG_ACTIVE
    )
    {
        scheduler_clear_500ms_flag();

        tasks_500ms_execute();
    }

    if (
        scheduler_is_1000ms_flag_active() ==
        SCHEDULER_FLAG_ACTIVE
    )
    {
        scheduler_clear_1000ms_flag();

        tasks_1000ms_execute();
    }
}