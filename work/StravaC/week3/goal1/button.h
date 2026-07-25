#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_FALSE                 (0U)
#define BUTTON_TRUE                  (1U)

#define BUTTON_NOT_PRESSED           (BUTTON_FALSE)
#define BUTTON_PRESSED               (BUTTON_TRUE)

typedef unsigned char button_uint8_t;

extern void button_init(
    volatile unsigned char *button_ddr_register,
    volatile unsigned char *button_port_register,
    volatile unsigned char *button_pin_register,
    button_uint8_t button_pin_number
);

extern void button_debounce_task(void);

extern button_uint8_t button_is_pressed(void);

#endif