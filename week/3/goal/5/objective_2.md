# Week: 3 - Goal : 5


## Objective 2: Ambient Light Application REVISITED

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[521]** | `CORE`     | [x] Completed
| **[522]** | `CORE`     | [x] Completed
| **[523]** | `STRETCH`  | [x] Completed

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

---

#### Task 522
> **Question/Prompt:**  Go to Ambient Light Application and refactor the code as follows:

> - encapsulate/hide the data result to adc module (use static keyword)
> - provide a "get" interface / function to use the data result in other modules, e.g. adc_get_data( );
> - make use of task scheduler to schedule the start of conversion, getting and using the data result for ambient light indicator (the 3 LEDs)

> **Answer/Explanation:**
> 

---

#### Task 523
> **Question/Prompt:**  Use an online tool for UML diagrams to make a diagram for connections you decided between scheduler module and other modules of your program. Use a UML component diagram type and the lollipop notation as above. Highlight the provided/required functions/tasks. e.g. online tools: draw.io, smartdraw.com, visual-paradigm.com.

> **Answer/Explanation:**
> 

---


