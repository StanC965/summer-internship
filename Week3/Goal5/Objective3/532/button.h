#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define BUTTON_SW0_DDR             (&DDRC)
#define BUTTON_SW0_PORT            (&PORTC)
#define BUTTON_SW0_PINR            (&PINC)
#define BUTTON_SW0_PIN             6

#define BUTTON_OLED_1_DDR          (&DDRC)
#define BUTTON_OLED_1_PORT         (&PORTC)
#define BUTTON_OLED_1_PINR         (&PINC)
#define BUTTON_OLED_1_PIN          1       

#define BUTTON_OLED_2_3_DDR        (&DDRA)
#define BUTTON_OLED_2_3_PORT       (&PORTA)
#define BUTTON_OLED_2_3_PINR       (&PINA)
#define BUTTON_OLED_2_PIN          0            
#define BUTTON_OLED_3_PIN          1

#define PCINT22_SW0                6
#define PCINT17_SW1                1   
#define PCINT0_SW2                 0   
#define PCINT1_SW3                 1   

#define PCIE0_PORT_A               0   
#define PCIE2_PORT_C               2     

#define BUTTON_DEBOUNCE_THRESHOLD 500

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Public Functions                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void button_init(void)
    \brief  Initializes the button module by setting up input configurations and pull-ups for all system buttons.
*/
void button_init(void);

/** \fn     void button_configure_pin(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number)
    \brief  Configures a single target pin as an input and enables its pull-up resistor.
*/
void button_configure_pin(volatile unsigned char *ddr_reg, volatile unsigned char *port_reg, unsigned char pin_number);

/** \fn     unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number)
    \brief  Reads a targeted pin status instantly without any debounce handling loops.
    \return 1 if the button is currently pressed (LOW), 0 if released (HIGH).
*/
unsigned char button_is_pressed(volatile unsigned char *pin_reg, unsigned char pin_number);

/** \fn     void button_debounce_update(void)
    \brief  Samples the raw pin value, shifts it into the historical moving window, 
            and evaluates the majority principle. Must be called periodically every 50ms.
*/
void button_debounce_update(void);

/** \fn     unsigned char button_get_debounced_state(void)
    \brief  Public getter interface to fetch the securely encapsulated debounced stable button state.
    \return 1 if the button is stably pressed, 0 if stably released.
*/
unsigned char button_get_debounced_state(void);

#endif