#ifndef ADC_H
#define ADC_H

#include <iom324pb.h>

#if !defined(ADC_RESOLUTION_8_BIT) && !defined(ADC_RESOLUTION_10_BIT)
    #define ADC_RESOLUTION_10_BIT
#endif

#if defined(ADC_RESOLUTION_8_BIT)
    /** \brief Map the result data type to 8-bit */
    typedef unsigned char adc_result_t;
    /** \brief Define the maximum step scale for inversion calculations */
    #define ADC_MAX_VAL              255
#elif defined(ADC_RESOLUTION_10_BIT)
    /** \brief Map the result data type to 16-bit */
    typedef unsigned int adc_result_t;
    /** \brief Define the maximum step scale for inversion calculations */
    #define ADC_MAX_VAL              1023
#endif

#define ADC_LIGHT_SENSOR_CHANNEL     4  
#define ADC_LEFT_ADJUST              5  
#define ADC_REFS_AVCC                6
#define ADC_REFS_1V                  7

#define ADC_PRESCALE_DIV_128         7 
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

/** \fn     void adc_power_down(void)
    \brief  Disables the ADC peripheral core to eliminate standby current consumption.
*/
void adc_power_down(void);

/** \fn     adc_result_t adc_get_result(void)
    \brief  Reads the conversion output using a dynamically configured return type.
    \return Returns 8-bit (unsigned char) or 10-bit (unsigned int) depending on configured compilation flags.
*/
adc_result_t adc_get_result(void);

/** \fn     adc_result_t adc_get_data(void)
    \brief  Public getter interface to access the safely encapsulated, 
            inverted light intensity value.
*/
adc_result_t adc_get_data(void);

#endif