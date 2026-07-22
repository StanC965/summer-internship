#ifndef ADC_H
#define ADC_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  ADC channel of the light sensor (PA4 = ADC4) */
#define ADC_LIGHT_CHANNEL   (4U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Initialize the ADC: AVCC reference, left aligned result (read ADCH),
            selected channel, conversion complete interrupt enabled.
            For low power the digital input buffer of the analog pin is disabled
            and the ADC is left OFF .
    \param[in]  channel  ADC channel to read (0 .. 7)
*/
extern void adc_init(unsigned char channel);

/** \brief  Power the ADC up (set ADEN); call it right before a conversion */
extern void adc_enable(void);

/** \brief  Power the ADC down (clear ADEN) to save current between conversions */
extern void adc_disable(void);

/** \brief  Start one single ADC conversion */
extern void adc_start_conversion(void);

/** \brief  Get the last 8-bit conversion result
    \return  the light value, 0 .. 255
*/
extern unsigned char adc_get_result(void);

#endif
