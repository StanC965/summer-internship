#ifndef BUTTON_H
#define BUTTON_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/





extern volatile unsigned char debounce_buffer;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void button_configure_SW0()

    \brief      [Configureaza butonul sw0]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui sw0 ]
*/
extern void configure_SW0();

/** \fn     unsigned char button_read_sw0_safe()

    \brief      [modifica buffer-ul sw0]  
    \param[in]  [ unsigned char button_buffer]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de modificarea registrului buffer software sw0]
*/
extern unsigned char button_read_sw0_safe();


#endif