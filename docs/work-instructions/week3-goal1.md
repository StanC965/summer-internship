# Week 3 · Goal 5

> **GOAL: Build a task scheduler**

By the end of this week you should be able to understand and implement processor time scheduling.

On short what you will do this week:

- use TC0 to build a scheduling algorithm
- design your application with task/function scheduling perspective

---

## Objective 1: Building from scratch a TASK SCHEDULER

- **511** — **CORE** —  First we relied on the `while(1)` loop to make the CPU go through our functions calls and execute those functions. Then we added interrupts, forcing the CPU to respond to events with routines execution. We had no concern about the "time" the CPU is spending with a particular function execution. A task scheduler is about that: taking care of CPU spent time on functions execution.

    Because "CPU time" is a resource, we would like to share this resource cooperatively among the functions from our program. Therefore we allocate a "time slot" or "time slice" for each function. Time slot/slice is the time passed between two consecutive timer interrupts. Time slots are periodic as timer interrupts are periodic. So each function has its CPU execution between two timer interrupts. How you trigger the execution of a function? Allocate a flag for each function and activate that flag for the time slot you want the execution to happen. Flags are activated within the ISR. This selective activation of flags is called flags management and it's similar to what you exercised last week by extending real time measurements beyond the maximum timings TC0 could provide.

    One more thing remains to do before scheduling is complete: looping through the flags and check if they are activated. If yes, then it's time to call that particular function to which this time slice has been allocated.

    At its core, a task scheduler consists of:

    1. system tick (based on timer interrupts)
    2. flags manager
    3. tasks dispatcher

- **512** — **CORE** —  **System Tick**. Choose a timer that will be dedicated to construct the system tick, e.g. TC0 or TC1. Set the timer for interrupts at 10ms precise interval. ATTENTION! in order for you to obtain the most accurate 10ms interval you have to research what is the best setup. So, play around with:
    - the initial settings for oscillator (uncheck the option "Divide clock by 8 internally" and/or choose external oscillator)
    - the 8bit vs. 16bit timers

    Remember that you are looking for the smallest deviation/offset from the 10ms mark... and make a final decision! Now you have an accurate system tick. As file organization is concerned, this interrupt service routine should be placed in the corresponding timer module. The timer you choose will remain dedicated to do the scheduling and you cannot use it for something else in your program.

- **513** — **CORE** —  **Flags Manager**. Starting with 10ms period build other longer periods of time: 50ms, 100ms, 500ms, 1000ms. Dedicate flag variables for each period. Optionally you can add more periods. You can gather all these into a single function, e.g. `void scheduler_flags_management (void)`. Call it from within the ISR. As file organization is concerned, this flags management function should be placed in scheduler module.
- **514** — **CORE** —  **Tasks Dispatcher**. Inside the `while(1)` loop you will check for the flags associated to the defined time slots and if they are set, then the associated function will be called. After the call, that particular flag must be reset in order to avoid the second call of the same function per current time slice when `while(1)` is re-entered. The final result of these constructs will be that each function call is time-spaced apart by a time slice of 10ms. Precisely! What a schedule!!! It is a cooperative schedule because functions are not prioritized, they do not interrupt each other.
- **515** — **CORE** —  A final makeup for file organization to be complete:
    1. replace the particular function calls with generic function calls (these are tasks), e.g. `task_500ms( );` Within the body of the generic functions you now relocate the call to particular functions.

        ```c
        void task_500ms (void) {
            led_on( );
        }
        ```

        This relocation and generic functions creation is a nice way to prepare our task scheduler to be used in any other context just by replacing the `led_on()` call.
    2. relocate the `while(1)` loop inside `void schedule_tasks_dispatcher (void)` function, which will be the core of the task scheduler. Relocate this function in the scheduler module and call it from within the main module (in similar way as Arduino Framework does with `loop ( )` function).

- **516** — **OPTIONAL** — Can you improve the flags storage so that they would occupy less memory? Experiment with your code.

