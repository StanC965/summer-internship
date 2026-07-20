#ifndef HVAC_CONTROL_H
#define HVAC_CONTROL_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef enum {
    STATE_NORMAL = 0,
    STATE_BLOCKED
} hvac_state_t;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void hvac_control_init(void)

    \brief      [ Initializes the HVAC control module. ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Performs all necessary initialization steps for the HVAC control module. ]
*/
extern void hvac_control_init(void);

/** \fn     void hvac_control_process(void)

    \brief      [ Processes the HVAC control logic. ]
    \param[in]  None
    \param[out] [ None ]
    \return     [ None ]
    \details    [ Executes the main control logic for the HVAC system. ]
*/
extern void hvac_control_process(void);

#endif /* HVAC_CONTROL_H */