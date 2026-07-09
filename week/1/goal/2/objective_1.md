# Week: 1 - Goal : 2


## Objective 1: Turn on user LED0
---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[211]** | `CORE` | [x] Completed 
| **[212]** | `CORE` | [x] Completed 

---

#### Task 211
> **Question/Prompt:** Clean your main.c file and include the header file iom324pb.h using include directive (#include). The function main( ) should be of type void and it has no return statement because it is never returning! Compared to PC software program, the embedded software program has this unique characteristic: it is stuck in an infinite while(1) loop. Intentionally!!! Therefore your program must have this loop also.

> **Answer/Explanation:**

```
#include <iom324pb.h>

void main (void){
  
  while(1){
    
  }
}
```

---

#### Task 212
> **Question/Prompt:** How many pins does the PORTC port have? 

> **Answer/Explanation:** 
> 8 (PC[7:0]).

---

## References & Resources
* [ATMega324PB Pin Configurations](http://content.alexandria.atmel.com/webhelp/GUID-74F8229E-4C43-4FA0-BE7D-1AA303C6F8A4-en-US-6/index.html?GUID-7CB50236-3F2B-4023-9C78-7F663A7B4801)