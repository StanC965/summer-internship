#include "iom324pb.h"
#include "adc.h"

/*
TEMT6000:
PA4 / ADC4

ADC configuration:
- 10-bit resolution
- AVCC reference
- right-adjusted result
- ADC clock = 16 MHz / 128 = 125 kHz
- interrupt enabled

TEMT6000 behavior required by Hyundai:
high light intensity = low voltage
low light intensity  = high voltage
*/

#define ADC_ZERO                    (0U)
#define ADC_ONE                     (1U)

/*
ADMUX:
bit 6 = REFS0
bit 5 = ADLAR
bits 4:0 = MUX
*/

#define ADC_REFS0_BIT               (6U)
#define ADC_ADLAR_BIT               (5U)

#define ADC_MUX0_BIT                (0U)
#define ADC_MUX1_BIT                (1U)
#define ADC_MUX2_BIT                (2U)
#define ADC_MUX3_BIT                (3U)

#define ADC_CHANNEL_4_MASK          \
    (ADC_ONE << ADC_MUX2_BIT)

/*
ADCSRA:
bit 7 = ADEN
bit 6 = ADSC
bit 3 = ADIE
bits 2:0 = ADPS2:ADPS0
*/

#define ADC_ADEN_BIT                (7U)
#define ADC_ADSC_BIT                (6U)
#define ADC_ADIE_BIT                (3U)

#define ADC_ADPS2_BIT               (2U)
#define ADC_ADPS1_BIT               (1U)
#define ADC_ADPS0_BIT               (0U)

#define ADC_PRESCALER_128_MASK      \
    ((ADC_ONE << ADC_ADPS2_BIT) |   \
     (ADC_ONE << ADC_ADPS1_BIT) |   \
     (ADC_ONE << ADC_ADPS0_BIT))

/*
DIDR0:
bit 4 = ADC4D
*/

#define ADC_ADC4D_BIT               (4U)

static volatile adc_uint16_t adc_data;
static volatile adc_uint8_t adc_data_ready;
static volatile adc_uint8_t adc_conversion_running;

void adc_init(void)
{
    /*
    PA4 configured as input.
    */

    DDRA &= (adc_uint8_t)(
        ~(ADC_ONE << 4U)
    );

    /*
    AVCC reference, right-adjusted result, ADC4.
    ADLAR remains 0 for 10-bit conversion.
    */

    ADMUX =
        (adc_uint8_t)(
            (ADC_ONE << ADC_REFS0_BIT) |
            ADC_CHANNEL_4_MASK
        );

    /*
    Disable digital input buffer on ADC4.
    */

    DIDR0 |= (adc_uint8_t)(
        ADC_ONE << ADC_ADC4D_BIT
    );

    ADCSRA =
        (adc_uint8_t)(
            (ADC_ONE << ADC_ADEN_BIT) |
            (ADC_ONE << ADC_ADIE_BIT) |
            ADC_PRESCALER_128_MASK
        );

    adc_data = ADC_ZERO;
    adc_data_ready = ADC_DATA_NOT_READY;
    adc_conversion_running = ADC_ZERO;
}

void adc_start_conversion(void)
{
    if (adc_conversion_running == ADC_ZERO)
    {
        adc_data_ready =
            ADC_DATA_NOT_READY;

        adc_conversion_running =
            ADC_ONE;

        ADCSRA |= (adc_uint8_t)(
            ADC_ONE << ADC_ADSC_BIT
        );
    }
}

adc_uint8_t adc_is_data_ready(void)
{
    return adc_data_ready;
}

adc_uint16_t adc_get_data(void)
{
    adc_uint16_t data_copy;

    data_copy = adc_data;

    adc_data_ready =
        ADC_DATA_NOT_READY;

    return data_copy;
}

#pragma vector=ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_uint8_t adc_low;
    adc_uint8_t adc_high;

    /*
    For a 10-bit ADC result, ADCL must be read first.
    */

    adc_low = ADCL;
    adc_high = ADCH;

    adc_data =
        (adc_uint16_t)(
            (
                (adc_uint16_t)adc_high << 8U
            ) |
            adc_low
        );

    adc_data_ready =
        ADC_DATA_READY;

    adc_conversion_running =
        ADC_ZERO;
}