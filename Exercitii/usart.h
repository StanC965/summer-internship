#ifndef USART_H
#define USART_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifdef ADC_USE_8_BIT_RESOLUTION  
typedef unsigned char ADC_result;
#else
typedef unsigned short ADC_result;
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn    void USART_Init( unsigned int ubrr)

    \brief      [ Aceasta functie configureaza usart ]  
*/
extern void USART_Init( unsigned int ubrr);
      

  
/** \fn    void USART_Transmit( unsigned char data )

    \brief      [ Aceasta functie trimite un caracter]  
*/
extern void USART_Transmit( unsigned char data );


#endif