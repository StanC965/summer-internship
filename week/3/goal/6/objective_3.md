# Week: 3 - Goal : 6


## Objective 3: Complex behaviors

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[631]** | `CORE`     | [] Completed
| **[632]** | `CORE`     | [] Completed
| **[633]** | `OPTIONAL` | [] Completed
| **[634]** | `OPTIONAL` | [] Completed

---

#### Task 631
> **Question/Prompt:** Build the next behavior for the LED identified as supporting PWM. The sequence described will be repetitive with pause (= PWM duty cycle 0%) of 3s. Be very attentive as the graphic below shows not the duty-cycle of a PWM signal, but the variation (!!!) of the PWM duty-cycle across time. The duty-cycle resolution you choose for ramping up PWM from 0% to 100% is up-to-you.

> **Answer/Explanation:**

**`pwm.h`**
```c
typedef enum
{
    SEQ_RAMP_UP = 0,
    SEQ_HOLD_HIGH_1,
    SEQ_DIP_LOW_1,
    SEQ_HOLD_HIGH_2,
    SEQ_DIP_LOW_2,
    SEQ_HOLD_HIGH_3,
    SEQ_RAMP_DOWN,
    SEQ_PAUSE
} pwm_seq_phase_t;

#define SEQ_RAMP_STEP_PERCENT   (5U)    
#define SEQ_HOLD_TICKS          (10U)   
#define SEQ_PAUSE_TICKS         (30U) 
```

**`pwm.c`**
```c
void pwm_sequence_update(void)
{
    static pwm_seq_phase_t phase = SEQ_RAMP_UP;
    static uint8_t duty = 0;
    static uint8_t tick_count = 0;

    switch (phase)
    {
    case SEQ_RAMP_UP:
        pwm_set_duty_cycle(duty);
        if (duty >= 100)
        {
            phase = SEQ_HOLD_HIGH_1;
            tick_count = 0;
        }
        else
        {
            duty += SEQ_RAMP_STEP_PERCENT;
        }
        break;

    case SEQ_HOLD_HIGH_1:
    case SEQ_HOLD_HIGH_2:
    case SEQ_HOLD_HIGH_3:
        pwm_set_duty_cycle(100);
        if (++tick_count >= SEQ_HOLD_TICKS)
        {
            tick_count = 0;
            phase = (phase == SEQ_HOLD_HIGH_1) ? SEQ_DIP_LOW_1 : (phase == SEQ_HOLD_HIGH_2) ? SEQ_DIP_LOW_2
                                                                                            : SEQ_RAMP_DOWN;
        }
        break;

    case SEQ_DIP_LOW_1:
    case SEQ_DIP_LOW_2:
        pwm_set_duty_cycle(0);
        if (++tick_count >= SEQ_HOLD_TICKS)
        {
            tick_count = 0;
            phase = (phase == SEQ_DIP_LOW_1) ? SEQ_HOLD_HIGH_2 : SEQ_HOLD_HIGH_3;
        }
        break;

    case SEQ_RAMP_DOWN:
        pwm_set_duty_cycle(duty);
        if (duty == 0)
        {
            phase = SEQ_PAUSE;
            tick_count = 0;
        }
        else
        {
            duty -= SEQ_RAMP_STEP_PERCENT;
        }
        break;

    case SEQ_PAUSE:
        pwm_set_duty_cycle(0);
        if (++tick_count >= SEQ_PAUSE_TICKS)
        {
            tick_count = 0;
            phase = SEQ_RAMP_UP;
            duty = 0;
        }
        break;
    }
}
```

---

#### Task 632
> **Question/Prompt:** Build the next behavior for the LED identified as supporting PWM. Be attentive to the indications of the scale!

> **Answer/Explanation:**
> 

---

#### Task 633
> **Question/Prompt:** Build an application varying the PWM signal applied to an LED based on sinus function, f(x) = sin(x). Note that it is impractical to look over full and continous range of f(x) values, therefore you should consider only few discrete points (time, dc%)

> **Answer/Explanation:**
> 

---

#### Task 634
> **Question/Prompt:** The Heart Beat illumination pattern was developed by Marquardt. In Reference Documents folder you will find the HeartBeat_illumination_pattern.xlsx file which presents you the variation of the PWM signal. Build an application based on the Heart Beat illumination pattern.

> **Answer/Explanation:**
> 

---



