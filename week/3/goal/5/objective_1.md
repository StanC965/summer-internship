# Week: 3 - Goal : 5


## Objective 1: Building from scratch a TASK SCHEDULER

---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[511]** | `CORE` | [x] Completed
| **[512]** | `CORE` | [x] Completed

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
>   - this formula only gives an exact interval if the (time x F_CPU) / prescaler) comes out as a whole number
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