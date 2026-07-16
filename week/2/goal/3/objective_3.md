# Week: 2 - Goal : 3


## Objective 3: Building a Control Panel - Internship's main application

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[331]** | `CORE`    | [x] Completed 

--- 

#### Task 331
> **Question/Prompt:** Construct your software program so that it can handle the 3 buttons from OLED1 extension board. The general behavior should be the following: when pressing button X then LED X is on, where X = 1,2,3, and when releasing button X then LED X is off. You have the freedom to choose what kind of implementation approach you prefer: polling the button state or trigger interrupts.

> **Answer/Explanation:**
> The buttons are connected to the following pins:
>  - 3 : PA0 - PCINT0  (BUTTON2)
>  - 4 : PA1 - PCINT1  (BUTTON3)
>  - 9 : PC1 - PCINT17 (BUTTON1)
>
> I created interrupt handlers for the buttons, and it is worth mentioning that the both the onboard button and the oled1_1 button and also the oled1_2 and oled_3 button share an interrupt vector.
> THe main loop's read logic will check what button is actually pressed.

**`interrupts.c`**
```c
volatile uint8_t button_event_detected[BUTTON_COUNT] = {0};

#pragma vector = PCINT0_vect
__interrupt void button_porta_routine(void)
{
    button_event_detected[BUTTON_OLED1_2] = 1;
    button_event_detected[BUTTON_OLED1_3] = 1;
}

#pragma vector = PCINT2_vect
__interrupt void button_portc_routine(void)
{
    button_event_detected[BUTTON_ONBOARD] = 1;
    button_event_detected[BUTTON_OLED1_1] = 1;
}
```

> 

**`interrupts.c`**
```c
extern volatile uint8_t button_event_detected[BUTTON_COUNT];
static uint8_t button_pressed[BUTTON_COUNT] = {0};

static const led_id_t button_to_led_map[BUTTON_COUNT] = {
    [BUTTON_ONBOARD] = LED_ONBOARD,
    [BUTTON_OLED1_1] = LED_OLED1_1,
    [BUTTON_OLED1_2] = LED_OLED1_2,
    [BUTTON_OLED1_3] = LED_OLED1_3};

void main(void)
{
  // inits and enable interrupts

  while (1)
  {
    // process all OLED1 buttons dynamically
    for (uint8_t i = BUTTON_OLED1_1; i <= BUTTON_OLED1_3; i++)
    {
      if (button_event_detected[i])
      {
        // button event detected, clear the flag
        button_event_detected[i] = 0;

        // debounce delay
        delay(10 * MILISECOND);

        // check if button was pressed, check if flag is cleared
        if (!button_read(i) && !button_pressed[i])
        {
          // set the flag 
          button_pressed[i] = 1;
          led_power_on(button_to_led_map[i]);
        } // check if button was released, check if flag is set
        else if (button_read(i) && button_pressed[i])
        {
          // clear the flag
          button_pressed[i] = 0;
          led_power_off(button_to_led_map[i]);
        }
      }
    }
    delay(1 * MILISECOND);
  }
}

```

---

## References & Resources
* AVR Microcontroller with Core Independent Peripherals and PicoPower technology (ATmega324PB)
* ATmega324PB Xplained Pro user guide
* OLED1 Xplained Pro user guide