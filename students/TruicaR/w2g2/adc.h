#ifndef ADC_H
#define ADC_H

void adc_init(unsigned char channel);
void adc_start_conversion(void);
unsigned char adc_get_result(void);

#endif