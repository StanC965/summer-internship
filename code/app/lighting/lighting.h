#ifndef LIGHTNG_H
#define LIGHTNG_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef enum
{
    LIGHT_MODE_NIGHT = 0,
    LIGHT_MODE_DAY
} light_mode_t;

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

extern void lighting_trigger_entry_phase(void);

extern void lighting_entry_phase_update(void);

#endif /* LIGHTNG_H */