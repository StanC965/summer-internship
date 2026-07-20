# Week: 3 - Goal : 5


## Objective 1: Building from scratch a TASK SCHEDULER

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[511]** | `CORE`     | [x] Completed
| **[512]** | `CORE`     | [x] Completed
| **[513]** | `CORE`     | [x] Completed
| **[514]** | `CORE`     | [x] Completed
| **[515]** | `CORE`     | [x] Completed
| **[516]** | `OPTIONAL` | [] Completed

---

#### Task 511
> **Question/Prompt:** First we relied on the while(1) loop to make the CPU go through our functions calls and execute those functions. Then we added interrupts, forcing the CPU to respond to events with routines execution. We had no concern about the "time" the CPU is spending with a particular function execution. A task scheduler is about that: taking care of CPU spent time on functions execution.
>
> Because "CPU time" is a resource, we would like to share this resource cooperatively among the functions from our program. Therefore we allocate a "time slot" or "time slice" for each function. Time slot/slice is the time passed between two consecutive timer interrupts. Time slots are periodic as timer interrupts are periodic. So each function has its CPU execution between two timer interrupts. How you trigger the execution of a function? Allocate a flag for each function and activate that flag for the time slot you want the execution to happen. Flags are activated within the ISR. This selective activation of flags is called flags management and it's similar to what you exercised last week by extending real time measurements beyond the maximum timings TC0 could provide.
>
> One more thing remains to do before scheduling is complete: looping through the flags and check if they are activated. If yes, then it's time to call that particular function to which this time slice has been allocated.
>
> At its core, a task scheduler consists of:
> - system tick (based on timer interrupts)
> - flags manager
> - tasks dispatcher

> **Answer/Explanation:**
> 

---

#### Task 512
> **Question/Prompt:** Choose a timer that will be dedicated to construct the system tick, e.g. TC0 or TC1. Set the timer for interrupts at 10ms precise interval. ATTENTION! in order for you to obtain the most accurate 10ms interval you have to research what is the best setup. So, play around with:
>
> - the initial settings for oscillator (uncheck the option "Divide clock by 8 internally" and/or choose external oscillator)
> - the 8bit vs. 16bit timers
>
> Remember that you are looking for the smallest deviation/offset from the 10ms mark... and make a final decision! Now you have an accurate system tick. As file organization is concerned, this interrupt service routine should be placed in the corresponding timer module. The timer you choose will remain dedicated to do the scheduling and you cannot use it for something else in your program.

> **Answer/Explanation:**
> - OCR = ((time x F_CPU) / prescaler) - 1
>   - this formula only gives an exact interval if the (time x F_CPU) / prescaler comes out as a whole number
>   - if not, it is more complicated
>  
> - time = 10 ms = 0.01 s
>
> 1. With the Divide clock by 8 internally checked
> - ticks needed = (0.01 x 1000000) / P
> - for TC0 (8 bit, max OCR 225): 

| prescaler  |ticks     | fits in 8 bit
| :---       | :---     | :--- 
| 1          | 10000    | No
| 8          | 1250     | No
| 64         | 156.25   | Not whole
| 256        | 39.0625  | Not whole
| 1024       | 9.77     | Not whole

> - for TC1 (16 bit, max OCR 65535): 

| prescaler  |ticks     | fits in 8 bit
| :---       | :---     | :--- 
| 1          | 10000    | Yes
| 8          | 1250     | Yes

> For this specific target the 16 bit timer is better, because it can express 10ms in one shot instead of needing accumulated overflows.
> 
> 2. With the Divide clock by 8 internally unchecked
> - ticks needed = (0.01 x 8000000) / P
> - for this option, prescaler 8 is 10000
>
> - both 1MHz and 8MHz hit an exact 10ms with TC1. 
>
> 3. With an external oscillator
> - typically more accurate and stable than the internal RC oscillator
> - the board features an external 16 MHz crystal oscillator
> - in this case, an 16 bit timer with prescaler 8 is equal to 20000

---

