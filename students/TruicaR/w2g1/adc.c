#include "iom324pb.h"
#include "adc.h"

#include "iom324pb.h"
#include "adc.h"

#define ADC_REF_AVCC          (1 << 6)
#define ADC_LEFT_ALIGN         (1 << 5)
#define ADC_ENABLE             (1 << 7)
#define ADC_INTERRUPT_ENABLE   (1 << 3)
#define ADC_START              (1 << 6)
#define ADC_CHANNEL_MASK       0x1F 

static volatile unsigned char adc_result = 0;

void adc_init(unsigned char channel)
{
    ADMUX = ADC_REF_AVCC | ADC_LEFT_ALIGN | (channel & ADC_CHANNEL_MASK);
    ADCSRA = ADC_ENABLE | ADC_INTERRUPT_ENABLE;
}

void adc_start_conversion(void)
{
    ADCSRA |= ADC_START;
}

unsigned char adc_get_result(void)
{
    return adc_result;
}

#pragma vector = ADC_vect
__interrupt void adc_isr(void)
{
    adc_result = ADCH;
}