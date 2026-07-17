#ifndef ADC_C
#define ADC_C

#include "iom324pb.h"
#include "intrinsics.h"

#include "adc.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului ADC.

Configuratie:
- referinta AVCC = 3.3V;
- rezultat left-adjusted;
- intrare single-ended ADC4;
- Single Conversion Mode;
- fara auto-trigger;
- intrerupere la finalul conversiei;
- rezultat de 8 biti.
*/

/* ADC reference selection: AVCC */

#define ADC_REFERENCE_AVCC_REFS1             (0U)
#define ADC_REFERENCE_AVCC_REFS0             (1U)

/* ADC result alignment */

#define ADC_RESULT_LEFT_ADJUSTED              (1U)

/* ADC4 channel: MUX[4:0] = 00100 */

#define ADC_CHANNEL_ADC4_MUX4                 (0U)
#define ADC_CHANNEL_ADC4_MUX3                 (0U)
#define ADC_CHANNEL_ADC4_MUX2                 (1U)
#define ADC_CHANNEL_ADC4_MUX1                 (0U)
#define ADC_CHANNEL_ADC4_MUX0                 (0U)

/* ADC operating mode */

#define ADC_ENABLE_VALUE                      (1U)
#define ADC_DISABLE_AUTO_TRIGGER              (0U)
#define ADC_ENABLE_INTERRUPT                  (1U)
#define ADC_START_CONVERSION_VALUE            (1U)

/* ADC prescaler: ADPS[2:0] = 000 */

#define ADC_PRESCALER_BIT_2                   (0U)
#define ADC_PRESCALER_BIT_1                   (0U)
#define ADC_PRESCALER_BIT_0                   (0U)

/* ADC trigger source: none */

#define ADC_TRIGGER_SOURCE_BIT_2              (0U)
#define ADC_TRIGGER_SOURCE_BIT_1              (0U)
#define ADC_TRIGGER_SOURCE_BIT_0              (0U)

/* Private module variables */

static volatile adc_uint8_t adc_conversion_result;
static volatile adc_uint8_t adc_result_state;

/*
IAR header-ul proiectului expune registrul ADC ca registru de 16 biti.

Pentru ADLAR = 1, cei mai semnificativi 8 biti reprezinta
continutul registrului ADCH. Expresia ADC >> 8 este echivalenta
cu citirea valorii din ADCH.
*/

#define ADC_HIGH_BYTE_SHIFT                   (8U)

/* ADC interrupt service routine */

#pragma vector=ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    adc_conversion_result = (adc_uint8_t)(
        ADC >> ADC_HIGH_BYTE_SHIFT
    );

    adc_result_state = ADC_RESULT_READY;
}

/* Public functions */

void adc_initialize(void)
{
    adc_conversion_result = 0U;
    adc_result_state = ADC_RESULT_NOT_READY;

    /*
    Selecteaza AVCC ca referinta:
    REFS1:0 = 01.
    */

    ADMUX_REFS1 = ADC_REFERENCE_AVCC_REFS1;
    ADMUX_REFS0 = ADC_REFERENCE_AVCC_REFS0;

    /*
    Rezultatul este aliniat la stanga.
    Astfel este suficienta citirea octetului high.
    */

    ADMUX_ADLAR = ADC_RESULT_LEFT_ADJUSTED;

    /*
    Selecteaza intrarea single-ended ADC4:
    MUX[4:0] = 00100.
    */

    ADMUX_MUX4 = ADC_CHANNEL_ADC4_MUX4;
    ADMUX_MUX3 = ADC_CHANNEL_ADC4_MUX3;
    ADMUX_MUX2 = ADC_CHANNEL_ADC4_MUX2;
    ADMUX_MUX1 = ADC_CHANNEL_ADC4_MUX1;
    ADMUX_MUX0 = ADC_CHANNEL_ADC4_MUX0;

    /*
    Nu se foloseste auto-trigger.
    ADC-ul functioneaza in Single Conversion Mode.
    */

    ADCSRA_ADATE = ADC_DISABLE_AUTO_TRIGGER;

    ADCSRB_ADTS2 = ADC_TRIGGER_SOURCE_BIT_2;
    ADCSRB_ADTS1 = ADC_TRIGGER_SOURCE_BIT_1;
    ADCSRB_ADTS0 = ADC_TRIGGER_SOURCE_BIT_0;

    /*
    Prescaler-ul ramane pe configuratia simpla ceruta:
    ADPS[2:0] = 000.
    */

    ADCSRA_ADPS2 = ADC_PRESCALER_BIT_2;
    ADCSRA_ADPS1 = ADC_PRESCALER_BIT_1;
    ADCSRA_ADPS0 = ADC_PRESCALER_BIT_0;

    /* Activeaza intreruperea ADC. */

    ADCSRA_ADIE = ADC_ENABLE_INTERRUPT;

    /*
    Activeaza perifericul ADC.
    Pornirea conversiei se face separat, dupa configurare.
    */

    ADCSRA_ADEN = ADC_ENABLE_VALUE;

    /* Activeaza global intreruperile. */

    __enable_interrupt();
}

void adc_start_conversion(void)
{
    adc_result_state = ADC_RESULT_NOT_READY;

    /*
    Scrierea valorii 1 in ADSC porneste o conversie.
    Bitul este resetat automat la terminarea conversiei.
    */

    ADCSRA_ADSC = ADC_START_CONVERSION_VALUE;
}

adc_uint8_t adc_is_result_ready(void)
{
    return adc_result_state;
}

adc_uint8_t adc_get_result(void)
{
    adc_uint8_t adc_result_copy;

    __disable_interrupt();

    adc_result_copy = adc_conversion_result;
    adc_result_state = ADC_RESULT_NOT_READY;

    __enable_interrupt();

    return adc_result_copy;
}

#endif