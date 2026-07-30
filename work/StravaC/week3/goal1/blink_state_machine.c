#include "led.h"
#include "blink_state_machine.h"

/*
LED0 blinking State Machine

States:
- BLINK_SM_STATE_LED_ON
- BLINK_SM_STATE_LED_OFF

Event:
- BLINK_SM_EVENT_TIMEOUT_1S

Transitions:
- LED_ON  -> LED_OFF when 1 second elapsed
- LED_OFF -> LED_ON  when 1 second elapsed

Guard condition:
- event == BLINK_SM_EVENT_TIMEOUT_1S

Actions:
- turn LED0 ON
- turn LED0 OFF
*/

void blink_sm_init(
    blink_sm_t *blink_sm_instance,
    volatile blink_sm_uint8_t *led_port_register,
    blink_sm_uint8_t led_pin_number
)
{
    blink_sm_instance->current_state =
        BLINK_SM_STATE_LED_ON;

    blink_sm_instance->led_port_register =
        led_port_register;

    blink_sm_instance->led_pin_number =
        led_pin_number;

    /*
    Entry action for the initial LED_ON state.
    */

    led_power_on(
        blink_sm_instance->led_port_register,
        blink_sm_instance->led_pin_number
    );
}

void blink_sm_process(
    blink_sm_t *blink_sm_instance,
    blink_sm_event_t blink_sm_event
)
{
    switch (blink_sm_instance->current_state)
    {
        case BLINK_SM_STATE_LED_ON:
        {
            if (
                blink_sm_event ==
                BLINK_SM_EVENT_TIMEOUT_1S
            )
            {
                /*
                Transition:
                LED_ON -> LED_OFF
                */

                blink_sm_instance->current_state =
                    BLINK_SM_STATE_LED_OFF;

                /*
                Entry action for LED_OFF.
                */

                led_power_off(
                    blink_sm_instance->led_port_register,
                    blink_sm_instance->led_pin_number
                );
            }

            break;
        }

        case BLINK_SM_STATE_LED_OFF:
        {
            if (
                blink_sm_event ==
                BLINK_SM_EVENT_TIMEOUT_1S
            )
            {
                /*
                Transition:
                LED_OFF -> LED_ON
                */

                blink_sm_instance->current_state =
                    BLINK_SM_STATE_LED_ON;

                /*
                Entry action for LED_ON.
                */

                led_power_on(
                    blink_sm_instance->led_port_register,
                    blink_sm_instance->led_pin_number
                );
            }

            break;
        }

        default:
        {
            /*
            Recovery from an invalid state.
            */

            blink_sm_instance->current_state =
                BLINK_SM_STATE_LED_ON;

            led_power_on(
                blink_sm_instance->led_port_register,
                blink_sm_instance->led_pin_number
            );

            break;
        }
    }
}