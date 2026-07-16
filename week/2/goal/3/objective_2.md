# Week: 2 - Goal : 3


## Objective 2: Coding rules

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[321]** | `CORE`    | [x] Completed 
| **[322]** | `STRETCH` | [x] Completed 

--- 

#### Task 321
> **Question/Prompt:** You need to avoid using magic numbers in the code. They are numbers which at the moment you write the code they make perfect sense for you and only for you, but the drawback is that it will be non-sense for the colleague that will make a code-review over your code (which frequently happens in real life projects). Even for yourself, they will become non-sense after 3 months of not working with that code, you will ask "what was I thinking here?!". So re-code your program and cover all these magic numbers with #defines as in the example:

```c
// change... set_direction(2,7,1);  ...to...
#define PORT_B   2
#define PIN_NUMBER_7   7
#define OUTPUT   1
/******************some code here*****************************/
set_direction(PORT_B, PIN_NUMBER_7, OUTPUT);
/******************************************************************/
```

> **Answer/Explanation:**
> 

---