#include "sos.h"
#include "led.h"
#include "button.h"

// Base Morse timing unit
#define MORSE_UNIT  7000 

static void sos_internal_delay(volatile unsigned long count) {
    for(volatile unsigned long i = 0; i < count; i++);
}

static void sos_print_dot(void) {
    led_power_on(LED_0);
    sos_internal_delay(MORSE_UNIT);      // ON for 1 unit
    led_power_off(LED_0);
    sos_internal_delay(MORSE_UNIT);     // Element gap: OFF for 1 unit
}

static void sos_print_dash(void) {
    led_power_on(LED_0);
    sos_internal_delay(MORSE_UNIT * 3);  // ON for 3 units
    led_power_off(LED_0);
    sos_internal_delay(MORSE_UNIT);     // Element gap: OFF for 1 unit
}

void sos_init(void) {
    led_init();
    button_init();
}

// Returns 1 if completed normally, returns 0 if aborted mid-sequence by a toggle request
uint8_t sos_run_sequence(void) {
    uint8_t i;

    //  Letter 'S': 3 Dots 
    for(i = 0; i < 3; i++) {
        sos_print_dot();
    }
    sos_internal_delay(MORSE_UNIT * 2); // Letter gap (Total 3 units off)

    // Did the user click to stop after the first 'S'?
    if (button_sw0_is_pressed()) return 0;

    // Letter 'O': 3 Dashes 
    for(i = 0; i < 3; i++) {
        sos_print_dash();
    }
    sos_internal_delay(MORSE_UNIT * 2); // Letter gap (Total 3 units off)

    // Did the user click to stop after the 'O'?
    if (button_sw0_is_pressed()) return 0;

    // Letter 'S': 3 Dots 
    for(i = 0; i < 3; i++) {
        sos_print_dot();
    }

    // Re-check button periodically during the long 1-second sleep
    for(i = 0; i < 10; i++) {
        sos_internal_delay(MORSE_UNIT * 2);
        if (button_sw0_is_pressed()) return 0; 
    }

    return 1; 
}