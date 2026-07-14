#ifndef ADC_H
#define ADC_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific null pointer */

/*
 \brief  parameter type unsigned byte (8 bit) 
typedef     unsigned char   ADC_result;

 \brief  parameter type unsigned word (16 bit) 
typedef     unsigned short   ADC_reader_16bits;
*/
#ifdef ADC_USE_8_BIT_RESOLUTION  
typedef unsigned char ADC_result;
#else
typedef unsigned short ADC_result;
#endif

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

/** \fn     ADC_result adc_adapter()

    \brief      [ Aceasta functie  preia valoarea obtinuta de 8 bits sau 16 bits  din conversie si o inverseaza ]  
*/
extern ADC_result adc_adapter8(ADC_result value);



/** \fn     void adc_get_result()

    \brief      [ Aceasta functie  preia valoarea obtinuta din ADCH de 8 biti sau 16 biti]  
*/
extern ADC_result adc_get_result();


extern void disable_input_buffer_for_lightSensor();

/** \fn     void enable_input_buffer_for_lightSensor()

    \brief      [ Aceasta functie activeaza input buffer-ul din DIDR0 pentru ADC -ul responsabil de senzorul de lumina ]  
*/
extern void enable_input_buffer_for_lightSensor();

#endif