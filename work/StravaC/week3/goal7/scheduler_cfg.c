#include "iom324pb.h"
#include "button.h"
#include "control_panel_protocol.h"
#include "gpio.h"
#include "led.h"
#include "scheduler_cfg.h"
#include "uart.h"

/*
OLED1 on EXT1:
BUTTON1 -> PC1, BUTTON2 -> PA0, BUTTON3 -> PA1
LED1 -> PD5, LED2 -> PD4, LED3 -> PA3

IO1 on EXT4:
USART2 RX -> PE2, USART2 TX -> PE3
Black jumper connects TX to RX.

Virtual MCU1 reads buttons and sends a 3-bit LED command.
Virtual MCU2 receives the command and drives the LEDs.
*/
#define APP_BUTTON1_DDR_REGISTER       (&DDRC)
#define APP_BUTTON1_PORT_REGISTER      (&PORTC)
#define APP_BUTTON1_PIN_REGISTER       (&PINC)
#define APP_BUTTON1_PIN_NUMBER         (1U)
#define APP_BUTTON2_DDR_REGISTER       (&DDRA)
#define APP_BUTTON2_PORT_REGISTER      (&PORTA)
#define APP_BUTTON2_PIN_REGISTER       (&PINA)
#define APP_BUTTON2_PIN_NUMBER         (0U)
#define APP_BUTTON3_DDR_REGISTER       (&DDRA)
#define APP_BUTTON3_PORT_REGISTER      (&PORTA)
#define APP_BUTTON3_PIN_REGISTER       (&PINA)
#define APP_BUTTON3_PIN_NUMBER         (1U)
#define APP_LED1_DDR_REGISTER          (&DDRD)
#define APP_LED1_PORT_REGISTER         (&PORTD)
#define APP_LED1_PIN_NUMBER            (5U)
#define APP_LED2_DDR_REGISTER          (&DDRD)
#define APP_LED2_PORT_REGISTER         (&PORTD)
#define APP_LED2_PIN_NUMBER            (4U)
#define APP_LED3_DDR_REGISTER          (&DDRA)
#define APP_LED3_PORT_REGISTER         (&PORTA)
#define APP_LED3_PIN_NUMBER            (3U)
#define APP_COMMAND_INITIAL_VALUE      (0U)

static button_t app_button1;
static button_t app_button2;
static button_t app_button3;
static control_panel_uint8_t app_master_led_command;

static void app_master_task(void);
static void app_slave_task(void);
static void app_apply_received_command(control_panel_uint8_t received_command);
static void app_set_led_from_mask(volatile gpio_uint8_t *led_port_register, gpio_uint8_t led_pin_number, control_panel_uint8_t command, control_panel_uint8_t led_mask);

void scheduler_cfg_init(void)
{
    gpio_init();
    uart_init();

    led_init(APP_LED1_DDR_REGISTER, APP_LED1_PORT_REGISTER, APP_LED1_PIN_NUMBER);
    led_init(APP_LED2_DDR_REGISTER, APP_LED2_PORT_REGISTER, APP_LED2_PIN_NUMBER);
    led_init(APP_LED3_DDR_REGISTER, APP_LED3_PORT_REGISTER, APP_LED3_PIN_NUMBER);

    button_init(&app_button1, APP_BUTTON1_DDR_REGISTER, APP_BUTTON1_PORT_REGISTER, APP_BUTTON1_PIN_REGISTER, APP_BUTTON1_PIN_NUMBER);
    button_init(&app_button2, APP_BUTTON2_DDR_REGISTER, APP_BUTTON2_PORT_REGISTER, APP_BUTTON2_PIN_REGISTER, APP_BUTTON2_PIN_NUMBER);
    button_init(&app_button3, APP_BUTTON3_DDR_REGISTER, APP_BUTTON3_PORT_REGISTER, APP_BUTTON3_PIN_REGISTER, APP_BUTTON3_PIN_NUMBER);

    app_master_led_command = APP_COMMAND_INITIAL_VALUE;
}

void scheduler_task_10ms(void)
{
    app_master_task();
    app_slave_task();
}

void scheduler_task_50ms(void) {}
void scheduler_task_100ms(void) {}
void scheduler_task_500ms(void) {}
void scheduler_task_1000ms(void) {}

static void app_master_task(void)
{
    control_panel_uint8_t command_changed = 0U;

    button_debounce_task(&app_button1);
    button_debounce_task(&app_button2);
    button_debounce_task(&app_button3);

    if (button_was_pressed(&app_button1) == BUTTON_EVENT_DETECTED)
    {
        app_master_led_command = control_panel_toggle_led(app_master_led_command, CONTROL_PANEL_LED1_MASK);
        command_changed = 1U;
    }
    if (button_was_pressed(&app_button2) == BUTTON_EVENT_DETECTED)
    {
        app_master_led_command = control_panel_toggle_led(app_master_led_command, CONTROL_PANEL_LED2_MASK);
        command_changed = 1U;
    }
    if (button_was_pressed(&app_button3) == BUTTON_EVENT_DETECTED)
    {
        app_master_led_command = control_panel_toggle_led(app_master_led_command, CONTROL_PANEL_LED3_MASK);
        command_changed = 1U;
    }

    if (command_changed != 0U)
    {
        uart_send_byte(app_master_led_command);
    }
}

static void app_slave_task(void)
{
    control_panel_uint8_t received_command;

    while (uart_is_data_available() == UART_DATA_AVAILABLE)
    {
        received_command = uart_receive_byte();
        received_command = control_panel_sanitize_command(received_command);
        app_apply_received_command(received_command);
    }
}

static void app_apply_received_command(control_panel_uint8_t received_command)
{
    app_set_led_from_mask(APP_LED1_PORT_REGISTER, APP_LED1_PIN_NUMBER, received_command, CONTROL_PANEL_LED1_MASK);
    app_set_led_from_mask(APP_LED2_PORT_REGISTER, APP_LED2_PIN_NUMBER, received_command, CONTROL_PANEL_LED2_MASK);
    app_set_led_from_mask(APP_LED3_PORT_REGISTER, APP_LED3_PIN_NUMBER, received_command, CONTROL_PANEL_LED3_MASK);
}

static void app_set_led_from_mask(volatile gpio_uint8_t *led_port_register, gpio_uint8_t led_pin_number, control_panel_uint8_t command, control_panel_uint8_t led_mask)
{
    if ((command & led_mask) != 0U)
    {
        led_power_on(led_port_register, led_pin_number);
    }
    else
    {
        led_power_off(led_port_register, led_pin_number);
    }
}
