#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\blink_state_machine.c"
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

#line 2 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\blink_state_machine.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\blink_state_machine.h"



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

#line 3 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\blink_state_machine.c"





















 

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
                


 

                blink_sm_instance->current_state =
                    BLINK_SM_STATE_LED_OFF;

                

 

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
                


 

                blink_sm_instance->current_state =
                    BLINK_SM_STATE_LED_ON;

                

 

                led_power_on(
                    blink_sm_instance->led_port_register,
                    blink_sm_instance->led_pin_number
                );
            }

            break;
        }

        default:
        {
            

 

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
