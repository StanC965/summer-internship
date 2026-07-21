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

/** \brief  Bit mask covering the CS0[2:0] clock select bits in TCCR0B */
#define TCCR0B_CS_MASK                (0x07U)

/** \brief  CS0[2:0] configuration for Timer0 running with no prescaling (clk/1) */
#define TIMER0_PRESCALER_NO_DIVISION  (0X01U)

/** \brief  OCR0A target value used for the CTC mode compare-match exercises */
#define TIMER0_CTC_TARGET             (127U)

/** \brief  CS0[2:0] configuration for Timer0 running with a /64 prescaler */
#define TIMER0_PRESCALER_64           (0X03U)

/** \brief  Module specific constant number zero */
#define TIMER0_PRELOAD_VALUE          (131U)

/** \brief  Module specific constant number one */
#define OVERFLOWS_PER_SECOND          (125U)

/** \brief  Module specific constant number two */
#define TIMER1_100MS_OCR1A_VALUE      (6249U)

/** \brief  Module specific constant number three */
#define TIMER1_10MS_OCR1A_VALUE       (19999U)

/** \brief  Module specific constant number four */
#define TIMER1_AIRBAG_OCR1A_VALUE     (724U)

/* PRR0 - Power Reduction Register 0 */
#define PRTIM0                        5   
#define PRTIM1                        3   

/* TIMSK0 - Timer/Counter0 Interrupt Mask Register */
#define TOIE0                         0   
#define OCIE0A                        1  

/* TIMSK1 - Timer/Counter1 Interrupt Mask Register */
#define OCIE1A                        1  
#define TOIE1                         0  

/* TCCR0A - Timer/Counter0 Control Register A */
#define WGM00                         0   
#define WGM01                         1   
#define COM0A0                        6   
#define COM0A1                        7  

/* TCCR1B - Timer/Counter1 Control Register B */
#define CS00                          0   

/* TCCR1A - Timer/Counter1 Control Register A */
#define COM1B1                        5
#define COM1A0                        6   
#define COM1A1                        7  
#define WGM11                         1

/* TCCR1B - Timer/Counter1 Control Register B */
#define WGM12                         3   
#define WGM13                         4  
#define CS10                          0   
#define CS11                          1   

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      void timer0_init(void)
    \brief   [ Initializes Timer/Counter0 in Normal mode. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Enables the Timer0 peripheral clock, selects Normal mode of
             operation, and configures the overflow interrupt so an
             interrupt request is raised every time TCNT0 wraps from
             0xFF back to 0x00. ]
*/
extern void timer0_init(void);

/** \fn      void timer0_enable_peripheral_clock(void)
    \brief   [ Enables the clock to the Timer/Counter0 peripheral. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Clears the PRTIM0 bit in the Power Reduction Register so
             Timer/Counter0 can operate. ]
*/
extern void timer0_enable_peripheral_clock(void);

/** \fn      void timer0_select_normal_mode(void)
    \brief   [ Configures Timer/Counter0 for Normal mode of operation. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Clears TCCR0A so WGM0[1:0] = 00, selecting Normal mode
             (free-running counter from 0x00 to 0xFF with overflow). ]
*/
extern void timer0_select_normal_mode(void);

/** \fn      void timer0_configure_control_settings(void)
    \brief   [ Applies the remaining Normal mode setup for Timer/Counter0. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Preloads TCNT0 with TIMER0_PRELOAD_VALUE so overflow occurs
             after a reduced number of counts, and enables the overflow
             interrupt. ]
*/
extern void timer0_configure_control_settings(void);

/** \fn      void timer0_enable_overflow_interrupt(void)
    \brief   [ Enables the Timer/Counter0 overflow interrupt. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets TOIE0 in TIMSK0 so a TIMER0_OVF interrupt request is
             raised whenever TCNT0 overflows. ]
*/
extern void timer0_enable_overflow_interrupt(void);

/** \fn      void timer0_start_no_prescaling(void)
    \brief   [ Starts Timer/Counter0 with no clock division. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets CS0[2:0] in TCCR0B so the timer counts at the full
             system clock frequency (F_CPU). Starting the clock source
             is what actually starts the timer counting, so this should
             be called last, after all other Timer0 settings are in
             place. ]
*/
extern void timer0_start_no_prescaling(void);

