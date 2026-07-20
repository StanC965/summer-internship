# Week: 3 - Goal : 5


## Objective 3: Understanding DEBOUNCE with Task Scheduler

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[531]** | `STRETCH`  | [] Completed
| **[532]** | `STRETCH`  | [] Completed
| **[533]** | `CORE`     | [x] Completed
| **[534]** | `OPTIONAL` | [] Completed

---

#### Task 531
> **Question/Prompt:** Software Debounce
> **Answer/Explanation:**
> 

---

#### Task 532
> **Question/Prompt:** Hardware Debounce

> **Answer/Explanation:**
> 

---

#### Task 533
> **Question/Prompt:** The BOUNCE term applies to electric signal generated when we press the button. The DEBOUNCE term intervenes when we want to read the signal. Can be implemented by reading 5x times the same signal generated when we push the button. The readings are spaced-time apart with the help of the scheduler tasks. Finally the principle applied to the acquired 5 samples is the majority principle: all samples must be with the same value (00000 or 11111) to consider the button pressed or not-pressed. The samples can be stored temporary in a buffer (that means a variable whose bits are shifted to the left each time a new sample is acquired). The debounce is done continously, all the time: with other words it is like a 5 samples window which is moving along the signal. So one sample in, one sample out, one sample in, one sample out, etc. We can characterize the debounce in terms of time: debounce time = task of X ms * no. of samples, e.g. reading 5 samples within 10ms task => 50ms debounce time.

> **Answer/Explanation:**
> 

---

#### Task 534
> **Question/Prompt:** Use the UML Activity Diagram type to illustrate the debounce algorithm (within the same online tools you have used before).

> **Answer/Explanation:**
> 

---
