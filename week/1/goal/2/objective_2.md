# Week: 1 - Goal : 2


## Objective 2: Turn on external LEDs
---

### Task Checklist & Results

| Task ID   | Type      | Status
| :---      | :---      | :--- 
| **[221]** | `CORE`    | [x] Completed 
| **[222]** | `CORE`    | [x] Completed 
| **[223]** | `CORE`    | [x] Completed 
| **[224]** | `CORE`    | [x] Completed 
| **[225]** | `STRETCH` | [x] Completed 

---

#### Task 221
> **Question/Prompt:** Check the electronic schematic of the ATMega324PB development board. Is there any resistor connected with the integrated LED0 in order to protect it? What value has that resistor?

> **Answer/Explanation:**
> There is a current limiting resistor connected in series with the LED to protect it from burning. R214 has a value of 330 ohms.

![alt text](../../../../images/w1g2obj2t221.PNG)

---

#### Task 222
> **Question/Prompt:**  In Reference_Documents folder you find the electronic schematics for OLED1 and IO1 boards (check .zip files). Can you figure it out, just by reading the schematics (NOT the User Guide!!!), how to turn on the contained LEDs for each board?

> **Answer/Explanation:**
> Both schematics show the same exact hardware configuration for driving the LED, which is known as an active low configuration:

![OLED board](../../../../images/w1g2obj2t222_1.PNG)
![IO1 board](../../../../images/w1g2obj2t222_2.PNG)

> 1. The top of each LED circuit is connect to VCC (labeled VCC_TARGET), which is the constant positive voltage supply.
> 2. Current flows from VCC through a resistor with a value of 680 ohms (R101, R102, R103). This resistor is critical to prevent the LED from burning.
> 3. The current enters pin 2 (the anode) and exits through pin 1 (cathode).
> 4. The cathode is directly tied to the microcontroller control lines (LED1, LED2, LED3).
>
> To turn the LEDs on, the microcontroller pins connected to LED1, LED2, and LED3 must be configured as outputs and driven to LOW.
> When the pins are LOW, a voltage potential is created between VCC and the microcontroller pins. Current then flows from the power supply, through the resistor, through the LED and lighting it up, and lastly it sinks directly into the microcontroller pin to GND.

> Even tough the physical hardware wiring looks the same, I assume that there must be a slight difference between the two boards, since the LEDs on the OLED1 board work just as encounterd before in this week's goals, but the LED on the IO1 board uses pulse width modulation (PWM).

---

#### Task 223
> **Question/Prompt:** Check that OLED1 extension board is connected to EXT1 header. Program all 3 LEDs to be turned on at once. Double check(!) with User Guide for OLED1 to see if schematics information matches with regards to LEDs activation.

> **Answer/Explanation:**
> I connected the OLED1 board to the EXT1 header, and also checked the information regarding LED activation, which states the following: The LEDs can be activated by driving the connected I/O line low. This aligns with previous findings.
>
> In order to turn the LEDs on, I looked for the pins in the EXT1 header in the OLED1 user guied, which are pin 7, 8, and 6 for LED1, LED3, and LED3 respectively. Then, using these pins, I looked in the ATmega user guide, and found the corresponding pins, which are PD5, PD4 and PA3.

```c
#include <iom324pb.h>

void main (void){
  
  // set PD5 as OUTPUT by setting bit 5 to 1
  DDRD |= 1 << 5;
  // set PD4 as OUTPUT by setting bit 4 to 1
  DDRD |= 1 << 4;
  // set PA3 as OUTPUT by setting bit 3 to 1
  DDRA |= 1 << 3;

  // drive PD5 LOW by clearing bit 5 to 0
  PORTD &= ~(1 << 5);
  // drive PD4 LOW by clearing bit 4 to 0
  PORTD &= ~(1 << 4);
  // drive PA3 LOW by clearing bit 3 to 0
  PORTA &= ~(1 << 3);
  
  while(1){
    // keep the controller running and the LED lit
  }
  
}
```

---

#### Task 224
> **Question/Prompt:** Make a program where LEDs are individually turned on and off (for half a second) in a repetitive sequence.

> **Answer/Explanation:**
> For this task I reused the delay function created for objective 1 task 216, but with half the value of the previous counter.

```c
#include <iom324pb.h>

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  
  // set PD5 as OUTPUT by setting bit 5 to 1 
  DDRD |= 1 << 5;
  // set PD4 as OUTPUT by setting bit 4 to 1
  DDRD |= 1 << 4;
  // set PA3 as OUTPUT by setting bit 3 to 1
  DDRA |= 1 << 3;
  
  while(1){
    // drive PD5 LOW by clearing bit 5 to 0 (LED ON)
    PORTD &= ~(1 << 5);
    delay(50000);
    // drive PD5 HIGH by setting bit 5 to 1 (LED OFF)
    PORTD |= 1 << 5;
    delay(50000);
    
    // drive PD4 LOW by clearing bit 4 to 0 (LED ON)
    PORTD &= ~(1 << 4);
    delay(50000);
    // drive PD4 HIGH by setting bit 4 to 1 (LED OFF)
    PORTD |= 1 << 4;
    delay(50000);
    
     // drive PA3 LOW by clearing bit 3 to 0 (LED ON)
    PORTA &= ~(1 << 3);
    delay(50000);
     // drive PA3 HIGH by setting bit 3 to 1 (LED OFF)
    PORTA |= 1 << 3;
    delay(50000);
  }
  
}
```

---

#### Task 224
> **Question/Prompt:** Make a program where LEDs are individually turned on and off (for half a second) in the following sequence: LED1 and LED3 are on when LED2 is off, then LED2 is on when LED1 and LED3 are off.

> **Answer/Explanation:**

```c
#include <iom324pb.h>

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){
  
  // set PD5 as OUTPUT by setting bit 5 to 1 
  DDRD |= 1 << 5;
  // set PD4 as OUTPUT by setting bit 4 to 1
  DDRD |= 1 << 4;
  // set PA3 as OUTPUT by setting bit 3 to 1
  DDRA |= 1 << 3;
  
  while(1){
    // drive PD5 LOW by clearing bit 5 to 0 (LED1 ON)
    PORTD &= ~(1 << 5);
    // drive PA3 LOW by clearing bit 3 to 0 (LED3 ON)
    PORTA &= ~(1 << 3);
    // drive PD4 HIGH by setting bit 4 to 1 (LED2 OFF)
    PORTD |= 1 << 4;

    delay(50000);

    // drive PD4 LOW by clearing bit 4 to 0 (LED2 ON)
    PORTD &= ~(1 << 4);
    // drive PD5 HIGH by setting bit 5 to 1 (LED1 OFF)
    PORTD |= 1 << 5;
    // drive PA3 HIGH by setting bit 3 to 1 (LED3 OFF)
    PORTA |= 1 << 3;

    delay(50000);
  }
  
}
```

---

## References & Resources
* ATmega324PB Xplained Pro Schematics
* IO1 Xplained Pro design documentation
* OLED Xplained Pro design documentation
* OLED1 Xplained Pro user guide
