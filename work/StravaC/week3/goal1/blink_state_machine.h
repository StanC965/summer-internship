#ifndef BLINK_STATE_MACHINE_H
#define BLINK_STATE_MACHINE_H

typedef unsigned char blink_sm_uint8_t;

typedef enum
{
    BLINK_SM_STATE_LED_ON = 0,
    BLINK_SM_STATE_LED_OFF
} blink_sm_state_t;

typedef enum
{
    BLINK_SM_EVENT_NONE = 0,
    BLINK_SM_EVENT_TIMEOUT_1S
} blink_sm_event_t;

typedef struct
{
    blink_sm_state_t current_state;

    volatile blink_sm_uint8_t *led_port_register;
    blink_sm_uint8_t led_pin_number;
} blink_sm_t;

extern void blink_sm_init(
    blink_sm_t *blink_sm_instance,
    volatile blink_sm_uint8_t *led_port_register,
    blink_sm_uint8_t led_pin_number
);

extern void blink_sm_process(
    blink_sm_t *blink_sm_instance,
    blink_sm_event_t blink_sm_event
);

#endif