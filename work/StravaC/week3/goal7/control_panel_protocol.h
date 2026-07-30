#ifndef CONTROL_PANEL_PROTOCOL_H
#define CONTROL_PANEL_PROTOCOL_H

typedef unsigned char control_panel_uint8_t;

#define CONTROL_PANEL_LED1_MASK    (0x01U)
#define CONTROL_PANEL_LED2_MASK    (0x02U)
#define CONTROL_PANEL_LED3_MASK    (0x04U)
#define CONTROL_PANEL_VALID_MASK   (0x07U)

extern control_panel_uint8_t control_panel_toggle_led(control_panel_uint8_t current_command, control_panel_uint8_t led_mask);
extern control_panel_uint8_t control_panel_sanitize_command(control_panel_uint8_t received_command);

#endif
