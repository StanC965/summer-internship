#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"
#include <iom324pb.h>
#include "gpio.h"
#include "delay.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct {
    volatile uint8_t *ddr_register; 
    volatile uint8_t *port_register; 
    uint8_t pin;                     
} led_config_t;

static const led_config_t led_table[LED_COUNT] = {
    // ATmega328P onboard LED
    { &DDRC, &PORTC, 7 },

    // OLED1 LEDs
    { &DDRD, &PORTD, 5 },
    { &DDRD, &PORTD, 4 },
    { &DDRA, &PORTA, 3 },

    // IO1 LED
    { &DDRB, &PORTB, 3 }
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void led_init(void){
    for(uint8_t i = 0; i < LED_COUNT; i++){
        gpio_set_pin(led_table[i].port_register, led_table[i].pin);
        gpio_set_direction(led_table[i].ddr_register, GPIO_OUTPUT, led_table[i].pin);
    }
}

void led_power_on(led_id_t led_id){
    if(led_id < LED_COUNT){
        gpio_reset_pin(led_table[led_id].port_register, led_table[led_id].pin);
    }
}

void led_power_off(led_id_t led_id){
    if(led_id < LED_COUNT){
        gpio_set_pin(led_table[led_id].port_register, led_table[led_id].pin);
    }
}

void led_toggle(led_id_t led_id){
    if(led_id < LED_COUNT){
        gpio_toggle_pin(led_table[led_id].port_register, led_table[led_id].pin);
    }
}

void led_blink_fast(led_id_t led_id){
    if(led_id < LED_COUNT){
        for(uint8_t i = 0; i < 5; i++){
            led_power_on(led_id);
            delay(SECOND / 12);

            led_power_off(led_id);
            delay(SECOND / 12);
        }
    }
}  

void led_blink_slow(led_id_t led_id){
    if(led_id < LED_COUNT){
        for(uint8_t i = 0; i < 2; i++){
            led_power_on(led_id);
            delay(SECOND / 4);

            led_power_off(led_id);
            delay(SECOND / 4);
        }
    }
}  

#endif /* LED_C */