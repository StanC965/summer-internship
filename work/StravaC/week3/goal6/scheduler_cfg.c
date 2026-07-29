#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

#include "pwm.h"
#include "scheduler_cfg.h"

/*
Exercise 634 - OPTIONAL
Heart Beat illumination pattern

Source:
HeartBeat_illumination_pattern.xlsx

One complete cycle:
1.6 seconds

Sampling period:
0.05 seconds = 50 ms

Number of intervals:
1.6 seconds / 0.05 seconds = 32 intervals

Number of discrete points:
32 intervals + initial point = 33 points

The PWM driver accepts integer percentages.
Therefore, the values from the Excel file are rounded
to the nearest integer percentage.

The heartbeat table is processed by scheduler_task_50ms().
One new PWM duty-cycle value is applied every 50 ms.

Complete sequence duration:

33 points are stored, but the first and last values are both 0%.
The time between the first point and the last point is:

32 intervals * 50 ms = 1600 ms = 1.6 seconds

After reaching the last point, the table index returns to zero
and the heartbeat sequence starts again.
*/

#define SCHEDULER_CFG_ZERO                    (0U)

#define SCHEDULER_CFG_HEARTBEAT_POINTS        (33U)

typedef unsigned char scheduler_cfg_uint8_t;

/*
Rounded Heart Beat duty-cycle values:

Time [s]    Excel [%]    Applied [%]

0.00          0.0000         0
0.05          0.2175         0
0.10          0.4350         0
0.15          0.6525         1
0.20          0.8700         1
0.25          1.0875         1
0.30          1.3050         1
0.35          1.5225         2
0.40          1.7400         2
0.45         21.3050        21
0.50         40.8700        41
0.55         60.4350        60
0.60         80.0000        80
0.65         56.6667        57
0.70         33.3333        33
0.75         10.0000        10
0.80         32.5000        33
0.85         55.0000        55
0.90         77.5000        78
0.95        100.0000       100
1.00         92.3077        92
1.05         84.6154        85
1.10         76.9231        77
1.15         69.2308        69
1.20         61.5385        62
1.25         53.8462        54
1.30         46.1538        46
1.35         38.4615        38
1.40         30.7692        31
1.45         23.0769        23
1.50         15.3846        15
1.55          7.6923         8
1.60          0.0000         0
*/

static const scheduler_cfg_uint8_t
    scheduler_cfg_heartbeat_duty_cycle[
        SCHEDULER_CFG_HEARTBEAT_POINTS
    ] =
{
      0U,
      0U,
      0U,
      1U,
      1U,
      1U,
      1U,
      2U,
      2U,
     21U,
     41U,
     60U,
     80U,
     57U,
     33U,
     10U,
     33U,
     55U,
     78U,
    100U,
     92U,
     85U,
     77U,
     69U,
     62U,
     54U,
     46U,
     38U,
     31U,
     23U,
     15U,
      8U,
      0U
};

static scheduler_cfg_uint8_t
    scheduler_cfg_heartbeat_index;

static void scheduler_cfg_apply_heartbeat_point(void);

void scheduler_cfg_init(void)
{
    pwm_init();

    scheduler_cfg_heartbeat_index =
        SCHEDULER_CFG_ZERO;

    /*
    Initial heartbeat value is 0%.
    The LED starts in the OFF state.
    */

    pwm_set_duty_cycle_percent(
        scheduler_cfg_heartbeat_duty_cycle[
            scheduler_cfg_heartbeat_index
        ]
    );
}

void scheduler_task_10ms(void)
{
    /*
    Not used for the Heart Beat pattern.

    Important:
    No other task must change the PWM duty cycle while
    the heartbeat application is active.
    */
}

void scheduler_task_50ms(void)
{
    /*
    The Excel file contains one duty-cycle value
    for every 50 ms.

    Therefore, one table point is applied at every
    execution of this task.
    */

    scheduler_cfg_apply_heartbeat_point();
}

void scheduler_task_100ms(void)
{
    /*
    Not used for the Heart Beat pattern.
    */
}

void scheduler_task_500ms(void)
{
    /*
    Not used for the Heart Beat pattern.
    */
}

void scheduler_task_1000ms(void)
{
    /*
    Not used for the Heart Beat pattern.
    */
}

static void scheduler_cfg_apply_heartbeat_point(void)
{
    pwm_set_duty_cycle_percent(
        scheduler_cfg_heartbeat_duty_cycle[
            scheduler_cfg_heartbeat_index
        ]
    );

    scheduler_cfg_heartbeat_index++;

    if (
        scheduler_cfg_heartbeat_index >=
        SCHEDULER_CFG_HEARTBEAT_POINTS
    )
    {
        /*
        The complete 1.6-second Heart Beat pattern
        has finished.

        Start again from the first table value.
        */

        scheduler_cfg_heartbeat_index =
            SCHEDULER_CFG_ZERO;
    }
}

#endif