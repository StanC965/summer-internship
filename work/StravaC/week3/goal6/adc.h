#ifndef ADC_H
#define ADC_H

typedef unsigned char adc_uint8_t;
typedef unsigned int adc_uint16_t;

#define ADC_DATA_NOT_READY    (0U)
#define ADC_DATA_READY        (1U)

extern void adc_init(void);

extern void adc_start_conversion(void);

extern adc_uint8_t adc_is_data_ready(void);

extern adc_uint16_t adc_get_data(void);

#endif