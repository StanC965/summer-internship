#include "iom324pb.h"
#include "intrinsics.h"

#include "scheduler.h"
#include "tasks.h"
#include "tc1.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Aplicatie bazata pe scheduler cooperativ.

main() realizeaza numai:
- initializarea modulelor;
- activarea intreruperilor;
- pornirea system tick-ului;
- apelarea dispatcherului.
*/

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void app_init(void);

/* ========================================================= */
/* MAIN                                                      */
/* ========================================================= */

void main(void)
{
    app_init();

    /*
    Functia contine bucla infinita a schedulerului
    si nu trebuie sa returneze.
    */

    scheduler_tasks_dispatcher();
}

/* ========================================================= */
/* APPLICATION INITIALIZATION                                */
/* ========================================================= */

static void app_init(void)
{
    /*
    Initializarea functionalitatilor aplicatiei.
    */

    tasks_init();

    /*
    Initializarea contoarelor si flagurilor.
    */

    scheduler_init();

    /*
    Initializarea timerului dedicat system tick-ului.
    TC1 ramane oprit dupa tc1_init().
    */

    tc1_init();

    /*
    Activeaza intreruperile globale numai dupa ce toate
    modulele au fost configurate.
    */

    __enable_interrupt();

    /*
    Porneste TC1 si generarea system tick-ului de 10 ms.
    */

    tc1_start();
}