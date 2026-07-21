/**
 * @file main.c
 * @brief Main application entry point and system hardware initialization[cite: 10].
 */

#include "timer.h"
#include "led.h"
#include "button.h"
#include "scheduler.h"
#include "adc.h"
#include "pwm.h"
#include "intrinsics.h"
#include "uart.h"

/**
 * @brief Initializes core system hardware peripherals and enables global interrupts[cite: 10].
 */
void init_system(void)
{
    gpio_init();
    led_init();
    scheduler_init();
    uart_init();
            
    __enable_interrupt();
}

/**
 * @brief Program main entry point[cite: 10].
 * @return Does not return; transfers control to the task dispatcher loop[cite: 10, 13].
 */
void main(void)
{
    init_system();
    
    timer_t3_init_system_tick();
    
    scheduler_tasks_dispatcher();
}