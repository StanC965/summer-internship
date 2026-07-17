#ifndef TIMER_H
#define TIMER_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/** \brief COUNTER VALUE */
#define COUNTER_VALUE            (1250)

/** \brief bitmask pentru a seta TCCR1A si TCCR1B pe normal mode*/
#define NORMAL_MODE_FOR_A          0
#define NORMAL_MODE_FOR_B          0

/** \brief bitmask pentru a seta TCCR1A si TCCR1B pe CTC*/
#define CTC_FOR_A                  0x00
#define CTC_FOR_B                  0x08

/** \brief bitmask pentru a seta TCCR1A si TCCR1B pe PWM phase correct cu OCR1A */
#define PWM_PHASE_CORRECT_FOR_A    0x03
#define PWM_PHASE_CORRECT_FOR_B    0x10

/** \brief bitmask pentru a seta TCCR1A si TCCR1B pe fast PWM */
#define FAST_PWM_FOR_A             0x03
#define FAST_PWM_FOR_B             0x18

/** \brief bitmask pentru a seta  TCCR1B pe prescale 0 */
#define TCCR1B_PRESCALE_0          0x00

/** \brief bitmask pentru a seta  TCCR1B pe prescale 1 */
#define TCCR1B_PRESCALE_1          0x01

/** \brief bitmask pentru a seta  TCCR1B pe prescale 8 */
#define TCCR1B_PRESCALE_8          0x02

/** \brief bitmask pentru a seta  TCCR1B pe prescale 64 */
#define TCCR1B_PRESCALE_64          0x03

/** \brief bitmask pentru a seta  TCCR1B pe prescale 256 */
#define TCCR1B_PRESCALE_256          0x04

/** \brief bitmask pentru a seta  TCCR1B pe prescale 1024 */
#define TCCR1B_PRESCALE_1024          0x05




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void TIMER1_INIT_10ms()

    \brief      [Se configureaza timer 1 pe 10 ms]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe 10 ms]
*/
extern void TIMER1_INIT_10ms();

/** \fn     void timer_Prescale_0_TC1()

    \brief      [Se configureaza timer 1 pe prescale 0]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe prescale 0]
*/
extern void timer_Prescale_0_TC1();

/** \fn     void timer_Prescale_0_TC1()

    \brief      [Se configureaza timer 1 pe prescale 8]  
    \param[in]  [ none]
    \param[out] [ void]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe prescale 8]
*/
extern void timer_Prescale_1_TC1();

/** \fn     void timer_Prescale_8_TC1()

    \brief      [Se configureaza timer 1 pe prescale 8]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe prescale 8]
*/
extern void timer_Prescale_8_TC1();

/** \fn     void timer_Prescale_64_TC1()

    \brief      [Se configureaza timer 1 pe prescale 64]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe prescale 64]
*/
extern void timer_Prescale_64_TC1();

/** \fn     void timer_Prescale_256_TC1()

    \brief      [Se configureaza timer 1 pe prescale 256]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe prescale 256]
*/
extern void timer_Prescale_256_TC1();


/** \fn     void timer_Prescale_1024_TC1()

    \brief      [Se configureaza timer 1 pe prescale 1024]  
    \param[in]  [ none]
    \param[out] [void  ]
    \return     [ none]
    \details    [functia se ocupa de configurarea lui tc1 pe prescale 1024]
*/
extern void timer_Prescale_1024_TC1();

/** \fn     _Bool Timer1_ales_exact_8Mhz(float milisecunde)

    \brief      [Se configureaza timer 1 pe o perioada aleasa]  
    \param[in]  [ float timp]
    \param[out] [ OCR1A +prescaler ]
    \return     [ BOOLEAN]
    \details    [functia se ocupa de configurarea lui tc1 pe o perioada aleasa exact, adica care nu poate avea desincronizari, daca nu exista nicio varianta 
      fara desincronizari, functia intoarce false]
*/
extern _Bool Timer1_ales_exact_8Mhz(float milisecunde);

/** \fn     _Bool Timer1_ales_aprox_8Mhz(float milisecunde)

    \brief      [Se configureaza timer 1 pe o perioada aleasa]  
    \param[in]  [ float timp]
    \param[out] [ OCR1A +prescaler ]
    \return     [ BOOLEAN]
    \details    [functia se ocupa de configurarea lui tc1 pe o perioada aleasa aproximativa, adica se cauta daca exista o valoare exacta ,daca nu, se determina
                 cea mai mica desincronizare si aia se alege]
*/
extern void Timer1_ales_aprox_8Mhz(float milisecunde);

#endif