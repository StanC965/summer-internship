#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

#include "pwm.h"
#include "scheduler_cfg.h"

#define SCHEDULER_CFG_INITIAL_STEP       \
    (PWM_DUTY_CYCLE_0_PERCENT)

/*
Exercise 631 timing:

0% -> 100% ramp:
2 s

100% hold:
1 s

0% hold:
1 s

100% hold:
1 s

0% hold:
1 s

100% hold:
1 s

100% -> 0% ramp:
2 s

0% pause:
3 s

Total sequence time:
2 + 1 + 1 + 1 + 1 + 1 + 2 + 3 = 12 s

Ramp resolution:
1% per step

100 steps in 2 s:
2000 ms / 100 = 20 ms per step
*/

/*
Exercise 632 timing:

The horizontal scale is:
1 unit = 500 ms

0% -> 70%:
3 units * 500 ms = 1500 ms

70% -> 0%:
6 units * 500 ms = 3000 ms

0% -> 100%:
immediate transition at unit 9

100% -> 0%:
9 units * 500 ms = 4500 ms

Total sequence time:
18 units * 500 ms = 9000 ms
*/
      
static pwm_duty_cycle_t
    scheduler_cfg_current_pwm_step;

static void scheduler_cfg_apply_next_pwm_step(void);

void scheduler_cfg_init(void)
{
    pwm_init();

    scheduler_cfg_current_pwm_step =
        SCHEDULER_CFG_INITIAL_STEP;
}

void scheduler_task_10ms(void)
{
    /*
    Exercise 624:

    Every 10 ms, apply the next PWM duty cycle:

    0% -> 25% -> 50% -> 75% -> 100% -> 0% ...
    */

    scheduler_cfg_apply_next_pwm_step();
}

void scheduler_task_50ms(void)
{
    /*
    Not used in this application.
    */
}

void scheduler_task_100ms(void)
{
    /*
    Not used in this application.
    */
}

void scheduler_task_500ms(void)
{
    /*
    Not used in this application.
    */
}

void scheduler_task_1000ms(void)
{
    /*
    Not used in this application.
    */
}

static void scheduler_cfg_apply_next_pwm_step(void)
{
    pwm_set_duty_cycle(
        scheduler_cfg_current_pwm_step
    );

    switch (scheduler_cfg_current_pwm_step)
    {
        case PWM_DUTY_CYCLE_0_PERCENT:
        {
            scheduler_cfg_current_pwm_step =
                PWM_DUTY_CYCLE_25_PERCENT;

            break;
        }

        case PWM_DUTY_CYCLE_25_PERCENT:
        {
            scheduler_cfg_current_pwm_step =
                PWM_DUTY_CYCLE_50_PERCENT;

            break;
        }

        case PWM_DUTY_CYCLE_50_PERCENT:
        {
            scheduler_cfg_current_pwm_step =
                PWM_DUTY_CYCLE_75_PERCENT;

            break;
        }

        case PWM_DUTY_CYCLE_75_PERCENT:
        {
            scheduler_cfg_current_pwm_step =
                PWM_DUTY_CYCLE_100_PERCENT;

            break;
        }

        case PWM_DUTY_CYCLE_100_PERCENT:
        default:
        {
            scheduler_cfg_current_pwm_step =
                PWM_DUTY_CYCLE_0_PERCENT;

            break;
        }
    }
}

#endif