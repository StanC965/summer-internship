#ifndef ADC_H
#define ADC_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului ADC.

IO1 Xplained Pro este conectat la EXT4.
Semnalul senzorului de lumina ajunge la PA4 / ADC4.

Rezultatul este aliniat la stanga si este citit pe 8 biti.
*/

#define ADC_FALSE                    (0U)
#define ADC_TRUE                     (1U)

#define ADC_RESULT_NOT_READY         (ADC_FALSE)
#define ADC_RESULT_READY             (ADC_TRUE)

typedef unsigned char adc_uint8_t;

extern void adc_initialize(void);

extern void adc_start_conversion(void);

extern adc_uint8_t adc_is_result_ready(void);

extern adc_uint8_t adc_get_result(void);

#endif