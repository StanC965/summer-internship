#ifndef LED_H
#define LED_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Module specific constant number zero */
#define LED_ZERO            (0xAA)

/** \brief  Module specific constant number one */
#define LED_ONE             (0xBB)

/** \brief  Module specific constant number two */
#define LED_TWO             (0xCC)

/** \brief  Module specific true */
#define LED_THREE            (0xDD)

/** \brief  Module specific false */
#define LED_FOUR             (0xEE)

/** \brief  parameter type unsigned byte (8 bit) */
typedef     unsigned char   mod_uint8_t;

/** \brief  parameter type unsigned word (16 bit) */
typedef     unsigned int    mod_uint16_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void leds_initialize(_Bool led0, _Bool led1, _Bool led2, _Bool led3, _Bool led4)

    \brief      [Se alege ce led-uri sunt initializate]  
    \param[in]  [ valori boolene ]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia initializeaza toate led-urile ]
*/
extern void leds_initialize(_Bool led0, _Bool led1, _Bool led2, _Bool led3, _Bool led4);

/** \fn    void led_Set(unsigned char Led_id)

    \brief       [ functia pune bit-ul unui anumit led pe 1]  
    \param[in]   [preia o valoare predefinita corespunzatoare unui anumit led  ]
    \param[out]  [void  ]
    \return      [ none]
    \details     [functia seteaza un led pe HIGH ]
*/
extern void led_Set(unsigned char Led_id);

/** \fn    void led_Set(unsigned char Led_id)

    \brief       [ functia pune bit-ul unui anumit led pe 1]  
    \param[in]   [preia o valoare predefinita corespunzatoare unui anumit led  ]
    \param[out]  [void  ]
    \return      [ none]
    \details     [functia seteaza un led pe HIGH ]
*/
extern void led_Reset(unsigned char Led_id);

/** \fn    void led_TOGGLE(unsigned char Led_id)

    \brief       [ functia inverseaza starea unui LED anume]  
    \param[in]   [preia o valoare predefinita corespunzatoare unui anumit led  ]
    \param[out]  [void  ]
    \return      [ none]
    \details     [functia inverseaza starea unui LED ]
*/
extern void led_TOGGLE(unsigned char Led_id);

/** \fn    void led_TEST_Fast(unsigned char Led_id)

    \brief       [ functia aprinde si stinge de 6 ori intr-o secunda un LED pentru un test]  
    \param[in]   [preia o valoare predefinita corespunzatoare unui anumit led  ]
    \param[out]  [void  ]
    \return      [ none]
    \details     [functie de test ]
*/
extern void led_TEST_Fast(unsigned char Led_id);

/** \fn    void led_TEST_Slow(unsigned char Led_id)

    \brief       [ functia aprinde si stinge de 2 ori intr-o secunda un LED pentru un test]  
    \param[in]   [preia o valoare predefinita corespunzatoare unui anumit led  ]
    \param[out]  [void  ]
    \return      [ none]
    \details     [functie de test]
*/
extern void led_TEST_Slow(unsigned char Led_id);


/** \fn   void led_TEST_Blink(unsigned char Led_id, float secunde, int limite_clipiri)

    \brief       [ functia aprinde si stinge de cate ori vrem intr-o secunda un LED ]  
    \param[in]   [preia o valoare predefinita corespunzatoare unui anumit led  ]
    \param[out]  [void  ]
    \return      [ none]
    \details     [functie de test]
*/
extern void led_TEST_Blink(unsigned char Led_id, float secunde, int limite_clipiri);

#endif