# Week: 3 - Goal : 6


## Objective 2: Fast PWM MODE of operation for TC0

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[621]** | `CORE`     | [x] Completed
| **[622]** | `CORE`     | [x] Completed
| **[623]** | `CORE`     | [x] Completed
| **[624]** | `CORE`     | [x] Completed
| **[625]** | `STRETCH`  | [] Completed
| **[626]** | `STRETCH`  | [] Completed

---

#### Task 621
> **Question/Prompt:** The Fast PWM is an operating mode of TC0 timer. Having already some experience with ADC operation and Normal/CTC modes of operation for TC0, you are now able to study chapter 17 in the datasheet, looking for Fast PWM Mode. You should apply the same 8 identified steps as for the aforementioned operations.

> **Answer/Explanation:**
> 

---

#### Task 622
> **Question/Prompt:** Check on the boards (user guides, schematics) to what pins you can output a PWM signal and if those pins have LEDs connected !!! Not all pins can support/output PWM signals.

> **Answer/Explanation:**
> The pins that support PWM signals are: LED1 and LED2 from OLED1 and LED from IO1.

---

#### Task 623
> **Question/Prompt:** Construct a new module for PWM feature containing the appropriate functions (remember: initialization, atomic actions, etc.). Do the math for implementing into one single function the following 5 use cases with PWM:
> 
> - output a PWM signal with 100% duty cycle
> - output a PWM signal with 75% duty cycle
> - output a PWM signal with 50% duty cycle
> - output a PWM signal with 25% duty cycle
> - output a PWM signal with 0% duty cycle
> 
> Individually apply each case to the LED identified as supporting PWM.

> **Answer/Explanation:**
> - this module implements pwm on timer0 in mode: fast pwm, 8 bit, non invertingm top = 0xFF
> - OCR0A = (duty% x 255) / 100

| Duty      | OCR0A     
| :---      | :---       
| 100%	    | 255 (0xFF)  
| 75%	    | 191 (0xBF) 
| 50%	    | 128 (0x80) 
| 25%	    | 64  (0x40) 
| 0%	    | 0   (0x00)


**`main.c`**
```c
void main(void)
{
  led_init();

  pwm_init();
  pwm_start();

  __enable_interrupt();

  while (1)
  {
    pwm_set_duty_cycle(100);
    delay(3 * SECOND);

    pwm_set_duty_cycle(75);
    delay(3 * SECOND);

    pwm_set_duty_cycle(50);
    delay(3 * SECOND);

    pwm_set_duty_cycle(25);
    delay(3 * SECOND);

    pwm_set_duty_cycle(0);
    delay(3 * SECOND);
  }
}
```

**`pwm.c`**
```c
void pwm_init(void)
{
    PRR0 &= ~(1 << PRTIM0);

    TCCR0A = (1 << WGM01) | (1 << WGM00);
    TCCR0B = 0x00;
}

void pwm_start(void)
{
    TCCR0B |= (1 << CS00);
}

void pwm_set_duty_cycle(uint8_t duty_percent)
{
    __disable_interrupt();

    // edge case: 0%
    if (duty_percent == 0)
    {
        TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
        led_power_off(LED_IO1);
    }
    // edge case: 100%
    else if (duty_percent >= 100)
    {
        TCCR0A |= (1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);
        OCR0A = 0xFF;
    }
    else
    {
        TCCR0A |= (1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);
        // converts any requested duty-cycle percetange into the correct OCR0A value
        // using this formula since one full PWM period spans 255 counter steps
        // and OCR0A marks how many of those steps the pin stays in HIGH
        OCR0A = (uint8_t)(((uint16_t)duty_percent * PWM_RESOLUTION) / 100U);
    }

    __enable_interrupt();
}
```

---

#### Task 624
> **Question/Prompt:** Having the Task Scheduler as your best friend (!) design an application where you incrementally apply these use cases to the LED identified as supporting PWM. e.g. you can apply the signal in an incremental way: on the first run of 10ms task you apply 0% duty cycle, on the second you apply 25% duty cycle, on the third 50%, and so on and so forth, then start all over again

> **Answer/Explanation:**


**`scheduler_cfg.c`**
```c
void task_10ms(void)
{
    pwm_incremental_update();
}
```

**`pwm.c`**
```c
static const uint8_t pwm_duty_steps[PWM_STEP_COUNT] = {0, 25, 50, 75, 100};

void pwm_incremental_update(void)
{
    static uint8_t run_counter = 0;

    uint8_t step_index = run_counter % PWM_STEP_COUNT;
    pwm_set_duty_cycle(pwm_duty_steps[step_index]);

    run_counter++;
}
```

---

#### Task 625
> **Question/Prompt:** What is the duty cycle resolution of the PWM signals (= the smallest duty cycle % step you can increment with) that can be build on TC0? Number of steps: (<<< answer here). Step size (resolution in %): (<<< answer here)

> **Answer/Explanation:**
> 

---

#### Task 626
> **Question/Prompt:** Add a new feature to your PWM driver: the possibility to change the duty-cycle with 1% step size. You would build a new provided interface e.g. void pwm_dc(int param);

> **Answer/Explanation:**
> 

---





