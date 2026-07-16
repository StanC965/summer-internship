#ifndef BUTTON_H
#define BUTTON_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define BUTTON_SW0_DDR     (&DDRC)
#define BUTTON_SW0_PORT    (&PORTC)
#define BUTTON_SW0_PINR    (&PINC)
#define BUTTON_SW0_PIN     6

#define BUTTON_OLED_1_DDR          (&DDRC)
#define BUTTON_OLED_1_PORT         (&PORTC)
#define BUTTON_OLED_1_PINR         (&PINC)
#define BUTTON_OLED_1_PIN          1       

#define BUTTON_OLED_2_3_DDR        (&DDRA)
#define BUTTON_OLED_2_3_PORT       (&PORTA)
#define BUTTON_OLED_2_3_PINR       (&PINA)
#define BUTTON_OLED_2_PIN          0            
#define BUTTON_OLED_3_PIN          1

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

/** \fn     unsigned char button_is_pressed_debounced(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf)
    \brief  Reads a targeted pin status dynamically using distinct tracking confidence thresholds.
    \return 1 if a stable press condition is verified, 0 otherwise.
*/
unsigned char button_is_pressed_debounced(volatile unsigned char *pin_reg, unsigned char pin_number, int *pressed_conf, int *released_conf);

#endif