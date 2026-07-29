#ifndef PWM_C
#define PWM_C

#include "iom324pb.h"

#include "pwm.h"

/*
TC0 Fast PWM configuration:

- System clock: 16 MHz
- Timer: TC0
- PWM output: OC0A
- OC0A pin: PB3
- OLED1 LED1 connected through EXT4 pin 7
- Fast PWM mode
- TOP = 0xFF
- Prescaler = 64

PWM frequency:

fPWM = fCPU / (prescaler * 256)

fPWM = 16000000 / (64 * 256)
     = 976.5625 Hz

OLED1 LED1 is active-low.

For intermediate duty-cycle values, inverting Fast PWM mode
is used so that the requested percentage represents the
visible LED ON time.
*/

/*
Exercise 625 - STRETCH

TC0 is an 8-bit timer.

Number of steps:
2^8 = 256 steps

Duty-cycle resolution:

100% / 256 = 0.390625%

Answer:
Number of steps: 256
Step size: approximately 0.39%
*/

#define PWM_ZERO                              (0U)
#define PWM_ONE                               (1U)

#define PWM_OC0A_PIN_NUMBER                   (3U)

#define PWM_PERCENT_MINIMUM                   (0U)
#define PWM_PERCENT_MAXIMUM                   (100U)

#define PWM_COMPARE_MAXIMUM                   (255U)

#define PWM_25_PERCENT_COMPARE_VALUE          (64U)
#define PWM_50_PERCENT_COMPARE_VALUE          (128U)
#define PWM_75_PERCENT_COMPARE_VALUE          (192U)

/*
TCCR0A bit positions:

bit 7: COM0A1
bit 6: COM0A0
bit 1: WGM01
bit 0: WGM00
*/

#define PWM_COM0A1_BIT                        (7U)
#define PWM_COM0A0_BIT                        (6U)
#define PWM_WGM01_BIT                         (1U)
#define PWM_WGM00_BIT                         (0U)

/*
TCCR0B bit positions:

bit 3: WGM02
bit 2: CS02
bit 1: CS01
bit 0: CS00
*/

#define PWM_WGM02_BIT                         (3U)
#define PWM_CS02_BIT                          (2U)
#define PWM_CS01_BIT                          (1U)
#define PWM_CS00_BIT                          (0U)

/*
Fast PWM with TOP = 0xFF:

WGM02 = 0
WGM01 = 1
WGM00 = 1
*/

#define PWM_FAST_PWM_TCCR0A_MASK              \
    ((PWM_ONE << PWM_WGM01_BIT) |             \
     (PWM_ONE << PWM_WGM00_BIT))

/*
Inverting mode on OC0A:

COM0A1 = 1
COM0A0 = 1
*/

#define PWM_OC0A_INVERTING_MODE_MASK          \
    ((PWM_ONE << PWM_COM0A1_BIT) |            \
     (PWM_ONE << PWM_COM0A0_BIT))

#define PWM_OC0A_COMPARE_MODE_MASK            \
    ((PWM_ONE << PWM_COM0A1_BIT) |            \
     (PWM_ONE << PWM_COM0A0_BIT))

/*
Prescaler 64:

CS02 = 0
CS01 = 1
CS00 = 1
*/

#define PWM_PRESCALER_64_MASK                 \
    ((PWM_ONE << PWM_CS01_BIT) |              \
     (PWM_ONE << PWM_CS00_BIT))

#define PWM_CLOCK_SELECT_MASK                 \
    ((PWM_ONE << PWM_CS02_BIT) |              \
     (PWM_ONE << PWM_CS01_BIT) |              \
     (PWM_ONE << PWM_CS00_BIT))

static void pwm_connect_output(void);

static void pwm_disconnect_output(void);

static void pwm_force_led_off(void);

static void pwm_force_led_on(void);

static void pwm_set_compare_value(
    pwm_uint8_t pwm_compare_value
);

void pwm_init(void)
{
    /*
    PB3 / OC0A configured as output.
    */

    DDRB |= (pwm_uint8_t)(
        PWM_ONE << PWM_OC0A_PIN_NUMBER
    );

    /*
    Stop TC0 during configuration.
    */

    TCCR0B &= (pwm_uint8_t)(
        ~PWM_CLOCK_SELECT_MASK
    );

    /*
    Disconnect OC0A and configure Fast PWM,
    TOP = 0xFF.
    */

    TCCR0A = PWM_FAST_PWM_TCCR0A_MASK;

    /*
    WGM02 must be 0.
    */

    TCCR0B &= (pwm_uint8_t)(
        ~(PWM_ONE << PWM_WGM02_BIT)
    );

    TCNT0 = PWM_ZERO;
    OCR0A = PWM_ZERO;

    /*
    Initial state:
    0% visible duty cycle, LED OFF.
    */

    pwm_disconnect_output();
    pwm_force_led_off();
}

