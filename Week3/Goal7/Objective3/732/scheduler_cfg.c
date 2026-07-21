#include "scheduler_cfg.h"
#include "pwm.h"
#include "button.h"
#include "adc.h"
#include "led.h"
#include "uart.h"

#define MESSAGE_LENGTH 12

static const char target_message[MESSAGE_LENGTH + 1] = "Hello World!";
static char rx_buffer[MESSAGE_LENGTH + 1];
static unsigned char tx_index = 0;
static unsigned char rx_index = 0;
static unsigned char test_complete = 0;

void scheduler_task_50ms(void)
{    
    if (uart_is_rx_available())
    {
        unsigned char rx_char = uart_read_byte();
        
        if (rx_index < MESSAGE_LENGTH)
        {
            rx_buffer[rx_index] = rx_char;
            rx_index++;
            rx_buffer[rx_index] = '\0'; 
            
            if (rx_index == MESSAGE_LENGTH)
            {
                test_complete = 1;
                
                led_power_on(LED_LED0_PORT, LED_LED0_PIN);
            }
        }
    }
}

void scheduler_task_100ms(void)
{
    
}

void scheduler_task_500ms(void)
{
    
}

void scheduler_task_1000ms(void)
{
    if (!test_complete && (tx_index < MESSAGE_LENGTH))
    {
        if (uart_is_tx_ready())
        {
            uart_send_byte((unsigned char)target_message[tx_index]);
            tx_index++;
        }
    }
}


