#include <iom324pb.h>
#include "led.h"
#include "gpio.h"

static void led_internal_delay(volatile unsigned long count) {
    for(volatile unsigned long i = 0; i < count; i++);
}

// Configures all pin mapping modes without exposing register complexities to main
void led_init(void) {
    gpio_set_direction(&DDRC, OUTPUT, 7); // LED0 on PC7
    gpio_set_direction(&DDRD, OUTPUT, 5); // LED1 on PD5
    gpio_set_direction(&DDRD, OUTPUT, 4); // LED2 on PD4
    gpio_set_direction(&DDRA, OUTPUT, 3); // LED3 on PA3
    
    // Ensure all start turned OFF initially (All are Active-Low, set to 1)
    led_power_off(LED_0);
    led_power_off(LED_1);
    led_power_off(LED_2);
    led_power_off(LED_3);
}

void led_power_on(uint8_t led_id) {
    switch(led_id) {
        case LED_0: gpio_reset_pin(&PORTC, 7); break; // Active-Low ON
        case LED_1: gpio_reset_pin(&PORTD, 5); break;
        case LED_2: gpio_reset_pin(&PORTD, 4); break;
        case LED_3: gpio_reset_pin(&PORTA, 3); break;
    }
}

void led_power_off(uint8_t led_id) {
    switch(led_id) {
        case LED_0: gpio_set_pin(&PORTC, 7); break; // Active-Low OFF
        case LED_1: gpio_set_pin(&PORTD, 5); break;
        case LED_2: gpio_set_pin(&PORTD, 4); break;
        case LED_3: gpio_set_pin(&PORTA, 3); break;
    }
}

void led_blink_fast(uint8_t led_id) {
    led_power_on(led_id);
    led_internal_delay(6600);  
    led_power_off(led_id);
    led_internal_delay(6600);
}

void led_blink_slow(uint8_t led_id) {
    led_power_on(led_id);
    led_internal_delay(20000);
    led_power_off(led_id);
    led_internal_delay(20000);
}