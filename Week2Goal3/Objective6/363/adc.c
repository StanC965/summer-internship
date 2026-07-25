#ifndef ADC_C
#define ADC_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "adc.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* ADMUX bits */
#define ADC_REFS0_BIT   (6U)
#define ADC_ADLAR_BIT   (5U)

/* ADCSRA bits */
#define ADC_ADEN_BIT    (7U)
#define ADC_ADSC_BIT    (6U)
#define ADC_ADIE_BIT    (3U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void adc_init(unsigned char channel)
{
    ADMUX = (1 << ADC_REFS0_BIT) | (1 << ADC_ADLAR_BIT) | (channel & 0x1F);
    DIDR0 |= (1 << channel);
    ADCSRA = (1 << ADC_ADIE_BIT);
}

void adc_enable(void)
{
    ADCSRA |= (1 << ADC_ADEN_BIT);
}

void adc_disable(void)
{
    ADCSRA &= ~(1 << ADC_ADEN_BIT);
}

void adc_start_conversion(void)
{
    ADCSRA |= (1 << ADC_ADSC_BIT);
}

unsigned char adc_get_result(void)
{
    return ADCH;
}

#endif
