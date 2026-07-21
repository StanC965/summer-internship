# Week: 3 - Goal : 5


## Objective 4: Control Panel REVISITED

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[541]** | `CORE`     | [x] Completed

---

#### Task 541
> **Question/Prompt:** Go to BMW Control Panel Application and refactor the code as follows:
> - introduce the task scheduler for handling of buttons and LEDs behavior
> - use debounce algorithm for a stable state of buttons

> **Answer/Explanation:**

**`scheduler_cfg.c`**
```c
void task_10ms(void)
{
    button_debounce_update();
}

void task_50ms(void)
{
    hvac_control_process();
}
```

**`button.c`**
```c
static uint8_t button_read_raw(button_id_t btn)
{
    if (btn >= BUTTON_COUNT)
    {
        return 0;
    }
    
    return (gpio_read_pin(button_table[btn].pin_register, button_table[btn].pin) == 0);
}

void button_debounce_update(void)
{
    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        uint8_t raw_sample = button_read_raw((button_id_t)i);

        button_sample_buffer[i] = ((button_sample_buffer[i] << 1) | raw_sample) & BUTTON_DEBOUNCE_MASK;

        if ((button_sample_buffer[i] == BUTTON_DEBOUNCE_PRESSED) && (button_stable_state[i] == 0))
        {
            button_stable_state[i] = 1;
            button_press_event[i] = 1;
        }
        else if ((button_sample_buffer[i] == BUTTON_DEBOUNCE_RELEASED) && (button_stable_state[i] == 1))
        {
            button_stable_state[i] = 0;
        }
    }
}

uint8_t button_was_pressed(button_id_t button_id)
{
    uint8_t event = 0;

    if (button_id < BUTTON_COUNT)
    {
        event = button_press_event[button_id];
        button_press_event[button_id] = 0;
    }

    return event;
}

uint8_t button_is_pressed(button_id_t button_id)
{
    return (button_id < BUTTON_COUNT) ? button_stable_state[button_id] : 0;
}
```

**`hvac_control.c`**
```c
void hvac_control_process(void)
{
    if (button_was_pressed(BUTTON_ONBOARD))
    {
        button_pressed_toggle[BUTTON_ONBOARD] ^= 1;

        if (button_pressed_toggle[BUTTON_ONBOARD])
        {
            hvac_state = STATE_BLOCKED;
            led_power_on(button_to_led_map[BUTTON_ONBOARD]);
            turn_off_all_vents();
        }
        else
        {
            hvac_state = STATE_NORMAL;
            led_power_off(button_to_led_map[BUTTON_ONBOARD]);
        }
    }

    for (uint8_t i = BUTTON_OLED1_1; i <= BUTTON_OLED1_3; i++)
    {
        if (button_was_pressed((button_id_t)i))
        {
            if (hvac_state == STATE_BLOCKED)
            {
                led_blink_fast(button_to_led_map[BUTTON_ONBOARD]);
                led_power_on(button_to_led_map[BUTTON_ONBOARD]);
            }
            else if (hvac_state == STATE_NORMAL)
            {
                button_pressed_toggle[i] ^= 1;

                if (button_pressed_toggle[i])
                {
                    led_power_on(button_to_led_map[i]);
                }
                else
                {
                    led_power_off(button_to_led_map[i]);
                }
            }
        }
    }
}
```

---