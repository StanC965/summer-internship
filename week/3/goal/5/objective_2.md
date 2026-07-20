# Week: 3 - Goal : 5


## Objective 2: Ambient Light Application REVISITED

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[521]** | `CORE`     | [x] Completed

---

#### Task 521
> **Question/Prompt:**  A task is executed when the corresponding flag of the time slice (e.g. 50ms) is set by the flag manager. You can populate a task with any function call you want. Thinking about your application as a sum of periodic events it is like designing your application to work in a task based environment, or with other words you are doing task oriented application design.
>
> In conclusion, re-organize your scheduler module as follows:
>
> - scheduler.c, contains schedule_dispatcher, schedule_flags_management functions; acts as the collection of these lollipops
> - scheduler.h, contains prototypes of provided functions
> - scheduler_cfg.c, contains initially the tasks empty bodies and after you decide what to connect with that task (what function to be called when task is executed) contains that function call; acts as the collection of these hooks
> - scheduler_cfg.h, contains prototypes of required functions

> **Answer/Explanation:**
> 

