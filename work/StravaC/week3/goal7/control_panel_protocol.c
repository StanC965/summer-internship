#include "control_panel_protocol.h"

control_panel_uint8_t control_panel_toggle_led(control_panel_uint8_t current_command, control_panel_uint8_t led_mask)
{
    return (control_panel_uint8_t)(current_command ^ led_mask);
}

control_panel_uint8_t control_panel_sanitize_command(control_panel_uint8_t received_command)
{
    return (control_panel_uint8_t)(received_command & CONTROL_PANEL_VALID_MASK);
}