#### Task 513
> **Question/Prompt:** Starting with 10ms period build other longer periods of time: 50ms, 100ms, 500ms, 1000ms. Dedicate flag variables for each period. Optionally you can add more periods. You can gather all these into a single function, e.g. void scheduler_flags_management (void). Call it from within the ISR. As file organization is concerned, this flags management function should be placed in scheduler module.

> **Answer/Explanation:**

**`scheduler.c`**
```c
static volatile uint32_t scheduler_tick_counter = 0;

volatile uint8_t scheduler_flag_10ms = 0;
volatile uint8_t scheduler_flag_50ms = 0;
volatile uint8_t scheduler_flag_100ms = 0;
volatile uint8_t scheduler_flag_500ms = 0;
volatile uint8_t scheduler_flag_1000ms = 0;

void scheduler_flags_management(void)
{
    scheduler_flags_10ms = 1;
    scheduler_tick_counter++;

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_50MS) == 0)
    {
        scheduler_flag_50ms = 1;
    }

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_100MS) == 0)
    {
        scheduler_flag_100ms = 1;
    }

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_500MS) == 0)
    {
        scheduler_flag_500ms = 1;
    }

    if ((scheduler_tick_counter % SCHEDULER_TICK_FOR_1000MS) == 0)
    {
        scheduler_flag_1000ms = 1;
    }
}
```

**`interrupts.c`**
```c
#pragma vector = TIMER1_COMPA_vect
__interrupt void timer1_compare_a__routine(void)
{
  scheduler_flags_management();
}
```

---

#### Task 514
> **Question/Prompt:** Inside the while(1) loop you will check for the flags associated to the defined time slots and if they are set, then the associated function will be called. After the call, that particular flag must be reset in order to avoid the second call of the same function per current time slice when while(1) is re-entered. The final result of these constructs will be that each function call is time-spaced apart by a time slice of 10ms. Precisely! What a schedule!!! It is a cooperative schedule because functions are not prioritized, they do not interrupt each other.

> **Answer/Explanation:**

**`main.c`**
```c
  while (1)
  {
    if (scheduler_flag_10ms)
    {
      scheduler_flag_10ms = 0;
    }

    if (scheduler_flag_50ms)
    {
      scheduler_flag_50ms = 0;
    }

    if (scheduler_flag_100ms)
    {
      scheduler_flag_100ms = 0;
    }

    if (scheduler_flag_500ms)
    {
      scheduler_flag_500ms = 0;
    }

    if (scheduler_flag_1000ms)
    {
      scheduler_flag_1000ms = 0;
    }
  }
```

---

#### Task 515
> **Question/Prompt:** A final makeup for file organization to be complete:
>
> - replace the particular function calls with generic function calls (these are tasks), e.g. task_500ms( ); Within the body of the generic functions you now relocate the call to particular functions.

```c
void task_500ms (void) {
    led_on( );
}
```

> This relocation and generic functions creation is a nice way to prepare our task scheduler to be used in any other context just by replacing the led_on() call. 2. relocate the while(1) loop inside void schedule_tasks_dispatcher (void) function, which will be the core of the task scheduler. Relocate this function in the scheduler module and call it from within the main module (in similar way as Arduino Framework does with loop ( ) function).

> **Answer/Explanation:**

**`scheduler.c`**
```c
void scheduler_tasks_dispatcher(void)
{
    while (1)
    {
        if (scheduler_flag_10ms)
        {
            scheduler_flag_10ms = 0;
            task_10ms();
        }

        if (scheduler_flag_50ms)
        {
            scheduler_flag_50ms = 0;
            task_50ms();
        }

        if (scheduler_flag_100ms)
        {
            scheduler_flag_100ms = 0;
            task_100ms();
        }

        if (scheduler_flag_500ms)
        {
            scheduler_flag_500ms = 0;
            task_500ms();
        }

        if (scheduler_flag_1000ms)
        {
            scheduler_flag_1000ms = 0;
            task_1000ms();
        }
    }
}
```

---

#### Task 516
> **Question/Prompt:**  Can you improve the flags storage so that they would occupy less memory? Experiment with your code.

> **Answer/Explanation:**
>

---