# Week: 3 - Goal : 5


## Objective 1: Building from scratch a TASK SCHEDULER

---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[511]** | `CORE` | [x] Completed

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