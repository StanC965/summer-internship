/* 331 - Implemented with polling.
   BUTTON1 -> PC1, BUTTON2 -> PA0, BUTTON3 -> PA1
   LED1 -> PD5, LED2 -> PD4, LED3 -> PA3 */

#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "button.h"

void main( void )
{
    led_init(LED1_DDR, LED1_PIN);
    led_init(LED2_DDR, LED2_PIN);
    led_init(LED3_DDR, LED3_PIN);

    led_power_off(LED1_PORT, LED1_PIN);
    led_power_off(LED2_PORT, LED2_PIN);
    led_power_off(LED3_PORT, LED3_PIN);

    button_init(BUTTON1_DDR, BUTTON1_PORT, BUTTON1_PIN);
    button_init(BUTTON2_DDR, BUTTON2_PORT, BUTTON2_PIN);
    button_init(BUTTON3_DDR, BUTTON3_PORT, BUTTON3_PIN);

    while(1)
    {
        if (button_is_pressed(BUTTON1_PIN_REG, BUTTON1_PIN) == BUTTON_PRESSED)
            led_power_on(LED1_PORT, LED1_PIN);
        else
            led_power_off(LED1_PORT, LED1_PIN);

        if (button_is_pressed(BUTTON2_PIN_REG, BUTTON2_PIN) == BUTTON_PRESSED)
            led_power_on(LED2_PORT, LED2_PIN);
        else
            led_power_off(LED2_PORT, LED2_PIN);

        if (button_is_pressed(BUTTON3_PIN_REG, BUTTON3_PIN) == BUTTON_PRESSED)
            led_power_on(LED3_PORT, LED3_PIN);
        else
            led_power_off(LED3_PORT, LED3_PIN);
    }
}
