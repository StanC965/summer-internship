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
            selected channel, ADC enabled, conversion complete interrupt enabled.
            The conversion is NOT started here.
    \param[in]  channel  ADC channel to read (0 .. 7)
*/
extern void adc_init(unsigned char channel);

/** \brief  Start one single ADC conversion */
extern void adc_start_conversion(void);

/** \brief  Get the last 8-bit conversion result
    \return  the light value, 0 .. 255
*/
extern unsigned char adc_get_result(void);

#endif
