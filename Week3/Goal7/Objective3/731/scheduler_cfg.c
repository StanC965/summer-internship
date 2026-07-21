#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"
#include "uart.h"


void scheduler_task_50ms(void)
{
    
}

void scheduler_task_100ms(void)
{
    
}

void scheduler_task_500ms(void)
{
    if (uart_is_tx_ready())
    {
        uart_send_byte('A');
    }

    if (uart_is_rx_available())
    {
        unsigned char received = uart_read_byte();
        
        if (received == 'A')
        {
            led_toggle(LED_LED0_PORT, LED_LED0_PIN);
        }
    }
}

void scheduler_task_1000ms(void)
{
    
}


