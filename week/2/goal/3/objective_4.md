# Week: 2 - Goal : 3


## Objective 4: Light sensor

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[341]** | `CORE`    | [x] Completed 
| **[342]** | `CORE`    | [x] Completed 
| **[343]** | `CORE`    | [x] Completed 

--- 

#### Task 341
> **Question/Prompt:** Our next big move will be to integrate the light sensor within our project and writing code for handling the analog to digital conversion. On short we want to do: connect light sensor to pin, receiving analog signal based on ambient light, convert this signal to a digital value, light up LED. A preview of how the setup will look like is here: TEMT6000 Ambient Light Sensor with Arduino - YouTube.

> **Answer/Explanation:**
> 

--- 

#### Task 342
> **Question/Prompt:** Connect the I/O board with light sensor to EXT4. Read from the User Guide about sensor type, its datasheet and most important: connection to microcontroller's pins. Observe in the electronic schematic also the connections to GND and VCC (without them the sensor would not work, right?).
>
> So, this phototransistor will transform the ambient light (photons hitting the base of this NPN) into electrical current flowing through collector. And because a 100K resistor is placed in collector we can measure the voltage drop that occurs compared to 3.3V (which is the VCC). This voltage* will act as input analog signal for the microcontroller's pin connected.

> **Answer/Explanation:**
> - The light sensor uses pin 3 to read the signal, and this corresponds to pin PA4 on the ATmega324PB board.
> - VCC is connected to pin 20 of the EXT4 header.
> - GND is connected to pin 2 of the EXT4 header.
> - The sensor type is a phototransistor.
> - The signal type is analog voltage output: increased ambient light causes more current to flow to ground, which decreases the output voltage on the signal pin toward 0V. Conversely, total darkness allows the pull-up resistor to pull the voltage up to 3.3V.

--- 

#### Task 343
> **Question/Prompt:** Double check the connected pin for its second functionality (other than just being a pin for GPIO) at microcontroller's datasheet, table 16-3 from chapter 16.3.1. 
> 
> Therefore, somehow* the pin can act both as a GPIO and as an ADC reader. This aspect is called alternate functions. Who decides to switch between the alternatives? You as embedded developer, depending on what you have connected to the pin (LEDs or analog sensors). In our case we connected the ambient light sensor which gives us the analog signal, therefore you need to use the analog function of the pin. How this decision is made? By enabling the ADC peripheral (writing the correct bits in its registers) the GPIO functionality is disabled.
> 
> So, this phototransistor will transform the ambient light (photons hitting the base of this NPN) into electrical current flowing through collector. And because a 100K resistor is placed in collector we can measure the voltage drop that occurs compared to 3.3V (which is the VCC). This voltage* will act as input analog signal for the microcontroller's pin connected.

> **Answer/Explanation:**
> The alternate functions are ADC input channel and pin change interrupt.

---

## References & Resources
* I/O1 Xplained Pro user guide