/** \fn      void timer0_start_prescaler_64(void)
    \brief   [ Starts Timer/Counter0 with a /64 clock prescaler. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets CS0[2:0] in TCCR0B so the timer counts at F_CPU / 64.
             As with timer_start_no_prescaling, this should be the last
             call after all other Timer0 settings are configured. ]
*/
extern void timer0_start_prescaler_64(void);

/** \fn      void timer0_init_ctc(void)
    \brief   [ Initializes Timer/Counter0 in CTC mode. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Enables the Timer0 peripheral clock, selects CTC mode of
             operation, and configures the compare match settings so an
             interrupt request (and, if COM0A0 is set, a toggle of the
             OC0A pin) occurs whenever TCNT0 matches OCR0A. ]
*/
extern void timer0_init_ctc(void);

/** \fn      void timer0_select_ctc_mode(void)
    \brief   [ Configures Timer/Counter0 for CTC mode of operation. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets WGM01 in TCCR0A to select CTC mode, and sets COM0A0
             so the OC0A pin (PB3) is toggled automatically by hardware
             on every compare match. ]
*/
extern void timer0_select_ctc_mode(void);

/** \fn      void timer0_configure_ctc_settings(void)
    \brief   [ Applies the remaining CTC mode setup for Timer/Counter0. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets OCR0A to TIMER0_CTC_TARGET, resets TCNT0 to 0x00, and
             enables the Output Compare A Match interrupt. In CTC mode
             TCNT0 is automatically cleared by hardware on every match,
             so no preload value is needed. ]
*/
extern void timer0_configure_ctc_settings(void);

/** \fn      void timer0_enable_compare_a_interrupt(void)
    \brief   [ Enables the Timer/Counter0 Output Compare A Match interrupt. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets OCIE0A in TIMSK0 so a TIMER0_COMPA interrupt request
             is raised whenever TCNT0 matches OCR0A. ]
*/
extern void timer0_enable_compare_a_interrupt(void);

/** \fn      void timer1_enable_peripheral_clock(void)
    \brief   [ Enables the clock to the Timer/Counter1 peripheral. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Clears the PRTIM1 bit in the Power Reduction Register so
             Timer/Counter1 can operate. ]
*/
extern void timer1_enable_peripheral_clock(void);

/** \fn      void timer1_enable_compare_a_interrupt(void)
    \brief   [ Enables the Timer/Counter1 Output Compare A Match interrupt. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Sets OCIE1A in TIMSK1 so a TIMER1_COMPA interrupt request
             is raised whenever TCNT1 matches OCR1A. ]
*/
extern void timer1_enable_compare_a_interrupt(void);

/** \fn      void timer1_init_ctc_100ms(void)
    \brief   [ Configures Timer/Counter1 to generate a 100ms square wave on OC1A. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Enables the Timer1 peripheral clock, selects CTC mode with
             OCR1A as TOP, sets OCR1A = 6249 so each compare match occurs
             every 50ms (giving a 100ms full period), sets COM1A0 so OC1A
             (PD5) is toggled automatically by hardware on every match,
             then starts the timer with a /8 prescaler. ]
*/
extern void timer1_init_ctc_100ms(void);

/** \fn      void timer1_airbag_configure(void)
    \brief   [ Arms the airbag deployment timer without starting it. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Enables the Timer1 peripheral clock and configures CTC mode
             with OCR1A = 724, so that once started, OC1A (PD5) is forced
             low by hardware exactly 725us later (no prescaling). Sets
             COM1A1 so OC1A is cleared on compare match. The clock source
             is intentionally left disabled here; the timer stays idle
             until airbag_timer_start() is called. ]
*/
extern void timer1_airbag_configure(void);

/** \fn      void timer1_airbag_start(void)
    \brief   [ Starts the airbag deployment countdown. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Resets TCNT1 to zero, and enables the
             Timer/Counter1 clock with no prescaling, so OC1A is driven
             low by hardware exactly 725us later. Call this the moment
             a frontal crash is detected. ]
*/
extern void timer1_airbag_start(void);

extern void timer1_init_10ms(void);

#endif /* TIMER_H */
