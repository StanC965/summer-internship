#ifndef BUTTON_H
#define BUTTON_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  SW0 button is connected to pin PC6 */
#define SW0_PIN   (6U)

/** \brief  Button states */
#define BUTTON_RELEASED     (0x00U)
#define BUTTON_PRESSED      (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Initialize the button pin as input with internal pull-up */
extern void button_init(void);

/** \brief  Read the button state with debounce
    \return     BUTTON_PRESSED (1) or BUTTON_RELEASED (0)
    \details    The signal is read twice, with a short delay between the readings,
                to filter out the contact bouncing noise.
*/
extern unsigned char button_is_pressed(void);

#endif
