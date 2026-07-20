#ifndef BUTTON_H
#define BUTTON_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/





extern volatile unsigned char debounce_buffer;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  



/** \fn     void buttons_initialize(_Bool bttn1, _Bool bttn2, _Bool bttn3, _Bool SW0)

    \brief      [initializeaza la alegere cele 4 butoane si le seteaza sa fie active-low]  
    \param[in]  [ 4_Bool parameters]
    \param[out] [void  ]
    \return     [ none]
    \details    []
*/
extern void buttons_initialize(_Bool bttn1, _Bool bttn2, _Bool bttn3, _Bool SW0);

/** \fn   void button_update_all(void)

    \brief      [Preia fiecare din cele 4 butoane si modifica parametrii astfel incat sa se semnaleze apasarea unui buton pe baza unui buffer deinput]  
    \param[in]  [ 4_Bool parameters]
    \param[out] [void  ]
    \return     [ none]
    \details    []
*/
extern void button_update_all(void);

/** \fn  unsigned char button_get_press_sw0(void)  

    \brief      [pe baza unei variabile care se modifica in functie de schimbarea dintr-o stare  a butonului in alta se returneaza o valoare]  
    \param[in]  [ 4_Bool parameters]
    \param[out] [void  ]
    \return     [ none]
    \details    []
*/
extern unsigned char button_get_press_sw0(void) ; 

/** \fn  unsigned char button_get_press_bttn1(void) 

    \brief      [pe baza unei variabile care se modifica in functie de schimbarea dintr-o stare  a butonului in alta se returneaza o valoare]  
    \param[in]  [ 4_Bool parameters]
    \param[out] [void  ]
    \return     [ none]
    \details    []
*/
extern unsigned char button_get_press_bttn1(void) ; 

/** \fn  unsigned char button_get_press_bttn2(void) 

    \brief      [pe baza unei variabile care se modifica in functie de schimbarea dintr-o stare  a butonului in alta se returneaza o valoare]  
    \param[in]  [ 4_Bool parameters]
    \param[out] [void  ]
    \return     [ none]
    \details    []
*/
extern unsigned char button_get_press_bttn2(void) ;  


/** \fn  unsigned char button_get_press_bttn3(void) 

    \brief      [pe baza unei variabile care se modifica in functie de schimbarea dintr-o stare  a butonului in alta se returneaza o valoare]  
    \param[in]  [ 4_Bool parameters]
    \param[out] [void  ]
    \return     [ none]
    \details    []
*/
extern unsigned char button_get_press_bttn3(void) ; 




#endif