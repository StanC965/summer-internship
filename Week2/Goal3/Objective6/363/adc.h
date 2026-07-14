#ifndef ADC_H
#define ADC_H

#include <iom324pb.h>

#define ADC_LIGHT_SENSOR_CHANNEL     4  
#define ADC_LEFT_ADJUST              5  
#define ADC_REFS_AVCC                6
#define ADC_REFS_1V                  7

#define ADC_PRESCALER_0              0   
#define ADC_PRESCALER_1              1   
#define ADC_PRESCALER_2              2   
#define ADC_INT_ENABLE               3   
#define ADC_START                    6   
#define ADC_ENABLE                   7

#define ADC_DIGITAL_INPUT_DISABLE    4

/** \fn     void adc_init(unsigned char adc_channel_pin)
    \brief  Initializes the analog-to-digital converter peripheral mode with standard 128x prescaling, 8-bit left alignment, and interrupt mapping.
*/
void adc_init(unsigned char adc_channel_pin);

/** \fn     void adc_start_conversion(void)
    \brief  Triggers a single-ended conversion on the previously selected multiplexer channel.
*/
void adc_start_conversion(void);

/** \fn     unsigned char adc_get_result(void)
    \brief  Reads the left-adjusted conversion output.
    \return 8-bit digital resolution sample (ADCH).
*/
unsigned char adc_get_result(void);

/** \fn     void adc_power_down(void)
    \brief  Disables the ADC peripheral core to eliminate standby current consumption.
*/
void adc_power_down(void);

#endif