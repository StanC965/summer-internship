#ifndef ADC_H
#define ADC_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific null pointer */


/** \brief  parameter type unsigned byte (8 bit) */
typedef     unsigned char   ADC_reader_8bits;

/** \brief  parameter type unsigned word (16 bit) */
typedef     unsigned short   ADC_reader_16bits;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void adc_init_LIGHT()

    \brief      [ Aceasta functie configureaza un ADC simplu,fara prescale ,are scop doar de exercitiu ]  
*/
extern void adc_init_LIGHT();

/** \fn     void adc_start_conversie()

    \brief      [ Aceasta functie seteaza ADCSRA astfel incat sa inceapa sa faca conversia,dupa masurarea hardware-ul pune bit-ul inapoi pe 0]  
*/
extern void adc_start_conversie();

/** \fn     ADC_reader_8bits adc_adapter8()

    \brief      [ Aceasta functie  preia valoarea obtinuta de 8 bits din conversie si o inverseaza ]  
*/
extern ADC_reader_8bits adc_adapter8(ADC_reader_8bits value);

/** \fn     ADC_reader_16bits adc_adapter16()

    \brief      [ Aceasta functie  preia valoarea obtinuta de 16 bits  din conversie si o inverseaza ]  
*/
extern ADC_reader_16bits adc_adapter16(ADC_reader_16bits value);


/** \fn     void adc_get_result8()

    \brief      [ Aceasta functie  preia valoarea obtinuta din ADCH de 8 biti]  
*/
extern ADC_reader_8bits adc_get_result8();

/** \fn     ADC_reader_16bits adc_get_result16()

    \brief      [ Aceasta functie  preia valoarea obtinuta din ADCH de 16 biti]  
*/
extern ADC_reader_16bits adc_get_result16();


/** \fn     void disable_input_buffer_for_lightSensor()

    \brief      [ Aceasta functie dezactiveaza input buffer-ul din DIDR0 pentru ADC -ul responsabil de senzorul de lumina ]  
*/
extern void disable_input_buffer_for_lightSensor();

/** \fn     void enable_input_buffer_for_lightSensor()

    \brief      [ Aceasta functie activeaza input buffer-ul din DIDR0 pentru ADC -ul responsabil de senzorul de lumina ]  
*/
extern void enable_input_buffer_for_lightSensor();

#endif