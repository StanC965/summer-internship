#ifndef ADC_C
#define ADC_C

/*
Autor: Strava Cosmin-Paul
Data: 2026

Implementarea modulului ADC.

IO1 Xplained Pro este conectat la EXT4.

Traseul semnalului:
LIGHTSENSOR -> EXT4 pin 3 -> PA4 -> ADC4

Rezultatul este aliniat la stanga.
Doar cei mai semnificativi 8 biti sunt utilizati.
*/

#include "iom324pb.h"
#include "intrinsics.h"

#include "adc.h"

/* ========================================================= */
/* ADC REFERENCE CONFIGURATION                               */
/* ========================================================= */

/* REFS[1:0] = 01 -> AVCC */

#define ADC_REFERENCE_REFS1_VALUE           (0U)
#define ADC_REFERENCE_REFS0_VALUE           (1U)

/* ========================================================= */
/* ADC RESULT CONFIGURATION                                  */
/* ========================================================= */

#define ADC_LEFT_ADJUST_ENABLE              (1U)
#define ADC_HIGH_BYTE_SHIFT                 (8U)
#define ADC_RESULT_INITIAL_VALUE            (0U)

/* ========================================================= */
/* ADC CHANNEL CONFIGURATION                                 */
/* ========================================================= */

/*
ADC4:
MUX[4:0] = 00100
*/

#define ADC_CHANNEL_MUX4_VALUE              (0U)
#define ADC_CHANNEL_MUX3_VALUE              (0U)
#define ADC_CHANNEL_MUX2_VALUE              (1U)
#define ADC_CHANNEL_MUX1_VALUE              (0U)
#define ADC_CHANNEL_MUX0_VALUE              (0U)

/* ========================================================= */
/* ADC OPERATING CONFIGURATION                               */
/* ========================================================= */

#define ADC_ENABLE                          (1U)
#define ADC_AUTO_TRIGGER_DISABLE            (0U)
#define ADC_INTERRUPT_ENABLE                (1U)
#define ADC_START_CONVERSION                (1U)

/* ========================================================= */
/* ADC PRESCALER CONFIGURATION                               */
/* ========================================================= */

/*
ADPS[2:0] = 000

Aceasta este configuratia simpla ceruta de exercitiu.
*/

#define ADC_PRESCALER_ADPS2_VALUE           (0U)
#define ADC_PRESCALER_ADPS1_VALUE           (0U)
#define ADC_PRESCALER_ADPS0_VALUE           (0U)

/* ========================================================= */
/* ADC TRIGGER CONFIGURATION                                 */
/* ========================================================= */

/*
Nu se foloseste auto-trigger.
ADTS[2:0] ramane 000.
*/

#define ADC_TRIGGER_ADTS2_VALUE             (0U)
#define ADC_TRIGGER_ADTS1_VALUE             (0U)
#define ADC_TRIGGER_ADTS0_VALUE             (0U)

/* ========================================================= */
/* PRIVATE MODULE VARIABLES                                  */
/* ========================================================= */

static volatile adc_uint8_t adc_conversion_result;
static volatile adc_uint8_t adc_result_state;

/* ========================================================= */
/* ADC INTERRUPT SERVICE ROUTINE                             */
/* ========================================================= */

#pragma vector=ADC_vect
__interrupt void adc_conversion_complete_isr(void)
{
    /*
    Header-ul IAR expune ADC ca registru de 16 biti.

    Pentru ADLAR = 1, deplasarea cu 8 pozitii extrage
    octetul superior, echivalent cu citirea ADCH.
    */

    adc_conversion_result = (adc_uint8_t)(
        ADC >> ADC_HIGH_BYTE_SHIFT
    );

    adc_result_state = ADC_RESULT_READY;
}

/* ========================================================= */
/* MODULE INITIALIZATION                                     */
/* ========================================================= */

void adc_init(void)
{
    adc_conversion_result = ADC_RESULT_INITIAL_VALUE;
    adc_result_state = ADC_RESULT_NOT_READY;

    /*
    Selecteaza AVCC ca referinta:
    REFS[1:0] = 01.
    */

    ADMUX_REFS1 = ADC_REFERENCE_REFS1_VALUE;
    ADMUX_REFS0 = ADC_REFERENCE_REFS0_VALUE;

    /*
    Rezultatul este aliniat la stanga.
    */

    ADMUX_ADLAR = ADC_LEFT_ADJUST_ENABLE;

    /*
    Selecteaza canalul single-ended ADC4.
    */

    ADMUX_MUX4 = ADC_CHANNEL_MUX4_VALUE;
    ADMUX_MUX3 = ADC_CHANNEL_MUX3_VALUE;
    ADMUX_MUX2 = ADC_CHANNEL_MUX2_VALUE;
    ADMUX_MUX1 = ADC_CHANNEL_MUX1_VALUE;
    ADMUX_MUX0 = ADC_CHANNEL_MUX0_VALUE;

    /*
    Dezactiveaza auto-trigger.
    Conversiile vor fi pornite doar prin software.
    */

    ADCSRA_ADATE = ADC_AUTO_TRIGGER_DISABLE;

    /*
    Selectia triggerului ramane pe valoarea implicita.
    */

    ADCSRB_ADTS2 = ADC_TRIGGER_ADTS2_VALUE;
    ADCSRB_ADTS1 = ADC_TRIGGER_ADTS1_VALUE;
    ADCSRB_ADTS0 = ADC_TRIGGER_ADTS0_VALUE;

    /*
    Configureaza prescaler-ul.
    */

    ADCSRA_ADPS2 = ADC_PRESCALER_ADPS2_VALUE;
    ADCSRA_ADPS1 = ADC_PRESCALER_ADPS1_VALUE;
    ADCSRA_ADPS0 = ADC_PRESCALER_ADPS0_VALUE;

    /*
    Activeaza intreruperea ADC Conversion Complete.
    */

    ADCSRA_ADIE = ADC_INTERRUPT_ENABLE;

    /*
    Activeaza perifericul ADC.

    Pornirea conversiei nu se face aici.
    Aceasta este o actiune atomica separata.
    */

    ADCSRA_ADEN = ADC_ENABLE;
}

/* ========================================================= */
/* ATOMIC ADC ACTIONS                                        */
/* ========================================================= */

void adc_start_conversion(void)
{
    adc_result_state = ADC_RESULT_NOT_READY;

    /*
    Scrierea valorii 1 in ADSC porneste conversia.
    ADSC este resetat automat de hardware la final.
    */

    ADCSRA_ADSC = ADC_START_CONVERSION;
}

adc_uint8_t adc_is_result_ready(void)
{
    return adc_result_state;
}

adc_uint8_t adc_get_result(void)
{
    adc_uint8_t adc_result_copy;

    /*
    Variabila este modificata de ISR.
    Se foloseste o sectiune critica scurta.
    */

    __disable_interrupt();

    adc_result_copy = adc_conversion_result;
    adc_result_state = ADC_RESULT_NOT_READY;

    __enable_interrupt();

    return adc_result_copy;
}

#endif