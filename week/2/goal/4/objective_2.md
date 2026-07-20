# Week: 2 - Goal : 4


## Objective 2: Start simple — NORMAL MODE of operation for TC0

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[421]** | `CORE`     | [x] Completed
| **[422]** | `CORE`     | [x] Completed
| **[423]** | `CORE`     | [x] Completed
| **[424]** | `OPTIONAL` | [x] Completed
| **[425]** | `CORE`     | [x] Completed
| **[426]** | `STRETCH`  | [] Completed
| **[427]** | `STRETCH`  | [] Completed
| **[428]** | `STRETCH`  | [] Completed
| **[429]** | `STRETCH`  | [] Completed

---

#### Task 421
> **Question/Prompt:** Your big task now is to make TC0 work in NORMAL MODE (from 0x00 to 0xFF) obtaining an interrupt at overflow. After reading the TC0 datasheet information (registers & functionalities) you should have these questions.

> **Answer/Explanation:**
> 

---

#### Task 422
> **Question/Prompt:** Introduce the corresponding interrupt service routine, breakpoint and hit!!!

> **Answer/Explanation:**

**`interrupts.c`**
```c
volatile uint32_t timer0_overflow_count = 0;

#pragma vector = TIMER0_OVF_vect
__interrupt void timer0_overflow_routine(void)
{
    timer0_overflow_count++;
}
```

**`main.c`**
```c
void main(void)
{
  timer_init();

  __enable_interrupt();
  
  timer_start_no_prescaling();

  while (1)
  {
  }

}
```

> For implementing the timer module, I followed the checklist:

**`timer.c`**
```c
void timer_init(void)
{
    timer_enable_peripheral_clock();
    timer_select_normal_mode();
    timer_configure_control_settings();
}

void timer_enable_peripheral_clock(void)
{

    PRR0 &= ~BIT_MASK(PRTIM0);
}

void timer_select_normal_mode(void)
{
    TCCR0A = 0x00;
}

void timer_configure_control_settings(void)
{
    timer_enable_overflow_interrupt();
}

void timer_enable_overflow_interrupt(void)
{
    TIMSK0 |= (1 << TOIE0);
}
```

---

#### Task 423
> **Question/Prompt:** Do the math calculations for minimum and maximum of real time you can natively measure with NORMAL MODE until overflow, all prescalers considered. It is a combination of:
>
> - HOW FAST timer can count: system clock frequency (1MHz) with prescaler (1, 8, ..., 1024) results in the counting frequency
> - HOW MUCH timer can count: TC0 maximum value for overflow (0xFF)
> - MIN => _ MAX => _
>
> How can you extend the maximum real time measured in NORMAL MODE? 

> **Answer/Explanation:**
> ### core constants and variables
> - system clock frequency ($F_{CPU}$): $1\text{ MHz} = 1,000,000\text{ Hz}$
> - how much the timer can count ($N_{steps}$): In Normal Mode, the 8 bit timer counts from 0x00 to 0xFF. This means an overflow interrupt is raised precisely every 256 steps.
> - prescaler values ($P$): Available division factors are 1, 8, 64, 256, and 1024.
> 
> The general formula to calculate the time elapsed until an overflow occurs is:

$$\text{Time} = \frac{1}{\text{Counting Frequency}} \times N_{steps} = \frac{\text{Prescaler}\:(P)}{F_{CPU}} \times 256$$

> ### prescaler = 1 (no prescaling)
> - counting frequency = $\frac{1,000,000\text{ Hz}}{1} = 1\text{ MHz}$
> - time to overflow = $\frac{1}{1,000,000\text{ Hz}} \times 256 = 0.000256\text{ seconds} = \mathbf{256\:\mu\text{s}}$
>
> ### prescaler = 8
> - counting frequency = $\frac{1,000,000\text{ Hz}}{8} = 125\text{ kHz}$
> - time to overflow = $\frac{1}{125,000\text{ Hz}} \times 256 = 0.002048\text{ seconds} = \mathbf{2.048\text{ ms}}$
>
> ### prescaler = 64
> - counting frequency = $\frac{1,000,000\text{ Hz}}{64} = 15.625\text{ kHz}$
> - time to overflow = $\frac{1}{15,625\text{ Hz}} \times 256 = 0.016384\text{ seconds} = \mathbf{16.384\text{ ms}}$
>
> ### prescaler = 256
> - counting frequency = $\frac{1,000,000\text{ Hz}}{256} = 3,906.25\text{ Hz}$
> - time to overflow = $\frac{1}{3,906.25\text{ Hz}} \times 256 = 0.065536\text{ seconds} = \mathbf{65.536\text{ ms}}$
>
> ### prescaler = 1024
> - counting frequency = $\frac{1,000,000\text{ Hz}}{1,024} = 976.5625\text{ Hz}$
> - time to overflow = $\frac{1}{976.5625\text{ Hz}} \times 256 = 0.262144\text{ seconds} = \mathbf{262.144\text{ ms}}$
> 
> **MIN =>** $256\:\mu\text{s}$ (With a prescaler of 1)
> 
> **MAX =>** $262.144\text{ ms}$ (With a prescaler of 1024)
> 
> The maximum real time duration can be extended by using a software counter variable (e.g., a volatile uint32_t overflow_count) inside the TIMER0_OVF ISR. Every time the hardware tracking flag reaches overflow and enters the routine, this variable is incremented. Multiplying that count by whichever fixed overflow period corresponds to the chosen prescaler (e.g., 26.144 ms if using prescaler 1024) extends the measurable range.

