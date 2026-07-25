#include "iom324pb.h"
#include "intrinsics.h"

#include "scheduler.h"
#include "scheduler_cfg.h"
#include "tc1.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Aplicatie task-oriented bazata pe scheduler cooperativ.

main() realizeaza:
- initializarea configuratiei taskurilor;
- initializarea schedulerului;
- initializarea system tick-ului;
- pornirea dispatcherului.
*/

static void app_init(void);

void main(void)
{
    app_init();

    /*
    Contine bucla infinita a aplicatiei.
    */

    scheduler_dispatcher();
}

static void app_init(void)
{
    /*
    Initializeaza perifericele utilizate de taskuri.
    */

    scheduler_cfg_init();

    /*
    Initializeaza contoarele si flagurile schedulerului.
    */

    scheduler_init();

    /*
    Initializeaza TC1 dedicat system tick-ului.
    */

    tc1_init();

    /*
    Activeaza intreruperile dupa configurarea modulelor.
    */

    __enable_interrupt();

    /*
    Porneste system tick-ul de 10 ms.
    */

    tc1_start();
}