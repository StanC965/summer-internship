#include "led.h"
#include "state_machine.h"

/*
State Machine correspondence:

STATES:
- STATE_MACHINE_LED_OFF
- STATE_MACHINE_LED_ON

EVENT:
- STATE_MACHINE_EVENT_BUTTON_PRESSED

TRANSITIONS:
- OFF -> ON
- ON  -> OFF

GUARD CONDITION:
- button press event must be valid after debounce

ACTIONS / OUTPUTS:
- turn corresponding LED ON
- turn corresponding LED OFF
*/

void state_machine_init(
    state_machine_led_t *state_machine_instance,
    volatile state_machine_uint8_t *led_port_register,
    state_machine_uint8_t led_pin_number
)
{
    state_machine_instance->current_state =
        STATE_MACHINE_LED_OFF;

    state_machine_instance->led_port_register =
        led_port_register;

    state_machine_instance->led_pin_number =
        led_pin_number;

    led_power_off(
        state_machine_instance->led_port_register,
        state_machine_instance->led_pin_number
    );
}

void state_machine_process(
    state_machine_led_t *state_machine_instance,
    state_machine_event_t state_machine_event
)
{
    switch (
        state_machine_instance->current_state
    )
    {
        case STATE_MACHINE_LED_OFF:
        {
            /*
            Guard condition:
            a valid debounced press event was received.
            */

            if (
                state_machine_event ==
                STATE_MACHINE_EVENT_BUTTON_PRESSED
            )
            {
                /*
                Transition:
                LED OFF -> LED ON
                */

                state_machine_instance->current_state =
                    STATE_MACHINE_LED_ON;

                /*
                Entry action/output:
                turn the corresponding LED ON.
                */

                led_power_on(
                    state_machine_instance
                        ->led_port_register,
                    state_machine_instance
                        ->led_pin_number
                );
            }

            break;
        }

        case STATE_MACHINE_LED_ON:
        {
            if (
                state_machine_event ==
                STATE_MACHINE_EVENT_BUTTON_PRESSED
            )
            {
                /*
                Transition:
                LED ON -> LED OFF
                */

                state_machine_instance->current_state =
                    STATE_MACHINE_LED_OFF;

                /*
                Entry action/output:
                turn the corresponding LED OFF.
                */

                led_power_off(
                    state_machine_instance
                        ->led_port_register,
                    state_machine_instance
                        ->led_pin_number
                );
            }

            break;
        }

        default:
        {
            /*
            Recovery from an invalid state.
            */

            state_machine_instance->current_state =
                STATE_MACHINE_LED_OFF;

            led_power_off(
                state_machine_instance
                    ->led_port_register,
                state_machine_instance
                    ->led_pin_number
            );

            break;
        }
    }
}