/**
 * @file adc.h
 * @brief Header file for Analog-to-Digital Converter (ADC) peripheral driver.
 * @details Defines hardware register bit mappings, resolution types, and public interfaces.
 */

#ifndef ADC_H
#define ADC_H

#include <iom324pb.h>

#if !defined(ADC_RESOLUTION_8_BIT) && !defined(ADC_RESOLUTION_10_BIT)
    /** @brief Default to 10-bit resolution if resolution mode is unspecified */
    #define ADC_RESOLUTION_10_BIT
#endif

#if defined(ADC_RESOLUTION_8_BIT)
    /** @brief Data type for 8-bit ADC readings */
    typedef unsigned char adc_result_t;
    /** @brief Maximum step value for 8-bit resolution calculations */
    #define ADC_MAX_VAL              255
#elif defined(ADC_RESOLUTION_10_BIT)
    /** @brief Data type for 10-bit ADC readings */
    typedef unsigned int adc_result_t;
    /** @brief Maximum step value for 10-bit resolution calculations */
    #define ADC_MAX_VAL              1023
#endif

/** @name ADC Hardware Configuration Bit Definitions */
/**@{*/
#define ADC_LIGHT_SENSOR_CHANNEL     4  
#define ADC_LEFT_ADJUST              5  
#define ADC_REFS_AVCC                6
#define ADC_REFS_1V                  7

#define ADC_PRESCALE_DIV_128         7 
#define ADC_INT_ENABLE               3   
#define ADC_START                    6   
#define ADC_ENABLE                   7

#define ADC_DIGITAL_INPUT_DISABLE    4
/**@}*/

/**
 * @brief Initializes the ADC peripheral.
 * @details Configures standard 128x prescaling, voltage reference source, resolution alignment, 
 *          and enables ADC conversion complete interrupts.
 * @param adc_channel_pin The analog multiplexer channel pin (0-31) to configure.
 */
void adc_init(unsigned char adc_channel_pin);

/**
 * @brief Triggers a single-ended ADC conversion on the active multiplexer channel.
 */
void adc_start_conversion(void);

/**
 * @brief Disables the ADC peripheral core to reduce power consumption.
 */
void adc_power_down(void);

/**
 * @brief Directly reads the current ADC conversion result registers (ADCH/ADC).
 * @return Raw conversion value as \ref adc_result_t (8-bit or 10-bit dependent on build flags).
 */
adc_result_t adc_get_result(void);

/**
 * @brief Public interface to retrieve the cached, inverted light level result.
 * @return Latest processed ADC value written by the interrupt service routine.
 */
adc_result_t adc_get_data(void);

#endif