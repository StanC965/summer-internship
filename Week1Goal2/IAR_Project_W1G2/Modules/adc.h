#ifndef ADC_H
#define ADC_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       adc.h
 *  \brief      ADC Driver module interface.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <iom324pb.h>
   
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Bit masks */ 
#define REFS0  6
#define ADLAR  5
#define ADEN   7
#define ADSC   6
#define ADIE   3

/** \brief  ADC last result */   
extern volatile unsigned char adc_last_result;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void adc_init(void)
    \brief      Initializes the ADC module based on default configuration.
    \param[in]  None.
    \param[out] None.
    \return     None.
    \details    VREF = AVCC, Left Aligned (ADCH read only), Single Ended Input, 
                Interrupts Enabled, No prescaler.
*/
extern void adc_init(void);

/** \fn     void adc_start_conversion(void)
    \brief      Triggers a single ADC conversion.
    \param[in]  None.
    \param[out] None.
    \return     None.
    \details    Triggers a single ADC conversion.
*/
extern void adc_start_conversion(void);

/** \fn     unsigned char adc_get_result(void)
    \brief      Returns the last successful conversion result.
    \param[in]  None.
    \param[out] None.
    \return     8-bit ADC value (from ADCH).
    \details    Returns the last successful conversion result.
*/
extern unsigned char adc_get_result(void);

#endif /* ADC_H */