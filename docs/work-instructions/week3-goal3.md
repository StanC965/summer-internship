# Week 3 Â· Goal 7

> **GOAL: UART Serial Communication**

By the end of this week you should be able to design and implement a serial communication.

On short what you will do this week:

- understand the concept of serial communication
- apply the concept of serial communication to your application

---

## Objective 1: Understanding Serial Communication

- **711** â€” **CORE** â€”  [Understanding Serial Protocols - YouTube](https://www.youtube.com/watch?v=LEz5UCN3aHA)
- **712** â€” **CORE** â€”  [Understanding UART - YouTube](https://www.youtube.com/watch?v=sTHckUyxwp8)
- **713** â€” **STRETCH** â€”  [PROTOCOLS: UART - I2C - SPI - Serial communications #001 - YouTube](https://www.youtube.com/watch?v=IyGwvGzrqp8)
- **714** â€” **STRETCH** â€”  [UART (Universal Asynchronous Receiver Transmitter) - Basics - YouTube](https://www.youtube.com/watch?v=npL5ph9RG84)
- **715** â€” **STRETCH** â€”  [UART - Troubleshooting tips (Debugging UART issues) - YouTube](https://www.youtube.com/watch?v=r-N53fpaJWo)
- **716** â€” **STRETCH** â€”  [Tutorials for the AVR Microcontroller : UART](https://www.youtube.com/watch?v=e8uEKWpVf10)
- **717** â€” **STRETCH** â€”  **FOR YOUR INFORMATION:** RS-232 is a very similar serial protocol to UART (it is similar because in its simplest form has the same hardware connections and uses the UART frame definition, but voltage levels are very different). It is used today mainly for industrial applications. Also your PC could still have the DB9 connector for RS-232.

    - [Serial Ports Are STILL Around! - YouTube](https://www.youtube.com/watch?v=kvNm7nmEUFo)
    - [Serial Ports - YouTube](https://www.youtube.com/watch?v=O1MhwPb2NWA)
    - [Control LEDs with your computer using RS232! - YouTube](https://www.youtube.com/watch?v=2T9ca53KMrM)

- **718** â€” **STRETCH** â€”  **FOR YOUR INFORMATION:** Inside your car there is LIN serial communication protocol which uses the UART hardware connections, frame definition and voltage levels. However, the number of frames, their sequence and the meaning of data sent with the frames is what makes LIN a new protocol on top of UART definitions. Marquardt develops products based on LIN protocol.

    - [LIN Message Frame - Developer Help (microchipdeveloper.com)](https://microchipdeveloper.com/lin:protocol-dll-lin-message-frame)

---

## Objective 2: Setting up the USART

- **721** â€” **CORE** â€”  First, observe that for our microcontroller the naming is not UART (as general accepted) but USART. The letter S comes from a feature enhancement of this peripheral: the engineers have decided to add a clock line, transforming the asynchronous UART into a synchronous one. The synchronous communication is not an UART anymore but an SPI (Serial Peripheral Interface) using the same hardware with UART. You can look at this enhancement as two mutual exclusive modes of operations of the same USART hardware module. We will not use the synchronous mode, therefore we will implement an asynchronous UART communication using the USART peripheral. For the sake of consistency we will keep the datasheet naming only for the peripheral references and the register names, but use UART name every time we refer to the communication protocol.
- **722** â€” **CORE** â€”  To implement a simple UART communication we will use the IO1 board. Observe that on the IO1 board there is a black jumper which connects the TX and RX of the same USART peripheral (e.g. USART0). This connection is called loopback. We will use those TX, RX connected together to simulate the communication between two different microcontrollers. Imagine that TX is from MCU1 sending messages and RX is from MCU2 receiving the messages. This is a simplex communication (one way communication, as MCU2 will not be able to respond back to MCU1, because RX pin cannot transmit, it only receives, but that's ok for our purpose here).
- **723** â€” **CORE** â€”  Identify (using schematics and User Guides) the exact peripheral name which has the TX, RX exposed on IO1. Is it USART0, USART1 or USART2? *(<<< answer here)*
- **724** â€” **CORE** â€”  Use the same approach as you had for ADC and TIMER peripherals to study the datasheet chapter for USART peripheral. Observe there is a chapter also dedicated to the USART in SPI mode which we will NOT use. Therefore ask yourself how many registers there are, what settings to choose (keep it simple!), how does UART communication works (keep it simple in using the features). Today you have become a mature engineer and you can take accountable decisions for yourself. Congrats!

---

## Objective 3: Implement driver and test application

- **731** â€” **CORE** â€”  Implement a new software driver for your peripheral: start simple (send a single byte, receiving a single byte), then you can complicate things more (like sending/receiving a couple of bytes which could represent a string). Be attentive to the separation of concerns (what a driver is supposed to do, and what an application is supposed to do) and give appropriate names for the files, functions, variables.
- **732** â€” **CORE** â€”  With the help of the new constructed driver, make an application to send and receive the "Hello World!" string. Again, be attentive to the separation of concerns of application vs. driver.

---

## Objective 4: Control Panel Application ... AGAIN ?! ... as a masterpiece ;)

- **741** â€” **CORE** â€”  Go to BMW Control Panel Application and refactor the code using the serial UART communication (simplex, that means one way) as follows:
    - imagine that on the physical microcontroller (ATmega324PB) we construct two virtual microcontrollers (MCU1 and MCU2)
    - these two virtual microcontrollers are connected by TX/RX line forming a simplex master-slave communication channel (MCU1 = master and MCU2 = slave)
    - all the buttons from your system will be read by virtual MCU1 via the physical pins of ATmega324PB
    - the buttons states are interpreted by virtual MCU1 and appropriate LEDs states are build and stored by virtual MCU1 but not executed
    - virtual MCU1 will send over UART protocol (by TX physical pin) the appropriate data/commands for LEDs light on/off behavior
    - virtual MCU2 (the slave) will receive these data (by RX physical pin) and execute/implement the LEDs behavior as requested by virtual MCU1 (the master)
