# Week 3 · Part 2

> **GOAL: Fine tunning with PWM and State Machines**

By the end of this week you should be able to understand and implement PULSE WIDTH MODULATION + STATE MACHINES.

On short what you will do this week:

- use TC0/TC1 to build PWM signals
- control the brightness of LEDs with PWM
- understand and use the concept of state machines

---

## Objective 1: Understanding PWM signals

- **611** — [PWM attributes](https://www.youtube.com/watch?v=rBQVfCUuhfs)
- **612** — [How PWM works](https://www.youtube.com/watch?v=5nwNKPs2gco)
- **613** — [PWM with AVR timers explained](https://www.youtube.com/watch?v=mVx02s1fHIY)
- **614** — [An example with PWM](https://www.youtube.com/watch?v=9WeewNNGs5E)

---

## Objective 2: Fast PWM MODE of operation for TC0

- **621** — The Fast PWM is an operating mode of TC0 timer. Having already some experience with ADC operation and Normal/CTC modes of operation for TC0, you are now able to study chapter 17 in the datasheet, looking for Fast PWM Mode. You should apply the same 8 identified steps as for the aforementioned operations.
- **622** — Check on the boards (user guides, schematics) to what pins you can output a PWM signal and if those pins have LEDs connected !!! Not all pins can support/output PWM signals.
- **623** — Construct a new module for PWM feature containing the appropriate functions (remember: initialization, atomic actions, etc.). Do the math for implementing into one single function the following 5 use cases with PWM:
    - output a PWM signal with 100% duty cycle
    - output a PWM signal with 75% duty cycle
    - output a PWM signal with 50% duty cycle
    - output a PWM signal with 25% duty cycle
    - output a PWM signal with 0% duty cycle

    Individually apply each case to the LED identified as supporting PWM.

- **624** — Having the Task Scheduler as your best friend (!) design an application where you incrementally apply these use cases to the LED identified as supporting PWM. e.g. you can apply the signal in an incremental way: on the first run of 10ms task you apply 0% duty cycle, on the second you apply 25% duty cycle, on the third 50%, and so on and so forth, then start all over again.
- **625** — What is the duty cycle resolution of the PWM signals (= the smallest duty cycle % step you can increment with) that can be build on TC0? Number of steps: *(<<< answer here)*. Step size (resolution in %): *(<<< answer here)*
- **626** — Add a new feature to your PWM driver: the possibility to change the duty-cycle with 1% step size. You would build a new provided interface e.g. `void pwm_dc(int param);`

---

## Objective 3: Complex behaviors

- **631** — Build the next behavior for the LED identified as supporting PWM. The sequence described will be repetitive with pause (= PWM duty cycle 0%) of 3s. Be very attentive as the graphic below shows not the duty-cycle of a PWM signal, but the variation (!!!) of the PWM duty-cycle across time. The duty-cycle resolution you choose for ramping up PWM from 0% to 100% is up-to-you.
- **632** — Build the next behavior for the LED identified as supporting PWM. Be attentive to the indications of the scale!
- **633** — **OPTIONAL** — Build an application varying the PWM signal applied to an LED based on sinus function, `f(x) = sin(x)`. Note that it is impractical to look over full and continous range of `f(x)` values, therefore you should consider only few discrete points (time, dc%).
- **634** — **OPTIONAL** — The Heart Beat illumination pattern was developed by Marquardt. In Reference Documents folder you will find the `HeartBeat_illumination_pattern.xlsx` file which presents you the variation of the PWM signal. Build an application based on the Heart Beat illumination pattern.

---

## Objective 4: HYUNDAI Imaginary Use Case

- **641** — HYUNDAI is an important asian customer for Marquardt. It plans a new Elantra carline to be unveiled next year. Today they are in prototyping phase. A Request For Bid (RFB) has been sent to Marquardt Rietheim Headquarters for a rapid prototype on Elantra's dashboard background illumination control. Therefore the management of Marquardt set up a mixed german-romanian team to make a prototype and go to Seoul, South Koreea next week. You are part of this team. If presentation to the customer is good then your team wins the project! Heavy responsability on you!

    There are a just few requirements received from Hyundai. Lack of details force you to take some engineering decisions to go on. The requirements are referring to a day illumination design (that means the way LEDs are behaving during the day light intensity) and a night illumination design (that means the way LEDs are behaving during night light intensity). Both designs are based on the measured ambient light intensity within the driver's cockpit. The measurements are based on TEMT6000 light sensor which outputs an analog signal (high light intensity = low voltage, and low light intensity = high voltage). To make a good impression to the presentation in Seoul, you have chosen to use 10bit ADC resolution which assures a fine grain reading of the light intensity. On the main board (ATmega324PB Xplained PRO) you choose SW0 switch to enable the headlights, therefore also the interior light intensity measurements are started in parallel. You need these initial measurements to detect if your prototype should behave in day or night mode.

    Once again, Hyundai detailed only the entry phase in the illumination design (when driver switches on the headlights!) and not the complete behavior (e.g. what happens after entry phase when ambient light is changing continously, how reactive the prototype should be or the illumination curve response after entry phase). The latter are up to you, to propose a certain design so that you please the customer. You can also counter-propose to Hyundai a different approach to the entry phase, but this only after you presented his request :) e.g. maybe you observed the requested illumination pattern to be too agressive for the human eye because of the PWM entry levels or too faint and not observable.

    Remember: in prototyping it is room for negociation, the final objective is to please the customer within realistic technological possibilities and win the project.

    Additionally with OLED1 board you implement the visual feedback to the driver/passenger in the car. Use two LEDs, LED1 and LED2 for background illumination in Day mode and Night Mode. Each time SW0 is pressed then the driver scenario turning on the headlights is repeated. Take care that Hyundai has a preference over the entry phase in Day/Night design (see Table 741.1 and Table 741.2).

    **Table 741.1**

    | Eye Perceived Light Levels | PWM % duty-cycle ABSOLUTE entry level | Design/Mode |
    | -------------------------- | ------------------------------------- | ----------- |
    | 0 - 20 | 15% | Night |
    | 21 - 40 | 20% | Night |
    | 41 - 50 | 42% | Day |
    | 51 - 70 | 80% | Day |
    | 71 - 100 | 90% | Day |

    **Table 741.2**

    | Time [sec] | Entry phase Night mode RELATIVE steps | Entry phase Day mode RELATIVE steps |
    | ---------- | ------------------------------------- | ----------------------------------- |
    | 0 | 0 | 0 |
    | 0.2 | 1 | 4 |
    | 0.4 | 1 | 7 |
    | 0.6 | 3 | 16 |
    | 0.8 | 7 | 44 |
    | 1 | 16 | 59 |
    | 1.2 | 16 | 59 |
    | 1.4 | 14 | 55 |
    | 1.6 | 12 | 50 |
    | 1.8 | 10 | 45 |
    | 2 | 8 | 40 |

    Success in winning the project !!! Enjoy your 22h flight and don't forget to come back with some souvenirs from Seoul !!!

---

## Objective 5: Measuring the code size

- **651** — Why bother measuring the code size? In embedded systems we don't have at our disposal too much memory, from ~2KB to ~8MB, therefore it becomes a highly important resource you should take care about. Activate memory map by right-click on Project Name => Options => Linker => List and make sure you mark the following checkboxes.
- **652** — Then, after compiling, open from Project Browser the `.map` file. This file is showing you the layout of object files and how the linker processed those object files into the final executable file. There are a lot of things to know about linker, but for the moment retain the following:
    - a function or a variable is usually named ENTRY
    - memory is organized in several zones, most important are CODE (storing your code) and DATA (storing your variables)
    - within those memory zones there will be several types of SEGMENTS
    - addresses are given in hexadecimal as start address and end address (in paranthesis is the ENTRY's total size in hexa)

    Below is the example of `main.r90` object file corresponding to `main.c` file containing the initial code from exercise 143 (yeah! week 1 :)).

- **653** — Open the `.map` file of your current project code and check the code size for the following functions:

    | functions proposed for measuring | implementation with switch — CODE | implementation with switch — DATA\* | implementation with binary operators — CODE | implementation with binary operators — DATA\* |
    | -------------------------------- | --------------------------------- | ----------------------------------- | ------------------------------------------- | --------------------------------------------- |
    | `set_pin (…)` |  |  |  |  |
    | `reset_pin(…)` |  |  |  |  |

    !!! note "Note"
        As learned last week, the hardware registers are mapped to variables, therefore you should find them within DATA, but you don't include them here when counting because their memory space is "used" anyway.

- **654** — Optimize your code in order to occupy less ROM memory. Keep a record or screenshots "before" and "after".
- **655** — Do you think code size is the only measure of code performance? Can you give examples of other measures of code performance? *(<<< answer here)*
- **656** — **OPTIONAL** — To modify one or several bits in a register without affecting the others, so just the ones you need, you now have/know two methods: bitfields (see the expansion talk week 1) and bitmasks. But which one is better to use in terms of code size and execution cycles? Compare code performance when applying the two methods, in terms of code size and execution cycles, for the use cases of modifying 1, 2, 3..., 8 bits at once. You should use the assembler code in Disassembly window, and for each instruction you can check the Instruction Set Summary in the microcontroller's datasheet for the amount of cycles/clocks it takes. Table your data observed and draw conclusions.

---

## Objective 6: Understanding State Machines (SM)

- **661** — [State machines ease programming microcontrollers - EDN](https://www.edn.com/state-machines-ease-programming-microcontrollers/)
- **662** — [What is a state machine? (itemis.com)](https://www.itemis.com/en/products/itemis-create/documentation/user-guide/overview_what_are_state_machines?hsLang=de)
- **663** — As a summarization, the main elements of State Machines are STATES, EVENTS and TRANSITIONS which are executed based on some GUARDS conditions. When arriving in a particular state, then an ACTION/OUTPUT has to be performed. For OLED1 board imagine the following scenario:
    - each button X (X = 1,2,3) when pressed will determine the corresponding LED X (X = 1,2,3) to be turned on
    - when pressed a second time, the button X will turn off the corresponding LED X

    Identify in a list (not implement yet!) the key elements of a state machine in the described scenario (look for STATES, TRANSITIONS, GUARD CONDITIONS, ACTIONS/OUTPUTS).

- **664** — Use an UML STATE MACHINE DIAGRAM to describe/capture the elements identified previously. e.g. online tools: [draw.io](http://draw.io/).

---

## Objective 7: Implementing State Machines

- **671** — To implement the state machine description into C programming language we should consider the following:
    - implementation using nested IFs statements
    - implementation using SWITCH statement
    - implementation using POINTERS to FUNCTIONS

    We can also consider the following correspondence State Machine key elements - C constructs:

    - STATES are usually kept into variables in C (some preference exists for enums as they keep an automatic numbering for the considered states)
    - EVENTS are usually implemented like enums or simple variables
    - TRANSITIONS are associated with a SWITCH structure (contained in the function handling the transitions) and the GUARD condition that must be met is checked with IF statement
    - ACTIONS/OUTPUTS are all normal C code statements that have to be executed for that specific state (e.g. turn on LED)

    All things considered, even if you are designing a state machine as a way to better organize your code, this will not exclude the usage of a task scheduler (since the events and guard conditions will be checked constantly). In this way you have a very powerful combination between task scheduler and state machines as design concepts for any embedded systems application.

- **672** — Consider LED0 with blinking behavior (ON 1sec, OFF 1 sec) implemented with IFs like in the example below. Use draw.io to draw UML State Machine diagram for it. Then re-write the code using the Task Scheduler and your own State Machine to drive the behavior described.
- **673** — Consider the code below. It is a State Machine to light up LED0 with a certain behavior. It is implemented with a SWITCH statement and state variable. First, draw an UML State Machine diagram and then re-write the code using Task Scheduler and your own State Machine.
- **674** — Below is an example of how a pointer to function works. And further, you have a pointer to function based implementation of a LED0 behavior. Check if the State Machine is the same as previous exercises. Re-write the code using pointers to functions, task scheduler and your own state machine (adapt to your board connections).
- **675** — What would be the advantage of using pointers to functions within state machines?

---

## Objective 8: Control Panel Application RE-REVISITED

- **681** — Go to BMW Control Panel Application and refactor the code using State Machine concept:
    - identify key-elements
    - draw State Machine diagram
    - implement State Machine
