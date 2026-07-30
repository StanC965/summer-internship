#ifndef ADC_H
#define ADC_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata publica a modulului ADC.

Rezultatul conversiei este ascuns in adc.c.
Alte module il pot accesa numai prin adc_get_data().
*/

#define ADC_FALSE                       (0U)
#define ADC_TRUE                        (1U)

#define ADC_DATA_NOT_READY              (ADC_FALSE)
#define ADC_DATA_READY                  (ADC_TRUE)

#define ADC_CONVERSION_NOT_RUNNING      (ADC_FALSE)
#define ADC_CONVERSION_RUNNING          (ADC_TRUE)

typedef unsigned char adc_uint8_t;

extern void adc_init(void);

extern void adc_start_conversion(void);

extern adc_uint8_t adc_is_data_ready(void);

extern adc_uint8_t adc_is_conversion_running(void);

extern adc_uint8_t adc_get_data(void);

#endif