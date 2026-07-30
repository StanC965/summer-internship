#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\button.c"
#line 1 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\button.h"



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

#line 5 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\button.h"

typedef unsigned char button_uint8_t;







typedef struct
{
    volatile gpio_uint8_t *button_pin_register;
    button_uint8_t button_pin_number;

    button_uint8_t button_sample_buffer;
    button_uint8_t button_stable_state;
    button_uint8_t button_press_event;
} button_t;

extern void button_init(
    button_t *button_instance,
    volatile gpio_uint8_t *button_ddr_register,
    volatile gpio_uint8_t *button_port_register,
    volatile gpio_uint8_t *button_pin_register,
    button_uint8_t button_pin_number
);

extern void button_debounce_task(
    button_t *button_instance
);

extern button_uint8_t button_was_pressed(
    button_t *button_instance
);

#line 2 "D:\\Marquradt\\summer-internship\\work\\StravaC\\week3\\goal1\\button.c"














 







void button_init(
    button_t *button_instance,
    volatile gpio_uint8_t *button_ddr_register,
    volatile gpio_uint8_t *button_port_register,
    volatile gpio_uint8_t *button_pin_register,
    button_uint8_t button_pin_number
)
{
    button_instance->button_pin_register =
        button_pin_register;

    button_instance->button_pin_number =
        button_pin_number;

    button_instance->button_sample_buffer =
        (0x1FU);

    button_instance->button_stable_state =
        (0U);

    button_instance->button_press_event =
        (0U);

    gpio_set_direction(
        button_ddr_register,
        button_pin_number,
        (0U)
    );

    

 

    gpio_set_pin(
        button_port_register,
        button_pin_number
    );
}

void button_debounce_task(
    button_t *button_instance
)
{
    button_uint8_t button_raw_sample;

    button_raw_sample = gpio_read_pin(
        button_instance->button_pin_register,
        button_instance->button_pin_number
    );

    button_instance->button_sample_buffer =
        (button_uint8_t)(
            (
                button_instance->button_sample_buffer
                << (1U)
            ) |
            button_raw_sample
        );

    button_instance->button_sample_buffer &=
        (0x1FU);

    if (
        button_instance->button_sample_buffer ==
        (0x00U)
    )
    {
        if (
            button_instance->button_stable_state ==
            (0U)
        )
        {
            button_instance->button_stable_state =
                (1U);

            button_instance->button_press_event =
                (1U);
        }
    }
    else if (
        button_instance->button_sample_buffer ==
        (0x1FU)
    )
    {
        button_instance->button_stable_state =
            (0U);
    }
    else
    {
        



 
    }
}

button_uint8_t button_was_pressed(
    button_t *button_instance
)
{
    button_uint8_t button_event;

    button_event =
        button_instance->button_press_event;

    button_instance->button_press_event =
        (0U);

    return button_event;
}
