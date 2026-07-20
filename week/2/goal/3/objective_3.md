# Week: 2 - Goal : 3


## Objective 3: Building a Control Panel - Internship's main application

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[331]** | `CORE`    | [x] Completed 
| **[332]** | `CORE`    | [x] Completed 
| **[333]** | `CORE`    | [x] Completed 
| **[334]** | `CORE`    | [x] Completed 

--- 

#### Task 331
> **Question/Prompt:** Construct your software program so that it can handle the 3 buttons from OLED1 extension board. The general behavior should be the following: when pressing button X then LED X is on, where X = 1,2,3, and when releasing button X then LED X is off. You have the freedom to choose what kind of implementation approach you prefer: polling the button state or trigger interrupts.

> **Answer/Explanation:**
> The buttons are connected to the following pins:
>  - 3 : PA0 - PCINT0  (BUTTON2)
>  - 4 : PA1 - PCINT1  (BUTTON3)
>  - 9 : PC1 - PCINT17 (BUTTON1)
>
> I created interrupt handlers for the buttons, and it is worth mentioning that both the onboard button and the oled1_1 button share an interrupt vector group, and also the oled1_2 and oled_3 button share an interrupt vector group.
> The main loop's read logic will check what button is actually pressed.

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

> Both the first and second group of the interrupt vectors handle multiple pins on PORTA, respectively PORTC. Since this vector is shared, any events detected on one of the pins trigger the routine. In this case, we set flags for both pins of each group, and we distinguish between them in the main loop.

**`main.c`**
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
  // led and button init and enable interrupts

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
        // we check here if the button which had an event detection
        // is actually active-low
        if (!button_read(i) && !button_pressed[i])
        {
          // set the flag to track that the button is held down
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

#### Task 332
> **Question/Prompt:** Modify your program so that when pressing button X on OLED1 a second time (X=1,2,3), only then LED X is off.

> **Answer/Explanation:**
> For this task I only changed the following line, which checks for second button press:

**`main.c`**
```c
 else if (!button_read(i) && button_pressed[i])
```

---

#### Task 333
> **Question/Prompt:** Add to the previous program the following behavior: when button SW0 is pressed then all LED X are off (no matter their current state on/off) and LED0 is on.

> **Answer/Explanation:**
> For this task I introduced the following lines, which check if a button press came from SW0, and if yes, LEDs 1-3 are turned off, and LED0 is turned on:

**`main.c`**
```c
        if (!button_read(i) && !button_pressed[i])
        { // check if SW0 was pressed
          if (i == BUTTON_ONBOARD)
          {
            for (uint8_t j = BUTTON_OLED1_1; j <= BUTTON_OLED1_3; j++)
            { 
              button_pressed[j] = 0;
              // SW0 pressed - turn LED1-3 OFF
              led_power_off(button_to_led_map[j]);
            }
            button_pressed[i] = 1;
            // SW0 pressed - turn LED0 ON
            led_power_on(button_to_led_map[i]);
            break;
          }
          // turn the other LEDs ON if they were pressed
          button_pressed[i] = 1;
          led_power_on(button_to_led_map[i]);
```

---

#### Task 334
> **Question/Prompt:** Your customer, BMW, has requested to implement a prototype for a central control panel in the car.
> REQUIREMENTS:
> 
> The HVAC vents are positioned to blow the AC in 3 directions: left, central and right. Each vent has its corresponding control button and LED for visual confirmation to the driver about the enabled function of that particular vent. They are the buttons and LEDs on OLED1 board. Each button push will toggle the function of the corresponding vent and will toggle accordingly also the corresponding LED. No crosstalks are allowed.
> 
> For comfort security BMW has requested that an additional button, SW0, called master control, when it is pushed to block the function of the entire control panel. The BLOCKED state of the control panel will be implemented as follows:
> 
> - LED0 on ATmega324PB main board is activated
> - pushing on OLED1 buttons will have no effect on vent and LED indicators from OLED1 (they stay OFF)
> - pushing on any OLED1 button will fast blink the LED0 indicating that the panel is blocked
> To unblock the panel it is needed to push the SW0 master control again (and the normal functionality is re-established).

> **Answer/Explanation:**
> For this task I implemented a new module called `HVAC control`. The main control loop features the requested functionalities:

**`hvac_control.c`**
```c
void hvac_control_process(void)
{
    if (button_event_detected[BUTTON_ONBOARD])
    {
        button_event_detected[BUTTON_ONBOARD] = 0;
        delay(10 * MILISECOND);

        if (!button_read(BUTTON_ONBOARD) && !button_pressed[BUTTON_ONBOARD])
        {
            // SW0 was pushed - it blocks the state of the control panel
            button_pressed[BUTTON_ONBOARD] = 1;
            hvac_state = STATE_BLOCKED;
            // SW0 was pushed - light up LED0
            led_power_on(button_to_led_map[BUTTON_ONBOARD]);
            // SW0 was pushed - turn off all other active LEDs
            turn_off_all_vents();
        }
        else if (!button_read(BUTTON_ONBOARD) && button_pressed[BUTTON_ONBOARD])
        {
            // SW0 was pushed again - it unlocks the state of the control panel
            button_pressed[BUTTON_ONBOARD] = 0;
            hvac_state = STATE_NORMAL;
            // SW0 was pushed again - turn off LED0
            led_power_off(button_to_led_map[BUTTON_ONBOARD]);
        }
    }
    for (uint8_t i = BUTTON_OLED1_1; i <= BUTTON_OLED1_3; i++)
    {
        if (button_event_detected[i])
        {
            button_event_detected[i] = 0;

            delay(10 * MILISECOND);

            if (!button_read(i))
            {
                
                if (hvac_state == STATE_BLOCKED)
                {
                    // SW0 was pushed 
                    // if other buttons are pushed then alert by 
                    // blinking LED0
                    led_blink_fast(button_to_led_map[BUTTON_ONBOARD]);
                    
                    // keep LED0 on
                    led_power_on(button_to_led_map[BUTTON_ONBOARD]);
                }
                else if (hvac_state == STATE_NORMAL)
                {
                    if (!button_pressed[i])
                    {
                        // SW0 was pushed again
                        // light up LEDs
                        button_pressed[i] = 1;
                        led_power_on(button_to_led_map[i]);
                    }
                    else if (button_pressed[i])
                    {
                        button_pressed[i] = 0;
                        led_power_off(button_to_led_map[i]);
                    }
                }
            }
        }
    }
}
```

---

## References & Resources
* AVR Microcontroller with Core Independent Peripherals and PicoPower technology (ATmega324PB)
* ATmega324PB Xplained Pro user guide
* OLED1 Xplained Pro user guide