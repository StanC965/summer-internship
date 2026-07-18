#ifndef ADC_H
#define ADC_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific constant number zero */
#define BIT_MASK(bit_position)        (1 << bit_position)
/** \brief  Module specific constant number one */
#define ADC_REFERENCE_MASK            (BIT_MASK(REFS1) | BIT_MASK(REFS0))
/** \brief  Module specific constant number two */
#define ADC_CHANNEL_MASK              (BIT_MASK(MUX3) | BIT_MASK(MUX2) | BIT_MASK(MUX1) | BIT_MASK(MUX0))
/** \brief  Module specific constant number three */
#define ADC_PRESCALER_64_MASK         (BIT_MASK(ADSP2) | BIT_MASK(ADSP1) | BIT_MASK(ADSP0))
/** \brief  Module specific constant number four */
#define ADC_PRESCALER_64_DIVISON_MASK (BIT_MASK(ADSP2) | BIT_MASK(ADSP1))
/** \brief  Module specific constant number five */
#define CHANNEL_4                     4
/* ADMUX - ADC Multiplexer Selection Register */
#define MUX0                          0
#define MUX1                          1
#define MUX2                          2
#define MUX3                          3
#define MUX4                          4
#define REFS0                         6
#define REFS1                         7

#define ADSP0                         0
#define ADSP1                         1
#define ADSP2                         2

#define ADEN                          7
#define ADIE                          1

#define ADLAR                         5
#define ADSC                          6
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void adc_init(void)

    \brief      [ Initializes the ADC module. ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Performs all necessary initialization steps for the ADC module. ]
*/
extern void adc_init(void);

/** \fn     void adc_select_avcc_voltage(void)

    \brief      [  ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [  ]
*/
extern void adc_select_avcc_voltage(void);

/** \fn     void adc_select_internal_voltage(void)

    \brief      [  ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [  ]
*/
extern void adc_select_internal_voltage(void);

/** \fn     void adc_select_input_channel(uint8_t channel)

    \brief      [  ]
    \param[in]  channel [ channel number ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_select_input_channel(uint8_t channel);

/** \fn     void adc_configure_control_settings(void)

    \brief      [  ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_configure_control_settings(void);

/** \fn     adc_set_prescaler_64(void)

    \brief      [  ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_set_prescaler_64(void);

/** \fn    adc_enable_interrupt(void)

    \brief      [  ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_enable_interrupt(void);

/** \fn    adc_enable(void)

    \brief      [  ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_enable(void);

/** \fn     void adc_disable_digital_input(uint8_t channel)

    \brief      [  ]
    \param[in]  channel [ channel number ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_disable_digital_input(uint8_t channel);

/** \fn     void adc_trigger_conversion(void)

    \brief      [  ]
    \param[in]  channel [ channel number ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ . ]
*/
extern void adc_trigger_conversion(void);

#endif /* ADC_H */