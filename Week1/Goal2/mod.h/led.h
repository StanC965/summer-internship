#ifndef LED_H
#define LED_H

#include <stdint.h>

// Abstract ID definitions matching our hardware design limits
#define LED_0   0  // Onboard LED0
#define LED_1   1  // OLED1 LED1
#define LED_2   2  // OLED1 LED2
#define LED_3   3  // OLED1 LED3

// Public Abstract Module Interfaces
void led_init(void);
void led_power_on(uint8_t led_id);
void led_power_off(uint8_t led_id);
void led_blink_fast(uint8_t led_id);
void led_blink_slow(uint8_t led_id);

#endif /* LED_H */