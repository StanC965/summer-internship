#ifndef PWM_C
#define PWM_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "pwm.h"
#include "gpio.h"
#include <iom324pb.h>
#include <intrinsics.h>
#include "led.h"
#include "timer.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static const uint8_t pwm_duty_steps[PWM_STEP_COUNT] = {0, 25, 50, 75, 100};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void pwm_init(void)
{
    PRR0 &= ~(1 << PRTIM0);

    TCCR0A = (1 << WGM01) | (1 << WGM00);
    TCCR0B = 0x00;
}

void pwm_start(void)
{
    TCCR0B |= (1 << CS00);
}

void pwm_set_duty_cycle(uint8_t duty_percent)
{
    __disable_interrupt();

    if (duty_percent == 0)
    {
        TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
        led_power_off(LED_IO1);
    }
    else if (duty_percent >= 100)
    {
        TCCR0A |= (1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);
        OCR0A = 0xFF;
    }
    else
    {
        TCCR0A |= (1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);
        OCR0A = (uint8_t)(((uint16_t)duty_percent * PWM_RESOLUTION) / 100U);
    }

    __enable_interrupt();
}

void pwm_incremental_update(void)
{
    static uint8_t run_counter = 0;

    uint8_t step_index = run_counter % PWM_STEP_COUNT;
    pwm_set_duty_cycle(pwm_duty_steps[step_index]);

    run_counter++;
}

void pwm_sequence_update(void)
{
    static pwm_seq_phase_t phase = SEQ_RAMP_UP;
    static uint8_t duty = 0;
    static uint8_t tick_count = 0;

    switch (phase)
    {
    case SEQ_RAMP_UP:
        pwm_set_duty_cycle(duty);
        if (duty >= 100)
        {
            phase = SEQ_HOLD_HIGH_1;
            tick_count = 0;
        }
        else
        {
            duty += SEQ_RAMP_STEP_PERCENT;
        }
        break;

    case SEQ_HOLD_HIGH_1:
    case SEQ_HOLD_HIGH_2:
    case SEQ_HOLD_HIGH_3:
        pwm_set_duty_cycle(100);
        if (++tick_count >= SEQ_HOLD_TICKS)
        {
            tick_count = 0;
            phase = (phase == SEQ_HOLD_HIGH_1) ? SEQ_DIP_LOW_1 : (phase == SEQ_HOLD_HIGH_2) ? SEQ_DIP_LOW_2
                                                                                            : SEQ_RAMP_DOWN;
        }
        break;

    case SEQ_DIP_LOW_1:
    case SEQ_DIP_LOW_2:
        pwm_set_duty_cycle(0);
        if (++tick_count >= SEQ_HOLD_TICKS)
        {
            tick_count = 0;
            phase = (phase == SEQ_DIP_LOW_1) ? SEQ_HOLD_HIGH_2 : SEQ_HOLD_HIGH_3;
        }
        break;

    case SEQ_RAMP_DOWN:
        pwm_set_duty_cycle(duty);
        if (duty == 0)
        {
            phase = SEQ_PAUSE;
            tick_count = 0;
        }
        else
        {
            duty -= SEQ_RAMP_STEP_PERCENT;
        }
        break;

    case SEQ_PAUSE:
        pwm_set_duty_cycle(0);
        if (++tick_count >= SEQ_PAUSE_TICKS)
        {
            tick_count = 0;
            phase = SEQ_RAMP_UP;
            duty = 0;
        }
        break;
    }
}

#endif /* PWM_C */
