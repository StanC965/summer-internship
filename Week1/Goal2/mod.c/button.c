#include <iom324pb.h>
#include "button.h"
#include "gpio.h"

// Configures SW0 (PC6) as an Input
void button_init(void) {
    gpio_set_direction(&DDRC, INPUT, 6);
    
    gpio_set_pin(&PORTC, 6);
}

// Reads SW0 pin and filters out contact bounce noise
uint8_t button_sw0_is_pressed(void) {
    // If gpio_read_pin returns 0, the button is physically connecting to GND
    if (gpio_read_pin(&PINC, 6) == 0) {
        
        // Delays execution for 10-15ms to let electrical noise settle down
        for (volatile unsigned long debounce_delay = 0; debounce_delay < 1200; debounce_delay++);
        
        // Re-read the pin: If low, this is a real press
        if (gpio_read_pin(&PINC, 6) == 0) {
            return 1; // Validated Pressed state
        }
    }
    return 0; // Not pressed, or caught during an unstable bounce
}