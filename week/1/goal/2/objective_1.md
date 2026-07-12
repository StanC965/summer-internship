# Week: 1 - Goal : 2


## Objective 1: Turn on user LED0
---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[211]** | `CORE` | [x] Completed 
| **[212]** | `CORE` | [x] Completed 
| **[213]** | `CORE` | [x] Completed 
| **[214]** | `CORE` | [x] Completed 
| **[215]** | `CORE` | [x] Completed 
| **[216]** | `CORE` | [x] Completed 

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

#### Task 213
> **Question/Prompt:** How many GPIO (General Purpose Input Output) ports does the ATmega324PB microcontroller have in total?

> **Answer/Explanation:** 
> 5 (PORTA, PORTB, PORTC, PORTD, PORTE).

---

#### Task 214
> **Question/Prompt:** Search in the dev board User Guide the port and the pin to which LED0 is connected and how you should light up (or activate) LED0. Read carefully, repeatedly (maybe 10x), see if you really understand that information. You can correlate with the information from electronic schematic of our dev board. See if all these information match in your mind with the general knowledge on LEDs control acquired last week. Further correlate with microcontroller datasheet on how to configure the pins (chapter 16.2.1).

> **Answer/Explanation:** 
> LED0 is connected to Port C, Pin 7 (PC7). The user guide states that the LED can be activated by driving the connected I/O line to GND (logic low). This confirms an active-low configuration. One side of LED is tied to the board's power supply, and the other side leads to pin PC7. Current will only flow and light the LED when PC7 acts as a path to GND.
>
> Additional information states that controlling any I/O pin requires configuring specific register bits:
> - DDxn (part of data direction register)
> - PORTxn (part of port data register)
>
> where x is the port lettter (C) and n is the pin number (7).
>
> From the datasheet we extract the steps needed to light up LED0:
>
> 1. To allow PC7 to drive the line to GND, it must be an output. Therefore, we must write a `1` to the DDC7 bit inside the DDRC register.
> 2. To turn LED0 on, we must write a `0` to the PC7 bit inside PORTC. This physically drives the pin to GND, completing the active low circuit.
> 3. For further implementations, if we need to turn LED0 off, we write a `1` to PC7. This drives PC7 high, removing the voltage difference across the LED and stopping current flow.

---

#### Task 215
> **Question/Prompt:** Write a program code for light up the LED0. You need to take control over the registers implied in turning LED0 on. Compile and download the code. Run the code in order to see LED0 on. Congrats!

> **Answer/Explanation:** 
> LED0 uses PC7, which is port C, pin 7. We need to set the direction of the LED to output (write 1 to DDRC) and also drive the pin LOW (write 0 to PORTC) to turn the active low LED on. 

```
#include <iom324pb.h>

void main (void){
  
  // set PC as OUTPUT by setting bit 7 to 1
  DDRC |= 1 << 7;

  // drive PC7 LOW by clearing bit 7 to 0
  PORTC &= ~(1 << 7);
  
  while(1){
    // keep the controller running and the LED lit
  }

}
```

---

#### Task 216
> **Question/Prompt:** Program LED0 to be turned on for 1 second*, turned off for the next 1 second and so on (repeat the sequence).

> **Answer/Explanation:** 
> To achieve a visible blinking effect with a delay of 1 second, we cannot simply count to 1000 in a for loop (which is 1 second in miliseconds). The value 1000 represents miliseconds only when utilizing high level abstraction library functions. A hardware level CPU loop, however, measures time purely in clock cycles and instruction executuion states.
>
> ATmega324PB operates at a clock speed of 16 MHz. This means that a single clock takes exactly:

```math
T = \frac{1}{f} = \frac{1}{16\,MHz} = 62.5\,nanoseconds  
```

> Becuase code optimization is disabled for this project, the compiler does not strip away the empty for loop. Instead, it generates several assembly instructions, for every single instruction. While this makes execution slower than optimized code, each iteration still only takes a handful of clock cycles.
>
> To stall a 16 MHz processor for a full 1 second, we must pass a significantly larger counter value to accumulate enough clock cycles. Further more, because a standard 16 bit `int` in the AVR compiler maxes out at a value of 32,767, passing large values requires redefining the counter parameter to a 32 bit `long` to prevent an arithmetic integer overflow, which maxes out at 2,147,483,647.
>
> An iteration takes:

```math
time\,per\,iteration = nr.\,clock\,cycles * time\,per\,clock\,cycle 
```

> The final count:

```math
count = \frac{1,000,000,000\,ns}{time\,per\,iteration} 
```

> Since the task only got harder because of the previous observations, and also because now the issue of determining the number of clock cycles and whether or not the counter value was correctly chosen to represent 1 second have arisen, I decided to chose a value of 100000 to represent the '1 second delay'.

```c
#include <iom324pb.h>

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  
  // set PC as OUTPUT by setting bit 7 to 1
  DDRC |= 1 << 7;
  
  while(1){
    // drive PC7 LOW by clearing bit 7 to 0
    PORTC &= ~(1 << 7);
    delay(100000);
    
    // drive PC7 LOW by setting bit 7 to 1
    PORTC |= 1 << 7;
    delay(100000);
  }
  
}
```

---

## References & Resources
* [ATmega324PB Pin Configurations](http://content.alexandria.atmel.com/webhelp/GUID-74F8229E-4C43-4FA0-BE7D-1AA303C6F8A4-en-US-6/index.html?GUID-7CB50236-3F2B-4023-9C78-7F663A7B4801)
*  AVR Microcontroller with Core Independent Peripherals and PicoPower technology (ATmega324PB)
* ATmega324PB Xplained Pro user guide