#ifndef LIGHTNG_H
#define LIGHTNG_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef struct
{
    uint8_t perceived_min;
    uint8_t perceived_max;
    uint8_t absolute_entry_percent;
    light_mode_t mode;
} light_band_t;

typedef enum
{
    LIGHT_MODE_NIGHT = 0,
    LIGHT_MODE_DAY
} light_mode_t;

#define ENTRY_PHASE_STEP_COUNT (11U)

#define LIGHTING_PWM_TOP (1249U)

typedef enum
{
    ENTRY_PHASE_IDLE = 0,
    ENTRY_PHASE_RUNNING
} entry_phase_state_t;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      void adc_init(void)
    \brief   [ Initializes the ADC module. ]
    \param   [ None ]
    \return  [ None ]
    \details [ Performs all necessary initialization steps for the ADC module,
               configuring initial references and control registers. ]
*/
extern void lighting_init(void);

/** \fn      void lighting_trigger_entry_phase(void)
    \brief   [ ]
    \param   [ None ]
    \return  [ None ]
    \details [ ]
*/
extern void lighting_trigger_entry_phase(void);

/** \fn      void lighting_entry_phase_update(void
    \brief   [ ]
    \param   [ None ]
    \return  [ None ]
    \details [ ]
*/
extern void lighting_entry_phase_update(void);

#endif /* LIGHTNG_H */