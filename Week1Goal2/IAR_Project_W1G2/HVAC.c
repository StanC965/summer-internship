#ifndef HVAC_C
#define HVAC_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       HVAC.c
 *  \brief      HVAC app implementation.
 *  \author     Chirila Viorel
 *  \date       18.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "HVAC.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static unsigned char is_panel_blocked = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static void blink_blocked_warning(void) {
  for(unsigned char i = 0; i < 3; i++) {
    PowerOff_LED(LED0);
    delay(ONE_SECOND_DELAY/2); 
    PowerOn_LED(LED0);
    delay(ONE_SECOND_DELAY/2);
  }
}

void Handle_MasterControl_Event(void) {
  if (button_events.sw0_pressed == 1) {
    delay(ONE_SECOND_DELAY/20);
    
    if (button_read_state(SW0) == BUTTON_PRESSED) {
        
      is_panel_blocked = !is_panel_blocked; 
      
      if (is_panel_blocked == 1) {
          PowerOff_LED(LED1);
          PowerOff_LED(LED2);
          PowerOff_LED(LED3);
          PowerOn_LED(LED0);
      } else {
          PowerOff_LED(LED0);
      }
    }
    button_events.sw0_pressed = 0;
  }
}

void Handle_VentControl_Event(button_uint8_t button_id, unsigned char led_id, volatile unsigned char *event_flag) {
  if (*event_flag == 1) {
    delay(ONE_SECOND_DELAY/20);
    
    if (button_read_state(button_id) == BUTTON_PRESSED) {
      if (is_panel_blocked == 1) {
          blink_blocked_warning();
      } else {
          Toggle_LED(led_id);
      }
    }
    
    *event_flag = 0; 
  }
}

#endif

