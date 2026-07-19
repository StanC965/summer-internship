# Week: 2 - Goal : 4


## Objective 2: Start simple — NORMAL MODE of operation for TC0

---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[421]** | `CORE` | [x] Completed
| **[422]** | `CORE` | [x] Completed

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

---

