#ifndef ADC_H
#define ADC_H

/*
Autor: Strava Cosmin-Paul
Data: 2026

Interfata modulului ADC.

Configuratia implicita a modulului:
- referinta AVCC;
- canal ADC4;
- intrare single-ended;
- rezultat left-adjusted;
- rezultat citit pe 8 biti;
- Single Conversion Mode;
- fara auto-trigger;
- intrerupere la finalul conversiei.

Actiunile atomice sunt:
- pornirea unei conversii;
- verificarea disponibilitatii rezultatului;
- citirea rezultatului.
*/

/* General values */

#define ADC_FALSE                   (0U)
#define ADC_TRUE                    (1U)

/* Result states */

#define ADC_RESULT_NOT_READY        (ADC_FALSE)
#define ADC_RESULT_READY            (ADC_TRUE)

/* Exported type */

typedef unsigned char adc_uint8_t;

/* Module initialization */

extern void adc_init(void);

/* Atomic ADC actions */

extern void adc_start_conversion(void);

extern adc_uint8_t adc_is_result_ready(void);

extern adc_uint8_t adc_get_result(void);

#endif