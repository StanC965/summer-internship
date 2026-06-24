# Week 1 · Part 2

> **GOAL FOR THIS WEEK 2: Design a good software program for controlling LEDs and buttons**

By the end of this week you should be able to control basic elements of every embedded system: LEDs and buttons.

Personal programming style/performance should be acknowledged and improved (comments, clarity, modularity).

On short what you will do this week:

- get to control some LEDs
- use generalization, modular programming and other software design principles to improve your coding style/performance
- use polling to read buttons

---

## Objective 1: Turn on user LED0

- **211** — Clean your `main.c` file and include the header file `iom324pb.h` using include directive (`#include`). The function `main( )` should be of type `void` and it has no return statement because it is never returning! Compared to PC software program, the embedded software program has this unique characteristic: it is stuck in an infinite `while(1)` loop. Intentionally!!! Therefore your program must have this loop also.
- **212** — How many pins does the PORTC port have? *(<<< your answer here)*
- **213** — How many GPIO (General Purpose Input Output) ports does the ATmega324PB microcontroller have in total? *(<<< your answer here)*
- **214** — Search in the dev board User Guide the port and the pin to which LED0 is connected and how you should light up (or activate) LED0. Read carefully, repeatedly (maybe 10x), see if you really understand that information. You can correlate with the information from electronic schematic of our dev board. See if all these information match in your mind with the general knowledge on LEDs control acquired last week. Further correlate with microcontroller datasheet on how to configure the pins (chapter 16.2.1).
- **215** — Write a program code for light up the LED0. You need to take control over the registers implied in turning LED0 on. Compile and download the code. Run the code in order to see LED0 on. Congrats!
- **216** — Program LED0 to be turned on for 1 second\*, turned off for the next 1 second and so on (repeat the sequence).

    !!! note "Note"
        For the LED0 to stay 1 second turned on you will need to use a time delay. We are calling it **software delay**. A software delay can be built using a `for` loop big enough to count for 1 second.

