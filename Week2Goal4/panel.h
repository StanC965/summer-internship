#ifndef PANEL_H
#define PANEL_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  States of the control panel */
#define PANEL_UNBLOCKED     (0x00U)
#define PANEL_BLOCKED       (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Initialize the control panel: LEDs, buttons and the unblocked state */
extern void panel_init(void);

/** \brief  Toggle the panel between BLOCKED and UNBLOCKED
    \details Called from the SW0 interrupt service routine.
*/
extern void panel_toggle_blocked(void);

/** \brief  Run one step of the control panel logic*/
extern void panel_update(void);

#endif
