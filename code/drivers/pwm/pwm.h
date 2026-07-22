#ifndef PWM_H
#define PWM_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Fast PWM 8-bit resolution: TOP is always 0xFF */
#define PWM_RESOLUTION       (255U)
#define PWM_STEP_COUNT       5

typedef enum
{
    PWM_DUTY_0   = 0,
    PWM_DUTY_25  = 25,
    PWM_DUTY_50  = 50,
    PWM_DUTY_75  = 75,
    PWM_DUTY_100 = 100
} pwm_duty_t;

typedef enum
{
    SEQ_RAMP_UP = 0,
    SEQ_HOLD_HIGH_1,
    SEQ_DIP_LOW_1,
    SEQ_HOLD_HIGH_2,
    SEQ_DIP_LOW_2,
    SEQ_HOLD_HIGH_3,
    SEQ_RAMP_DOWN,
    SEQ_PAUSE
} pwm_seq_phase_t;

#define SEQ_RAMP_STEP_PERCENT   (5U)    
#define SEQ_HOLD_TICKS          (10U)   
#define SEQ_PAUSE_TICKS         (30U)   

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \fn      void pwm_init(void)
 
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \brief      [ Configures Timer0/OC0A for Fast PWM, non-inverting, no output yet. ]
    \details    [ Sets WGM02:00 for Fast PWM (TOP=0xFF), configures PB3 (OC0A)
                  as output, leaves the timer clock stopped until pwm_start(). ]
*/
extern void pwm_init(void);

/** \fn      void pwm_start(void)
 
    \brief      [ Starts the PWM timer clock (no prescaling). ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [  ]

*/
extern void pwm_start(void);

/** \fn      void pwm_set_duty_cycle(uint8_t duty_percent)
 
    \brief      [ Sets the OC0A duty cycle, handling the 0% and 100% edge cases. ]
    \param[in]  duty_percent [ 0-100 ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [  ]
*/
extern void pwm_set_duty_cycle(uint8_t duty_percent);

extern void pwm_incremental_update(void);

extern void pwm_sequence_update(void);

#endif /* PWM_H */
