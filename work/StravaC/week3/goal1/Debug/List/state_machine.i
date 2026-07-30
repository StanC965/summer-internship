#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\state_machine.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\led.h"



#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\gpio.h"



typedef unsigned char gpio_uint8_t;







extern void gpio_init(void);

extern void gpio_set_direction(
    volatile gpio_uint8_t *gpio_ddr_register,
    gpio_uint8_t gpio_pin_number,
    gpio_uint8_t gpio_direction
);

extern void gpio_set_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
);

extern void gpio_reset_pin(
    volatile gpio_uint8_t *gpio_port_register,
    gpio_uint8_t gpio_pin_number
);

extern gpio_uint8_t gpio_read_pin(
    volatile gpio_uint8_t *gpio_pin_register,
    gpio_uint8_t gpio_pin_number
);

#line 5 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\led.h"






 

extern void led_init(
    volatile gpio_uint8_t *led_ddr_register,
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

extern void led_power_on(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

extern void led_power_off(
    volatile gpio_uint8_t *led_port_register,
    gpio_uint8_t led_pin_number
);

#line 2 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\state_machine.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\state_machine.h"



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

#line 3 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\state_machine.c"





















 

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
            


 

            if (
                state_machine_event ==
                STATE_MACHINE_EVENT_BUTTON_PRESSED
            )
            {
                


 

                state_machine_instance->current_state =
                    STATE_MACHINE_LED_ON;

                


 

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
                


 

                state_machine_instance->current_state =
                    STATE_MACHINE_LED_OFF;

                


 

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