void pwm_start(void)
{
    /*
    Clear previous clock source selection.
    */

    TCCR0B &= (pwm_uint8_t)(
        ~PWM_CLOCK_SELECT_MASK
    );

    /*
    Start TC0 with prescaler 64.
    */

    TCCR0B |= PWM_PRESCALER_64_MASK;
}

void pwm_stop(void)
{
    /*
    Stop TC0 by clearing CS02:CS00.
    */

    TCCR0B &= (pwm_uint8_t)(
        ~PWM_CLOCK_SELECT_MASK
    );

    pwm_disconnect_output();
    pwm_force_led_off();
}

void pwm_set_duty_cycle(
    pwm_duty_cycle_t pwm_duty_cycle
)
{
    switch (pwm_duty_cycle)
    {
        case PWM_DUTY_CYCLE_0_PERCENT:
        {
            /*
            Exact 0%:
            disconnect PWM and force LED OFF.
            */

            pwm_disconnect_output();
            pwm_force_led_off();

            break;
        }

        case PWM_DUTY_CYCLE_25_PERCENT:
        {
            pwm_set_compare_value(
                PWM_25_PERCENT_COMPARE_VALUE
            );

            break;
        }

        case PWM_DUTY_CYCLE_50_PERCENT:
        {
            pwm_set_compare_value(
                PWM_50_PERCENT_COMPARE_VALUE
            );

            break;
        }

        case PWM_DUTY_CYCLE_75_PERCENT:
        {
            pwm_set_compare_value(
                PWM_75_PERCENT_COMPARE_VALUE
            );

            break;
        }

        case PWM_DUTY_CYCLE_100_PERCENT:
        {
            /*
            Exact 100%:
            disconnect PWM and force LED ON.
            */

            pwm_disconnect_output();
            pwm_force_led_on();

            break;
        }

        default:
        {
            pwm_disconnect_output();
            pwm_force_led_off();

            break;
        }
    }
}

void pwm_set_duty_cycle_percent(
    pwm_uint8_t pwm_duty_cycle_percent
)
{
    pwm_uint16_t pwm_calculated_compare_value;

    if (
        pwm_duty_cycle_percent <=
        PWM_PERCENT_MINIMUM
    )
    {
        pwm_disconnect_output();
        pwm_force_led_off();
    }
    else if (
        pwm_duty_cycle_percent >=
        PWM_PERCENT_MAXIMUM
    )
    {
        pwm_disconnect_output();
        pwm_force_led_on();
    }
    else
    {
        /*
        Convert percent to 8-bit compare value:

        OCR0A = duty_cycle_percent * 255 / 100

        The addition of 50 provides integer rounding.
        */

        pwm_calculated_compare_value =
            (
                (
                    (pwm_uint16_t)
                    pwm_duty_cycle_percent *
                    PWM_COMPARE_MAXIMUM
                ) +
                50U
            ) /
            PWM_PERCENT_MAXIMUM;

        pwm_set_compare_value(
            (pwm_uint8_t)
            pwm_calculated_compare_value
        );
    }
}

static void pwm_set_compare_value(
    pwm_uint8_t pwm_compare_value
)
{
    OCR0A = pwm_compare_value;

    pwm_connect_output();
}

static void pwm_connect_output(void)
{
    /*
    Clear COM0A1:COM0A0 before selecting the mode.
    */

    TCCR0A &= (pwm_uint8_t)(
        ~PWM_OC0A_COMPARE_MODE_MASK
    );

    /*
    Select inverting Fast PWM on OC0A.
    */

    TCCR0A |= PWM_OC0A_INVERTING_MODE_MASK;
}

static void pwm_disconnect_output(void)
{
    /*
    COM0A1:COM0A0 = 00.

    PB3 returns to normal GPIO operation.
    */

    TCCR0A &= (pwm_uint8_t)(
        ~PWM_OC0A_COMPARE_MODE_MASK
    );
}

static void pwm_force_led_off(void)
{
    /*
    OLED1 LED is active-low.

    HIGH means LED OFF.
    */

    PORTB |= (pwm_uint8_t)(
        PWM_ONE << PWM_OC0A_PIN_NUMBER
    );
}

static void pwm_force_led_on(void)
{
    /*
    OLED1 LED is active-low.

    LOW means LED ON.
    */

    PORTB &= (pwm_uint8_t)(
        ~(PWM_ONE << PWM_OC0A_PIN_NUMBER)
    );
}

#endif