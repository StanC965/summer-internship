#ifndef TIMER_H
#define TIMER_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Macro utility to generate a bit mask for a specific bit position */
#define BIT_MASK(bit_position)        (1 << bit_position)

#define TCCR0B_CS_MASK                (0x07U)
#define TIMER_PRESCALER_NO_DIVISION   (0X01U)
#define TIMER0_CTC_TARGET             (127U)
#define TIMER_PRESCALER_64            (0X03U)
#define TIMER0_PRELOAD_VALUE          (131U)
#define OVERFLOWS_PER_SECOND          (125U)
#define PRTIM0                        5
#define PRTIM1                        3
#define TOIE0                         0
#define WGM01                         1
#define WGM12                         3
#define OCIE0A                        1
#define OCIE1A                        1
#define COM0A0                        6
#define COM1A0                        6
#define CS11                          1

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      void timer_init(void)
    \brief   [ Initializes the ADC module. ]
    \param   [ None ] 
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
             configuring initial references and control registers. ]
*/
extern void timer_init(void);

/** \fn      void timer_enable_peripheral_clock(void)
    \brief   [ Initializes the ADC module. ]
    \param   [ None ] 
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
             configuring initial references and control registers. ]
*/
extern void timer_enable_peripheral_clock(void);

/** \fn      void timer_select_normal_mode(void)
    \brief   [ Initializes the ADC module. ]
    \param   [ None ] 
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
             configuring initial references and control registers. ]
*/
extern void timer_select_normal_mode(void);

/** \fn      void timer_configure_control_settings(void)
    \brief   [ Initializes the ADC module. ]
    \param   [ None ] 
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
             configuring initial references and control registers. ]
*/
extern void timer_configure_control_settings(void);

/** \fn      void timer_enable_overflow_interrupt()
    \brief   [ Initializes the ADC module. ]
    \param   [ None ] 
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
             configuring initial references and control registers. ]
*/
extern void timer_enable_overflow_interrupt(void);

extern void timer_start_no_prescaling(void);

extern void timer_start_prescaler_64(void);

extern void timer_init_ctc(void);

extern void timer_select_ctc_mode(void);

extern void timer_configure_ctc_settings(void);

extern void timer_enable_overflow_interrupt(void);

extern void timer_enable_compare_a_interrupt(void);

extern void timer1_enable_compare_a_interrupt(void);

extern void timer1_init_ctc_100ms(void);

extern void timer1_enable_peripheral_clock(void);

#endif /* TIMER_H */

