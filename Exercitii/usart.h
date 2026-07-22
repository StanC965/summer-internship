#ifndef USART_H
#define USART_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define CMD_LED0_ON     0x01
#define CMD_LED0_OFF    0x02
#define CMD_LED0_TOGGLE 0x03

#define CMD_LED1_ON     0x11
#define CMD_LED1_TOGGLE 0x13

#define CMD_LED2_ON     0x21
#define CMD_LED2_TOGGLE 0x23

#define CMD_LED3_ON     0x31
#define CMD_LED3_TOGGLE 0x33



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn   void USART0_Init(unsigned int ubrr)

    \brief      [ Aceasta functie configureaza usart ]  
*/
extern void USART0_Init(unsigned int ubrr);
      

  
/** \fn    void USART0_Transmit( unsigned char data )

    \brief      [ Aceasta functie trimite un caracter]  
*/
extern void USART0_Transmit( unsigned char data );


#endif