??? info "Additional materials — FOR YOUR INFO"
    Explore how microcontrollers work here:

    - [Exploring How Computers Work - YouTube](https://www.youtube.com/watch?v=QZwneRb-zqA)

---

## Objective 2: Turn on external LEDs

- **221** — Check the electronic schematic of the ATMega324PB development board. Is there any resistor connected with the integrated LED0 in order to protect it? What value has that resistor? *( <<< resistor value here )*
- **222** — In `Reference_Documents` folder you find the electronic schematics for OLED1 and IO1 boards (check `.zip` files). Can you figure it out, just by reading the schematics (NOT the User Guide!!!), how to turn on the contained LEDs for each board?
- **223** — Check that OLED1 extension board is connected to EXT1 header. Program all 3 LEDs to be turned on at once. Double check(!) with User Guide for OLED1 to see if schematics information matches with regards to LEDs activation.
- **224** — Make a program where LEDs are individually turned on and off (for half a second) in a repetitive sequence.
- **225** — Make a program where LEDs are individually turned on and off (for half a second) in the following sequence: LED1 and LED3 are on when LED2 is off, then LED2 is on when LED1 and LED3 are off.
- **226** — Make a program where LEDs are individually turned on and off (for half a second) in the following sequence, described by the table:

    | LED id | initial state | state 1 | state 2 | state 3 |
    | ------ | ------------- | ------- | ------- | ------- |
    | 1 | OFF | ON | OFF | ON |
    | 2 | OFF | ON | ON | OFF |
    | 3 | OFF | OFF | ON | ON |

    *(state 1 → state 3 form a repetitive sequence)*

- **227** — But wait: have you asked yourself so far that you should have put a resistor in the connection with LEDs? You missed the resistor but the LEDs are working fine. Why? *(<<< answer here)*
- **228** — **OPTIONAL** — Make your own Christmas Tree like sequence, for playing the LEDs and describe it in the table below. Up to 5 states and 5 LEDs available (not mandatory to use them all).

    | LED id | initial state | state 1 | state 2 | state 3 | state 4 | state 5 |
    | ------ | ------------- | ------- | ------- | ------- | ------- | ------- |
    | 1 |  |  |  |  |  |
    | 2 |  |  |  |  |  |
    | 3 |  |  |  |  |  |
    | 4 |  |  |  |  |  |
    | 5 |  |  |  |  |  |

??? info "Additional materials — FOR YOUR INFO"
    Explore how LEDs are working:

    - [Light-Emitting Diodes (LEDs) - SparkFun Learn](https://learn.sparkfun.com/tutorials/light-emitting-diodes-leds/all)

    How to work with bitmasks:

    - [What are Bit Masks, and how do I use them?](https://www.youtube.com/watch?v=Ew2QnDeTCCE)

---

## Objective 3: GPIO and Generalization Principle

- **231** — Build a single function e.g. `set_pin( … )` to set (set = means writing value "1" to bit) any pin from register PORTC, without affecting the state of the remaining pins from the PORTC. What parameters do you need to build the function? Test this function with LEDs connected to PORTC pins.
- **232** — Build another function e.g. `reset_pin( … )` to reset (reset = means writing value "0" to bit) any pin from the same register without changing the other pins value from the register. Test with LEDs connected to PORTC.
- **233** — Finally, build a function only for managing the direction (input/output) of any pin. It can be named e.g. `set_direction( ... )`. What parameters should it receive and what values should it return?
- **234** — **OPTIONAL** — Build yet another function e.g. `toggle_pin( … )` to toggle any pin from the same register, without affecting any other pin from the register.
- **235** — **OPTIONAL** — A real challenge is to reduce the complexity of the code for each function above, by writing the functionality of each function in a single line of code! How can you realize this?
- **236** — **OPTIONAL** — Yet another challenge is to generalize the functions above to cover all existing ports and pins on this ATmega324PB microcontroller! In this way you will cover any connection LED <=> pin! What parameters you could design your function to have in order to cover the existing variability?

---

## Objective 4: Modular programming

- **241** — Reorganize your code written until now using the following templates from `Reference_Documents` folder: `mod.c`, `mod.h`.

    File `mod.c` is divided into several areas:

    - information about who is the author of this module and the date on which it was created
    - the area where other necessary headers for this module are included
    - definition area of static variables (private to this module)
    - declaration area of static functions (private to this module)
    - definition area of public functions (which will be seen by other modules, interfaces provided)
    - definition area of static functions (hidden in this module)

    File `mod.h` is the interface of this module with other modules and contains:

    - information about who is the author of this module and the date on which it was created
    - declaration area of data types used in this module and the constant values (`#define`)
    - declaration area of public functions (those that can be called in other modules)

    Therefore build two files `gpio.c` and `gpio.h`. In general, there is a convention that this combination of files (`.c` and `.h`) represents a software module. The gpio module must contain only functions and variables used in the very basic management/handling of the pins and ports of the microcontroller (e.g. set, reset pins, etc.). Then include the `gpio.h` header (the module's interface) in the `main.c` file to give the program access to the functions contained in the `gpio.c`. The `main.c` module will remain as the central module that makes the integration of all the other modules you will create in the future. Why do you think it would be so much needed to organize our software program in a modular way? *(<<< your answer here)*

- **242** — Further separate the software program, considering the functionality of the LEDs (on, off). Create a new LED module (`led.c` and `led.h`) which will contain only the variables and functions that manipulate the on/off state of LEDs (e.g. functions might be referred as `PowerOn_LED(...)` and `PowerOff_LED(...)`). These led related functions will call the basic i/o functions of the gpio module!\*

    !!! note "Note"
        With basic i/o functions from gpio module you can control not only LEDs, but motors also, communication signals, etc. Therefore is a good modular design to keep i/o functions separate from the abstract behavior they sustain.

- **243** — The separation of functionalities in logical units allows us to develop new functionalities. For example, add two new LED functionalities to the LED module:
    1. LED blink fast = The LED lights on and off repetitively with 6-ons and 6-offs per second;
    2. LED blink slow = The LED lights on and off repetitively with 2-ons and 2-offs per second.

    Compile again. It often happens during software development to have to reorganize the written code, process called redesign or refactoring.

- **244** — In the header file `mod.h` observe the existence of some constructs at the beginning and at the end of the file (they are called guardians). By analogy, to the gpio module they should look like:

    ```c
    #ifndef GPIO_H
    #define GPIO_H
    ……..
    #endif
    ```

    In your opinion what would be the role of these constructs? To clear the issue of these constructs, compare the output files `.i` of the preprocessor in these use cases:

    | What you observe to `.i` files when... | ...gpio.h is included ONCE in main.c | ...gpio.h is included TWICE in main.c |
    | -------------------------------------- | ----------------------------------- | ------------------------------------- |
    | gpio.h with guardians |  |  |
    | gpio.h without guardians |  |  |

??? info "Additional materials — FOR YOUR INFO"
    - [Modular programming - Wikipedia](https://en.wikipedia.org/wiki/Modular_programming)
    - [C "Modules" - Tutorial](https://www.youtube.com/watch?v=8KyZedtkEhk)
    - [Header Issues: Guards, Name Mangling, and extern "C" - YouTube](https://www.youtube.com/watch?v=NeOTr0u7ALk)

---

## Objective 5: Reading the user button SW0 - debounce

- **251** — Search in the User Guide the port and the pin to which the SW0 button is connected. Pin direction must be input (signal will be read). To use SW0 you must activate the pull-up resistor for that pin (write 1 to the pin's corresponding bit of the PORTx data register). By pressing the SW0 button the i/o line of the PINx port is coupled to GND (see User Guide and Electronic Schematic). Define a variable to which you assign the value of the PINx register and test if button is pressed. First code you should do it step by step (debugging the code and check the Registers and Watch Windows) in `main.c` file.
- **252** — Within `main.c` file combine the reading of a "pressed" SW0 button with turning ON the LED0. Congrats!
- **253** — The GPIO module should be developed further. So add/modify the GPIO module according to the new button functionality. What variables and/or functions should be changed or added? Remember the point where we started in the modular programming. Observe one of the advantages of modular programming, that the code interventions are punctual in the modules affected by the newly added button functionality (LED module is not affected).
- **254** — [Software debounce for buttons (VIDEO)](https://www.youtube.com/watch?v=sSOz1QcYnB0&list=PLE72E4CFE73BD1DE1&index=14)
- **255** — Introduce a debounce for the button you read to filter the noise in the signal when pressed or released.

---

## Objective 6: Architecting S.O.S. - polling technique

- **261** — Yet another step towards writing a more professional code is abstractization. Let us introduce a new LED0 behavior: SOS sequence, which in MORSE language is 3 points, 3 lines, 3 points `. . . - - - . . .`. Write code to turn on/off the LED0 simulating the SOS signal. First build the POINT and the LINE (with appropriate functions) which are nothing else but abstract behaviors of the LED0 on/off basic functionalities (so the POINT appropriate function will call the LED on/off functions). Then build the SOS behavior (creating appropriate functions) which behavior is nothing else but yet another abstract luminous behavior of the same LED0, build upon the POINT and LINE behaviors previously created (thus calling the functions implementing POINT and LINE).

    !!! note "Note"
        This kind of thinking in abstract levels (complex behavior build upon other simpler behaviors) you will encounter when as a software embedded engineer you will deal with Software Architecture of your system. In a simplistic way the Software Architecture for the system you have build so far would look like this:

    | Abstraction Level | Elements from the corresponding level |
    | ----------------- | ------------------------------------- |
    | Application software | `sos.c, sos.h` |
    | Intermediate software | `led.c, led.h, button.c, button.h` |
    | Basic (driver) software | `gpio.c, gpio.h, iom324pb.h` |
    | Hardware | microcontroller registers (e.g. PORTC, etc...) |
    | Physical | voltage levels (e.g. GND, VCC, 0V, 3.3V, etc...) |

- **262** — Code to launch the SOS signaling at the press of the SW0 button. The complete SOS sequence runs indefinitely with a 1 second break between the smaller sequences (see graph).
- **263** — Make the SOS message begin when the SW0 button is pressed for the first time. At the second press of the SW0 button, the SOS message must stop. At the next press, SOS starts, and so on. Depending on your "resolution" to poll the state of the SW0 button (e.g. after each point, or after each letter) you might need to hold down pressed SW0 for a longer period of time or less, so that it can be read correctly.

---

!!! success "END OF WEEK 2"