---

## Objective 2: Ambient Light Application REVISITED

- **521** — **CORE** —  A task is executed when the corresponding flag of the time slice (e.g. 50ms) is set by the flag manager. You can populate a task with any function call you want. Thinking about your application as a sum of periodic events it is like designing your application to work in a task based environment, or with other words you are doing task oriented application design.

    !!! note "Note"
        In the software design paradigm, the terms of provided interfaces and required interfaces are used. Interfaces are functions. Interfaces provided by a module outside of it are publicly declared or have no static keyword in front of their name. The required interfaces of a module are those empty functions (no code in their body). They are already called somewhere in the code of the current module. The software engineer who includes the current module in his software program will need to write custom code into those functions to create the desired functionality. In other words, a module's callbacks are points in the code of that module from where CPUs can be assigned to an unknown code at the time the module was created. In our case, at the moment of creating the SCHEDULER module it is not known which code the tasks will have, but the scheduler reserves points in his code to give control of the program to some later written functions (tasks of LEDs ignition, reading buttons, etc.).

    In conclusion, re-organize your scheduler module as follows:

    - `scheduler.c`, contains `schedule_dispatcher`, `schedule_flags_management` functions; acts as the collection of these lollipops
    - `scheduler.h`, contains prototypes of provided functions
    - `scheduler_cfg.c`, contains initially the tasks empty bodies and after you decide what to connect with that task (what function to be called when task is executed) contains that function call; acts as the collection of these hooks
    - `scheduler_cfg.h`, contains prototypes of required functions

- **522** — **CORE** —  Go to Ambient Light Application and refactor the code as follows:
    1. encapsulate/hide the data result to adc module (use static keyword)
    2. provide a "get" interface / function to use the data result in other modules, e.g. `adc_get_data( );`
    3. make use of task scheduler to schedule the start of conversion, getting and using the data result for ambient light indicator (the 3 LEDs)
- **523** — **STRETCH** —  Use an online tool for UML diagrams to make a diagram for connections you decided between scheduler module and other modules of your program. Use a UML component diagram type and the lollipop notation as above. Highlight the provided/required functions/tasks. e.g. online tools: [draw.io](http://draw.io/), [smartdraw.com](https://www.smartdraw.com/uml-diagram/), [visual-paradigm.com](https://online.visual-paradigm.com/diagrams/).

---

## Objective 3: Understanding DEBOUNCE with Task Scheduler

- **531** — **STRETCH** —  [Software Debounce](https://www.youtube.com/watch?v=jYOYgU2vlSE)
- **532** — **STRETCH** —  [Hardware Debounce](https://www.youtube.com/watch?v=FOMI2J-y1Rc)
- **533** — **CORE** —  The BOUNCE term applies to electric signal generated when we press the button. The DEBOUNCE term intervenes when we want to read the signal. Can be implemented by reading 5x times the same signal generated when we push the button. The readings are spaced-time apart with the help of the scheduler tasks. Finally the principle applied to the acquired 5 samples is the majority principle: all samples must be with the same value (`00000` or `11111`) to consider the button pressed or not-pressed. The samples can be stored temporary in a buffer (that means a variable whose bits are shifted to the left each time a new sample is acquired). The debounce is done continously, all the time: with other words it is like a 5 samples window which is moving along the signal. So one sample in, one sample out, one sample in, one sample out, etc. We can characterize the debounce in terms of time: `debounce time = task of X ms * no. of samples`, e.g. reading 5 samples within 10ms task => 50ms debounce time.
- **534** — **OPTIONAL** — Use the UML Activity Diagram type to illustrate the debounce algorithm (within the same online tools you have used before).

---

## Objective 4: Control Panel REVISITED

- **541** — **CORE** —  Go to BMW Control Panel Application and refactor the code as follows:
    - introduce the task scheduler for handling of buttons and LEDs behavior
    - use debounce algorithm for a stable state of buttons
