#ifndef TC0_C
#define TC0_C

#include "iom324pb.h"

#include "tc0.h"

/* CTC Mode: WGM02:0 = 010 */

#define TC0_CTC_MODE_WGM02_VALUE             (0U)
#define TC0_CTC_MODE_WGM01_VALUE             (1U)
#define TC0_CTC_MODE_WGM00_VALUE             (0U)

/* Compare output configuration */

#define TC0_OC0A_DISCONNECTED_COM0A1         (0U)
#define TC0_OC0A_DISCONNECTED_COM0A0         (0U)

#define TC0_OC0A_TOGGLE_COM0A1               (0U)
#define TC0_OC0A_TOGGLE_COM0A0               (1U)

#define TC0_CHANNEL_B_DISABLED               (0U)

/* Interrupt configuration */

#define TC0_COMPARE_A_INTERRUPT_ENABLE       (1U)
#define TC0_COMPARE_B_INTERRUPT_DISABLE      (0U)
#define TC0_OVERFLOW_INTERRUPT_DISABLE       (0U)

/* Clock stopped */

#define TC0_CLOCK_STOPPED_CS02               (0U)
#define TC0_CLOCK_STOPPED_CS01               (0U)
#define TC0_CLOCK_STOPPED_CS00               (0U)

/* No prescaler: 001 */

#define TC0_PRESCALER_1_CS02                 (0U)
#define TC0_PRESCALER_1_CS01                 (0U)
#define TC0_PRESCALER_1_CS00                 (1U)

/* Prescaler 8: 010 */

#define TC0_PRESCALER_8_CS02                 (0U)
#define TC0_PRESCALER_8_CS01                 (1U)
#define TC0_PRESCALER_8_CS00                 (0U)

/* Prescaler 64: 011 */

#define TC0_PRESCALER_64_CS02                (0U)
#define TC0_PRESCALER_64_CS01                (1U)
#define TC0_PRESCALER_64_CS00                (1U)

/* Prescaler 256: 100 */

#define TC0_PRESCALER_256_CS02               (1U)
#define TC0_PRESCALER_256_CS01               (0U)
#define TC0_PRESCALER_256_CS00               (0U)

/* Prescaler 1024: 101 */

#define TC0_PRESCALER_1024_CS02              (1U)
#define TC0_PRESCALER_1024_CS01              (0U)
#define TC0_PRESCALER_1024_CS00              (1U)

/* Other values */

#define TC0_FORCE_COMPARE_DISABLED           (0U)
#define TC0_OC0A_TOGGLE_DISABLED             (0U)
#define TC0_OC0A_TOGGLE_ENABLED              (1U)

static tc0_callback_t tc0_compare_a_callback;

#pragma vector=TIMER0_COMPA_vect
__interrupt void tc0_compare_a_isr(void)
{
    if (tc0_compare_a_callback != 0)
    {
        tc0_compare_a_callback();
    }
}

void tc0_init(
    tc0_uint8_t tc0_top_value,
    tc0_uint8_t tc0_toggle_oc0a,
    tc0_callback_t tc0_callback
)
{
    tc0_stop();

    tc0_compare_a_callback = tc0_callback;

    /*
    Configureaza CTC Mode:
    WGM02:0 = 010.
    */

    TCCR0A_WGM00 = TC0_CTC_MODE_WGM00_VALUE;
    TCCR0A_WGM01 = TC0_CTC_MODE_WGM01_VALUE;
    TCCR0B_WGM02 = TC0_CTC_MODE_WGM02_VALUE;

    /*
    Configureaza OC0A.
    */

    if (tc0_toggle_oc0a == TC0_OC0A_TOGGLE_ENABLED)
    {
        TCCR0A_COM0A1 = TC0_OC0A_TOGGLE_COM0A1;
        TCCR0A_COM0A0 = TC0_OC0A_TOGGLE_COM0A0;
    }
    else
    {
        TCCR0A_COM0A1 =
            TC0_OC0A_DISCONNECTED_COM0A1;

        TCCR0A_COM0A0 =
            TC0_OC0A_DISCONNECTED_COM0A0;
    }

    /*
    Canalul B nu este folosit.
    */

    TCCR0A_COM0B1 = TC0_CHANNEL_B_DISABLED;
    TCCR0A_COM0B0 = TC0_CHANNEL_B_DISABLED;

    TCCR0B_FOC0A = TC0_FORCE_COMPARE_DISABLED;
    TCCR0B_FOC0B = TC0_FORCE_COMPARE_DISABLED;

    /*
    OCR0A este TOP in CTC Mode.
    */

    OCR0A = tc0_top_value;

    /*
    Counterul porneste de la zero.
    */

    TCNT0 = 0U;

    /*
    Se foloseste numai Compare Match A Interrupt.
    */

    TIMSK0_TOIE0 = TC0_OVERFLOW_INTERRUPT_DISABLE;
    TIMSK0_OCIE0B = TC0_COMPARE_B_INTERRUPT_DISABLE;
    TIMSK0_OCIE0A = TC0_COMPARE_A_INTERRUPT_ENABLE;
}

void tc0_start_prescaler_1(void)
{
    TCCR0B_CS02 = TC0_PRESCALER_1_CS02;
    TCCR0B_CS01 = TC0_PRESCALER_1_CS01;
    TCCR0B_CS00 = TC0_PRESCALER_1_CS00;
}

void tc0_start_prescaler_8(void)
{
    TCCR0B_CS02 = TC0_PRESCALER_8_CS02;
    TCCR0B_CS01 = TC0_PRESCALER_8_CS01;
    TCCR0B_CS00 = TC0_PRESCALER_8_CS00;
}

void tc0_start_prescaler_64(void)
{
    TCCR0B_CS02 = TC0_PRESCALER_64_CS02;
    TCCR0B_CS01 = TC0_PRESCALER_64_CS01;
    TCCR0B_CS00 = TC0_PRESCALER_64_CS00;
}

void tc0_start_prescaler_256(void)
{
    TCCR0B_CS02 = TC0_PRESCALER_256_CS02;
    TCCR0B_CS01 = TC0_PRESCALER_256_CS01;
    TCCR0B_CS00 = TC0_PRESCALER_256_CS00;
}

void tc0_start_prescaler_1024(void)
{
    TCCR0B_CS02 = TC0_PRESCALER_1024_CS02;
    TCCR0B_CS01 = TC0_PRESCALER_1024_CS01;
    TCCR0B_CS00 = TC0_PRESCALER_1024_CS00;
}

void tc0_stop(void)
{
    TCCR0B_CS02 = TC0_CLOCK_STOPPED_CS02;
    TCCR0B_CS01 = TC0_CLOCK_STOPPED_CS01;
    TCCR0B_CS00 = TC0_CLOCK_STOPPED_CS00;
}

#endif