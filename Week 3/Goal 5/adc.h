#ifndef ADC_H
#define ADC_H

void adc_init(void);
void adc_start_conversion(void);
unsigned char adc_get_data(void);

#endif