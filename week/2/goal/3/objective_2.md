# Week: 2 - Goal : 3


## Objective 2: Coding rules

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[321]** | `CORE`    | [x] Completed 
| **[322]** | `STRETCH` | [x] Completed 
| **[323]** | `CORE`    | [x] Completed 
| **[324]** | `STRETCH` | [x] Completed 

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

#### Task 322
> **Question/Prompt:** Watch this clip on magic numbers

> **Answer/Explanation:**
> 

--- 

#### Task 323
> **Question/Prompt:** Re-design your code wrote so far using the following naming convention: name your functions and variables with a prefix which represents the name of the module it belongs to. e.g. if led is my module's name, then:
> - led_set_state( ON ) will be the name of the function setting the state ON for that LED
> - unsigned char led_state; will be your variable declaration

> **Answer/Explanation:**
> 

--- 

#### Task 324
> **Question/Prompt:** Watch this clip on naming

> **Answer/Explanation:**
> 

--- 

