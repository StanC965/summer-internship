#include "iom324pb.h"
#include "intrinsics.h"

#include "scheduler.h"
#include "tc1.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Test pentru scheduler flags management.

TC1 produce system tick-ul la fiecare 10 ms.
ISR-ul administreaza flagurile pentru:
10 ms, 50 ms, 100 ms, 500 ms si 1000 ms.
*/

static void app_init(void);

void main(void)
{
    app_init();

    while (SCHEDULER_TRUE)
    {
        if (
            scheduler_is_10ms_flag_active() ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_clear_10ms_flag();

            /*
            Aici va fi apelat taskul de 10 ms.
            */
        }

        if (
            scheduler_is_50ms_flag_active() ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_clear_50ms_flag();

            /*
            Aici va fi apelat taskul de 50 ms.
            */
        }

        if (
            scheduler_is_100ms_flag_active() ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_clear_100ms_flag();

            /*
            Aici va fi apelat taskul de 100 ms.
            */
        }

        if (
            scheduler_is_500ms_flag_active() ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_clear_500ms_flag();

            /*
            Aici va fi apelat taskul de 500 ms.
            */
        }

        if (
            scheduler_is_1000ms_flag_active() ==
            SCHEDULER_FLAG_ACTIVE
        )
        {
            scheduler_clear_1000ms_flag();

            /*
            Aici va fi apelat taskul de 1000 ms.
            */
        }
    }
}

static void app_init(void)
{
    scheduler_init();

    tc1_init();

    __enable_interrupt();

    tc1_start();
}