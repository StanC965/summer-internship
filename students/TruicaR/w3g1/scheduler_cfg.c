#include "iom324pb.h"
#include "scheduler_cfg.h"
#include "gpio.h"
#include "led.h"

void task_50ms(void)   { }
void task_100ms(void)  { }
void task_500ms(void)  { }
void task_1000ms(void)
{
    gpio_read_pin(&PINC, 7) ? led_off(&PORTC, 7) : led_on(&PORTC, 7);
}