#include "iom324pb.h"
#include "pwm.h"

/*
OLED1 mounted on EXT4:

LED1 -> EXT4 pin 7 -> PB3 / OC0A
LED2 -> EXT4 pin 8 -> PB4 / OC0B

Both LEDs are active-low.

TC0:
- Fast PWM
- TOP = 0xFF
- prescaler = 64
- frequency = 16 MHz / (64 * 256)
            = 976.5625 Hz
*/

#define PWM_ZERO                    (0U)
#define PWM_ONE                     (1U)

#define PWM_OC0A_PIN                (3U)
#define PWM_OC0B_PIN                (4U)

#define PWM_MAX_PERCENT             (100U)
#define PWM_MAX_COMPARE             (255U)

/*
TCCR0A bits.
*/

#define PWM_COM0A1_BIT              (7U)
#define PWM_COM0A0_BIT              (6U)

#define PWM_COM0B1_BIT              (5U)
#define PWM_COM0B0_BIT              (4U)

#define PWM_WGM01_BIT               (1U)
#define PWM_WGM00_BIT               (0U)

/*
TCCR0B bits.
*/

#define PWM_WGM02_BIT               (3U)

#define PWM_CS02_BIT                (2U)
#define PWM_CS01_BIT                (1U)
#define PWM_CS00_BIT                (0U)

#define PWM_FAST_PWM_MASK           \
    ((PWM_ONE << PWM_WGM01_BIT) |   \
     (PWM_ONE << PWM_WGM00_BIT))

#define PWM_CHANNEL_A_COM_MASK      \
    ((PWM_ONE << PWM_COM0A1_BIT) |  \
     (PWM_ONE << PWM_COM0A0_BIT))

#define PWM_CHANNEL_B_COM_MASK      \
    ((PWM_ONE << PWM_COM0B1_BIT) |  \
     (PWM_ONE << PWM_COM0B0_BIT))

#define PWM_PRESCALER_64_MASK       \
    ((PWM_ONE << PWM_CS01_BIT) |    \
     (PWM_ONE << PWM_CS00_BIT))

#define PWM_CLOCK_MASK              \
    ((PWM_ONE << PWM_CS02_BIT) |    \
     (PWM_ONE << PWM_CS01_BIT) |    \
     (PWM_ONE << PWM_CS00_BIT))

static void pwm_connect_channel(
    pwm_channel_t channel
);

static void pwm_disconnect_channel(
    pwm_channel_t channel
);

static void pwm_force_channel_off(
    pwm_channel_t channel
);

static void pwm_force_channel_on(
    pwm_channel_t channel
);

void pwm_init(void)
{
    /*
    PB3 and PB4 configured as outputs.
    */

    DDRB |= (pwm_uint8_t)(
        (PWM_ONE << PWM_OC0A_PIN) |
        (PWM_ONE << PWM_OC0B_PIN)
    );

    /*
    Stop TC0 while configuring.
    */

    TCCR0B &= (pwm_uint8_t)(
        ~PWM_CLOCK_MASK
    );

    /*
    Fast PWM, TOP = 0xFF.
    Both channels initially disconnected.
    */

    TCCR0A = PWM_FAST_PWM_MASK;

    TCCR0B &= (pwm_uint8_t)(
        ~(PWM_ONE << PWM_WGM02_BIT)
    );

    TCNT0 = PWM_ZERO;

    OCR0A = PWM_ZERO;
    OCR0B = PWM_ZERO;

    pwm_force_channel_off(
        PWM_CHANNEL_DAY_LED
    );

    pwm_force_channel_off(
        PWM_CHANNEL_NIGHT_LED
    );
}

void pwm_start(void)
{
    TCCR0B &= (pwm_uint8_t)(
        ~PWM_CLOCK_MASK
    );

    TCCR0B |= PWM_PRESCALER_64_MASK;
}

void pwm_stop(void)
{
    TCCR0B &= (pwm_uint8_t)(
        ~PWM_CLOCK_MASK
    );

    pwm_disconnect_channel(
        PWM_CHANNEL_DAY_LED
    );

    pwm_disconnect_channel(
        PWM_CHANNEL_NIGHT_LED
    );

    pwm_force_channel_off(
        PWM_CHANNEL_DAY_LED
    );

    pwm_force_channel_off(
        PWM_CHANNEL_NIGHT_LED
    );
}

void pwm_set_duty_cycle_percent(
    pwm_channel_t channel,
    pwm_uint8_t duty_cycle_percent
)
{
    pwm_uint16_t compare_value;

    if (duty_cycle_percent == PWM_ZERO)
    {
        pwm_disconnect_channel(channel);
        pwm_force_channel_off(channel);

        return;
    }

    if (duty_cycle_percent >= PWM_MAX_PERCENT)
    {
        pwm_disconnect_channel(channel);
        pwm_force_channel_on(channel);

        return;
    }

    compare_value =
        (
            (
                (pwm_uint16_t)duty_cycle_percent *
                PWM_MAX_COMPARE
            ) +
            50U
        ) /
        PWM_MAX_PERCENT;

    if (channel == PWM_CHANNEL_DAY_LED)
    {
        OCR0A = (pwm_uint8_t)compare_value;
    }
    else
    {
        OCR0B = (pwm_uint8_t)compare_value;
    }

    pwm_connect_channel(channel);
}

static void pwm_connect_channel(
    pwm_channel_t channel
)
{
    if (channel == PWM_CHANNEL_DAY_LED)
    {
        TCCR0A &= (pwm_uint8_t)(
            ~PWM_CHANNEL_A_COM_MASK
        );

        /*
        Inverting PWM because the LED is active-low.
        */

        TCCR0A |= PWM_CHANNEL_A_COM_MASK;
    }
    else
    {
        TCCR0A &= (pwm_uint8_t)(
            ~PWM_CHANNEL_B_COM_MASK
        );

        TCCR0A |= PWM_CHANNEL_B_COM_MASK;
    }
}

static void pwm_disconnect_channel(
    pwm_channel_t channel
)
{
    if (channel == PWM_CHANNEL_DAY_LED)
    {
        TCCR0A &= (pwm_uint8_t)(
            ~PWM_CHANNEL_A_COM_MASK
        );
    }
    else
    {
        TCCR0A &= (pwm_uint8_t)(
            ~PWM_CHANNEL_B_COM_MASK
        );
    }
}

static void pwm_force_channel_off(
    pwm_channel_t channel
)
{
    if (channel == PWM_CHANNEL_DAY_LED)
    {
        PORTB |= (pwm_uint8_t)(
            PWM_ONE << PWM_OC0A_PIN
        );
    }
    else
    {
        PORTB |= (pwm_uint8_t)(
            PWM_ONE << PWM_OC0B_PIN
        );
    }
}

static void pwm_force_channel_on(
    pwm_channel_t channel
)
{
    if (channel == PWM_CHANNEL_DAY_LED)
    {
        PORTB &= (pwm_uint8_t)(
            ~(PWM_ONE << PWM_OC0A_PIN)
        );
    }
    else
    {
        PORTB &= (pwm_uint8_t)(
            ~(PWM_ONE << PWM_OC0B_PIN)
        );
    }
}