# Week: 2 - Goal : 4


## Objective 4: Integration challenge

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[441]** | `CORE`     | [] Completed

---

#### Task 441
> **Question/Prompt:** You are a member of the software development team for application Car Crash Management. The requirement (1) for today is to integrate in your program the module called CarCrashDetection (You can find it in the folder Reference Documents). This module was developed by our colleagues in Pune, India, where Marquardt has a subsidiary. The module offers an interface unsigned char GetCarCrashDetectionStatus(void) which returns 1 in case of detection of a frontal impact with another car and returns 0 in all other cases. The requirement (2) for today is that after the correct integration of module CarCrashDetection, you should command the explosion of the airbag caps for the driver and the passenger. The time window to do this is [ 650µs – 800µs ]. So, no later than 800µs, but also no earlier than 650µs!!! Measurements are started from the moment when your program is notified that has been detected a frontal accident with another car. (For our safety, the airbag caps explosion will be simulated by lighting up an LED :)).

> **Answer/Explanation:**

> The value I chose to command the explosion of the airbag sits right between the min and max of the range, which is 724.

**`timer.c`**
```c
void airbag_timer_configure(void)
{
    timer1_enable_peripheral_clock();

    TCCR1A = BIT_MASK(COM1A1);                  
    TCCR1B = BIT_MASK(WGM12);                   

    OCR1A = 724;                            
}

void airbag_timer_start(void)
{
    TCNT1 = 0x0000;
    TCCR1B |= BIT_MASK(CS10);                  
}
```

> The function that returns the car crash status is seeded, becuase it reseeds wih the literal constant on every call.
> - srand(31) produces the same first output every time, so the function returns the same fixed value on every call, which doesn't really demonstrate a state transition.
> 
> I changed that line to be able to get a different value each time the function is called.

**`timer.c`**
```c
#include "CarCrashDetection.h"

void main(void)
{
  led_init();

  airbag_timer_configure();

  __enable_interrupt();

  while (1)
  {
    if (GetCarCrashDetectionStatus() == CRASH)
    {
      airbag_timer_start();
      break;
    }
  }

  while (1)
  {
  }
}
```

---





