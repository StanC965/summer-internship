#ifndef ADC_H
#define ADC_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>
#include "bits.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* ADMUX - ADC Multiplexer Selection Register */
#define MUX0                          0
#define MUX1                          1
#define MUX2                          2
#define MUX3                          3
#define MUX4                          4
#define REFS0                         6
#define REFS1                         7
#define ADLAR                         5

/** \brief  Bit mask covering the reference voltage selection bits */
#define ADC_REFERENCE_MASK            (BIT_MASK(REFS1) | BIT_MASK(REFS0))

/** \brief  Bit mask covering the channel selection bits */
#define ADC_CHANNEL_MASK              (BIT_MASK(MUX3) | BIT_MASK(MUX2) | BIT_MASK(MUX1) | BIT_MASK(MUX0))

/* ADCSRA - ADC Control and Status Register A bits */
#define ADSP0                         0
#define ADSP1                         1
#define ADSP2                         2
#define ADIE                          3
#define ADSC                          6
#define ADEN                          7

/** \brief  Bit mask covering all ADC prescaler selection bits */
#define ADC_PRESCALER_64_MASK         (BIT_MASK(ADSP2) | BIT_MASK(ADSP1) | BIT_MASK(ADSP0))

/** \brief  Division configuration mask targeting a clock prescaler factor of 64 */
#define ADC_PRESCALER_64_DIVISON_MASK (BIT_MASK(ADSP2) | BIT_MASK(ADSP1))

/** \brief  Module specific constant number one */
#define CHANNEL_4                     4

#define LIGHT_SENSOR_FULL_DARK        (255U)
#define LIGHT_SENSOR_SEMI_DARK        (170U)
#define LIGHT_SENSOR_SEMI_LIGHT       (85U)
#define LIGHT_SENSOR_FULL_LIGHT       (0U)

#define ADC_RESOLUTION_10_BIT

#ifdef ADC_RESOLUTION_10_BIT
    typedef uint16_t adc_result_t;
#else    
    typedef uint8_t adc_result_t;
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      void adc_init(void)
    \brief   [ Initializes the ADC module. ]
    \param   [ None ] 
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
             configuring initial references and control registers. ]
*/
extern void adc_init(void);

/** \fn      void adc_select_avcc_voltage(void)
    \brief   [ Selects AVCC as the reference voltage ceiling. ] 
    \param   [ None ] 
    \return  [ None ] 
    \details [ Configures ADMUX to use the VCC analog supply line. ]
*/
extern void adc_select_avcc_voltage(void);

/** \fn      void adc_select_internal_voltage(void)
    \brief   [ Selects the internal 1.1V reference voltage. ]
    \param   [ None ]
    \return  [ None ] 
    \details [ Configures ADMUX to target the internal voltage. ]
*/
extern void adc_select_internal_voltage(void);

/** \fn      void adc_select_input_channel(uint8_t channel)
    \brief   [ Selects the hardware analog input pin channel.] 
    \param   channel [ The target hardware channel index number (e.g. CHANNEL_4). ]
    \return  None
    \details [ Configures the MUX register path to connect 
               a specific analog signal pin to the conversion pipeline. ]
*/
extern void adc_select_input_channel(uint8_t channel);

/** \fn      void adc_configure_control_settings(void)
    \brief   [ Configures essential feature enables inside ADCSRA. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Groups structural enabling routines like system activation
               and enabling individual hardware interrupts. ]
*/
extern void adc_configure_control_settings(void);

/** \fn      void adc_set_prescaler_64(void)
    \brief   [ Sets the clock frequency divider division factor to 64. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Adjusts prescaling configuration to run conversions within 
               target sampling stability speeds. ]
*/
extern void adc_set_prescaler_64(void);

/** \fn      void adc_enable_interrupt(void)
    \brief   [ Enables the dedicated ADC conversion complete peripheral interrupt flag circuit. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Flipped local ADIE bits to allow execution logic to jump to
               the assigned vector handle upon processing completion. ]
*/
extern void adc_enable_interrupt(void);

/** \fn      void adc_enable(void)
    \brief   [ Powers up the underlying physical operational blocks of the ADC. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Toggles the fundamental activation bit inside the control registry block framework. ]
*/
extern void adc_enable(void);

/** \fn      void adc_disable_digital_input(uint8_t channel)
    \brief   [ Deactivates the standard digital buffer structure on an analog pin. ]
    \param   channel [ The corresponding target pin channel index. ]
    \return  [ None ]
    \details [ Isolates input lines inside DIDR0 to preserve dynamic
               power metrics by decoupling standard schmitt-triggers. ]
*/
extern void adc_disable_digital_input(uint8_t channel);

/** \fn      void adc_start_conversion(void)
    \brief   [ Fires off a brand new single conversion cycle. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Toggles the high-level ADSC runtime execution 
               register bit to grab a singular discrete system capture. ]
*/
extern void adc_start_conversion(void);

/** \fn      adc_result_t adc_get_data(void)
    \brief   [  ]
    \param   [ None ]
    \return  [ The result of the conversion (uint8_t or uint16_t).  ]
    \details [  ]
*/
extern adc_result_t adc_get_data(void);

/** \fn      void adc_set_conversion_result(void)
    \brief   [  ]
    \param   [  ]
    \return  [  ]
    \details [  ]
*/
extern void adc_set_conversion_result(void);

#endif /* ADC_H */