---

#### Task 424
> **Question/Prompt:** What can you say about the jitter (deviation in time) introduced when extending the maximum real time measured in NORMAL MODE?

> **Answer/Explanation:**
> When extending the real time measurement in Normal Mode using a software variable, the hardware counter itself remains perfectly stable, but the software variable introduces timing jitter due to interrupt execution delays. 
> This variation occurs because the CPU must complete its current instruction before jumping to the ISR. 
> Additionally, if other background interrupts are currently executing, or if global interrupts are temporarily locked out by critical atomic operations, the execution of the timer module's counter logic is stalled. 
> This delay introduces a minor timing deviation, or jitter, equal to the length of those blocking instructions.

---

#### Task 425
> **Question/Prompt:** Time your LED0 on and off at 1 second interval (exercise 216 revisited! but this time without software delays!) managed by TC0 Timer working in NORMAL MODE of operation with the help of interrupt service routine.

> **Answer/Explanation:**
> Since Normal Mode overflows at a fixed 256 steps, numbers like 1 second cannot be hit directly. Instead of letting TCNT0 start at 0x00, it should be preloaded with a starting value. That way the timer has to count up from the preloaded value to 0xFF.
>
> - The prescalerwas selected to be 64.
> - For the overflow period, since 1 second is equal to 1000 ms, a period this value evenly is a good candidate. 8 ms divides it into 125.
> - The ticks needed are equal to (8 * 1000 ms) / 64, which is 125. This results into a preload value of 131 (256 - ticks needed).
> Each overflow with a preload now takes exaclty 8ms, so we get 125 overflows.

**`timer.h`**
```c
#define TIMER_PRESCALER_64            (0X03U)
#define TIMER0_PRELOAD_VALUE          (131U)
#define OVERFLOWS_PER_SECOND          (125U)
```

**`timer.c`**
```c
void timer_configure_control_settings(void)
{
    TCNT0 = TIMER0_PRELOAD_VALUE;
    timer_enable_overflow_interrupt();
}

void timer_start_prescaler_64(void)
{
    TCCR0B &= ~TCCR0B_CS_MASK;
    TCCR0B |= (TIMER_PRESCALER_64 & TCCR0B_CS_MASK);
}

```

**`interrupts.c`**
```c
#pragma vector = TIMER0_OVF_vect
__interrupt void timer0_overflow_routine(void)
{
    TCNT0 = TIMER0_PRELOAD_VALUE;

    static uint8_t overflow_count = 0;
    overflow_count++;

    if (overflow_count >= OVERFLOWS_PER_SECOND)
    {
        overflow_count = 0;
        led_toggle(LED_ONBOARD);
    }
}
```

---

#### Task 426
> **Question/Prompt:** What min, max frequency would have the signal on LED0 toggled from within ISR in case of min, max prescalers? FREQ MIN => _ FREQ MAX => _

> **Answer/Explanation:**
> 

---

#### Task 427
> **Question/Prompt:** Use button SW0 to cycle through the possible frequencies (5 prescalers = 5 different frequencies). Use LED0 for your demonstration.

> **Answer/Explanation:**
> 

---

#### Task 428
> **Question/Prompt:** Build a 5 seconds countdown timer using the 5 LEDs you have on all the boards: the countdown shall start when SW0 is pressed. The initial system state is that all LEDs are on, then for each substracted second one LED goes off.

> **Answer/Explanation:**
> 

---

#### Task 429
> **Question/Prompt:** Re-design your BMW Control Panel Application with the introduction of timer feature. You can e.g. introduce a timer managed delay or a reading of the button from ISR.

> **Answer/Explanation:**
> 

---





