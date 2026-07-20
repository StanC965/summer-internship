//W1G2 Objective 1

// #include <iom324pb.h>

// void main(void) {
  
//    volatile unsigned long delay;
//    
//    // set PC7 as an output
//    DDRC |= (1 << 7);
//
//    while(1) {
//        // LED0 ON (Drive LOW)
//        PORTC &= ~(1 << 7);
//        
//        // delay for 1 second
//        for(delay = 0; delay < 100000; delay++);
//        
//        // LED0 OFF (Drive HIGH)
//        PORTC |= (1 << 7);
//        
//        // delay for 1 second
//        for(delay = 0; delay < 100000; delay++);
//    }
  
  
// }


// W1G2 Objective 2

//#include <iom324pb.h>
//
//void delay(volatile unsigned long count) {
//    for(volatile unsigned long i = 0; i < count; i++);
//}
//
//void main(void) {
//  
//    DDRD |= (1 << 5); 
//    DDRD |= (1 << 4); 
//    DDRA |= (1 << 3); 
//    
//    // 2. Set Initial State: All LEDs OFF (Drive pins HIGH)
//    PORTD |= (1 << 5); 
//    PORTD |= (1 << 4);
//    PORTA |= (1 << 3);
//    delay(50000); // Hold initial state briefly before starting the loop
//
//    while(1) {
//        
//        PORTD &= ~(1 << 5); // LED1 ON (Low)
//        PORTD &= ~(1 << 4); // LED2 ON (Low)
//        PORTA |= (1 << 3);  // LED3 OFF (High)
//        delay(50000);
//
//        PORTD |= (1 << 5);  // LED1 OFF (High)
//        PORTD &= ~(1 << 4); // LED2 ON (Low)
//        PORTA &= ~(1 << 3); // LED3 ON (Low)
//        delay(50000);       
//        
//        PORTD &= ~(1 << 5); // LED1 ON (Low)
//        PORTD |= (1 << 4);  // LED2 OFF (High)
//        PORTA &= ~(1 << 3); // LED3 ON (Low)
//        delay(50000);       
//    }
//}

//W1G2 Objective 3

//#include <iom324pb.h>
//#include <stdint.h>  
//
//#define INPUT  0
//#define OUTPUT 1
//
//
//void gpio_set_pin(volatile uint8_t *port, uint8_t pin) {
//    *port |= (1 << pin);
//}
//
//void gpio_reset_pin(volatile uint8_t *port, uint8_t pin) {
//    *port &= ~(1 << pin);
//}
//
//void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin) {
//    *ddr_register = (direction == OUTPUT) ? (*ddr_register | (1 << pin)) : (*ddr_register & ~(1 << pin)); 
//}
//
//void gpio_toggle_pin(volatile uint8_t *port, uint8_t pin) {
//    *port ^= (1 << pin);
//}
//
//void delay(volatile unsigned long count) {
//    for(volatile unsigned long i = 0; i < count; i++);
//}
//
//void main(void) {
//    // initialize directions 
//    gpio_set_direction(&DDRC, OUTPUT, 7); // Onboard LED0 (PC7)
//    gpio_set_direction(&DDRD, OUTPUT, 5); // OLED LED1 (PD5)
//    gpio_set_direction(&DDRD, OUTPUT, 4); // OLED LED2 (PD4)
//    gpio_set_direction(&DDRA, OUTPUT, 3); // OLED LED3 (PA3)
//
//    while(1) {
//        // turn all LEDs ON (active-low: reset pin to 0) 
//        gpio_reset_pin(&PORTC, 7);
//        gpio_reset_pin(&PORTD, 5);
//        gpio_reset_pin(&PORTD, 4);
//        gpio_reset_pin(&PORTA, 3);
//        delay(40000);
//
//        // turn all LEDs OFF (active-low: set pin to 1) 
//        gpio_set_pin(&PORTC, 7);
//        gpio_set_pin(&PORTD, 5);
//        gpio_set_pin(&PORTD, 4);
//        gpio_set_pin(&PORTA, 3);
//        delay(40000);
//
//        // toggle OLED display pins individually 
//        gpio_toggle_pin(&PORTD, 5); 
//        delay(20000);
//        gpio_toggle_pin(&PORTD, 4); 
//        delay(20000);
//        gpio_toggle_pin(&PORTA, 3); 
//        delay(20000);
//    }
//}

//W1G2 Objective 4

//#include "led.h"
//
//void main(void) {
//
//    led_init();
//
//    while(1) {
//        
//        led_blink_fast(LED_0); 
//        led_blink_slow(LED_1); 
//    }
//}

// W1G2 Objective 5

//#include "led.h"
//#include "button.h"
//
//void main(void) {
//    led_init();
//    button_init();
//
//    volatile uint8_t button_state = 0;
//
//    while(1) {
//        button_state = button_sw0_is_pressed();
//
//        if (button_state == 1) {
//            // Turn ON LED0 (PC7) if SW0 is held down
//            led_power_on(LED_0);
//        } else {
//            // Keep onboard LED0 turned OFF when released
//            led_power_off(LED_0);
//        }
//    }
//}

// W1G2 Objective 6

#include "sos.h"
#include "button.h"
#include "led.h"

void main(void) {
    sos_init();

    uint8_t sos_active = 0;     // State flag: 0 = Idle, 1 = Transmission active
    uint8_t button_released = 1; // Edge protection tracker to avoid double-triggering

    while(1) {
        if (button_sw0_is_pressed()) {
            if (button_released) {
                sos_active = !sos_active; Toggle the state (ON <-> OFF)
                button_released = 0;      // Lock edge flag until button is let go
                
                // If turning off, instantly force the LED dark
                if (!sos_active) {
                    led_power_off(LED_0);
                }
            }
        } else {
            button_released = 1; // Reset edge lock when button is free
        }

        if (sos_active) {
            // Run the sequence. If it returns 0, it means it was aborted early mid-loop
            uint8_t completed = sos_run_sequence();
            
            if (!completed) {
                sos_active = 0; // Turn off immediately
                led_power_off(LED_0);
                
                // Small safety window to allow the user to lift their finger 
                // after an early abort command
                for(volatile unsigned long lock = 0; lock < 40000; lock++);
            }
        }
    }
}