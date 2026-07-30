#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef unsigned char state_machine_uint8_t;

typedef enum
{
    STATE_MACHINE_EVENT_NONE = 0,
    STATE_MACHINE_EVENT_BUTTON_PRESSED
} state_machine_event_t;

typedef enum
{
    STATE_MACHINE_LED_OFF = 0,
    STATE_MACHINE_LED_ON
} state_machine_led_state_t;

typedef struct
{
    state_machine_led_state_t current_state;

    volatile state_machine_uint8_t *led_port_register;
    state_machine_uint8_t led_pin_number;
} state_machine_led_t;

extern void state_machine_init(
    state_machine_led_t *state_machine_instance,
    volatile state_machine_uint8_t *led_port_register,
    state_machine_uint8_t led_pin_number
);

extern void state_machine_process(
    state_machine_led_t *state_machine_instance,
    state_machine_event_t state_machine_event
);

#endif